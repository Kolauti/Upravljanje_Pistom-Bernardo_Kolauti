/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <upravljanjePistom.h>

InterruptIn m_zabranjenoKoristenjePiste{ARDUINO_UNO_D10};
InterruptIn m_smjerKretanjaAviona{ARDUINO_UNO_D9};
Ticker m_maintanance;
Timer m_debounce;
UpravljanjePistom *upravljanjePistom(
    new UpravljanjePistom(ARDUINO_UNO_D8, ARDUINO_UNO_D7, ARDUINO_UNO_D11,
                          ARDUINO_UNO_D12, ARDUINO_UNO_D14, ARDUINO_UNO_D15));
std::chrono::microseconds m_maintanaceSignalingTimeout = 10s;

void promijeniSmjerKretanjaAviona(void) {
  if (m_debounce.read_ms() > 500) {
    upravljanjePistom->promijeniSmjerKretanjaAviona();
    m_debounce.reset();
  }
}

void zabranaKoristenja(void) {
  if (m_debounce.read_ms() > 500) {
    if (m_zabranjenoKoristenjePiste.read() == 1) {
      m_maintanaceSignalingTimeout = 5s;
    } else {
      m_maintanaceSignalingTimeout = 10s;
    }
    upravljanjePistom->zabranaKoristenja();
    m_debounce.reset();
  }
}

void maintananceAlarm(void) {
  m_maintanance.detach();
  upravljanjePistom->maintananceAlarm();
  m_maintanance.attach(&maintananceAlarm, 10s);
}

int main() {
  while (true) {

    m_debounce.start();
    m_smjerKretanjaAviona.rise(&promijeniSmjerKretanjaAviona);
    m_zabranjenoKoristenjePiste.rise(&zabranaKoristenja);
    m_zabranjenoKoristenjePiste.fall(&zabranaKoristenja);

    m_maintanance.attach(&maintananceAlarm, m_maintanaceSignalingTimeout);
    wait_us(10000000);
  }
}
