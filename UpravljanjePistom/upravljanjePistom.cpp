#include "mbed.h"
#include <upravljanjePistom.h>

UpravljanjePistom::UpravljanjePistom(PinName smjerLijevoDesno,
                                     PinName smjerDesnoLijevo,
                                     PinName yellowStripeOne,
                                     PinName yellowStripeTwo,
                                     PinName redStripeOne, PinName redStripeTwo)
    : m_smjerLijevoDesno(new DigitalOut(smjerLijevoDesno)),
      m_smjerDesnoLijevo(new DigitalOut(smjerDesnoLijevo)),
      m_yellowStripeOne(new DigitalOut(yellowStripeOne)),
      m_yellowStripeTwo(new DigitalOut(yellowStripeTwo)),
      m_redStripeOne(new DigitalOut(redStripeOne)),
      m_redStripeTwo(new DigitalOut(redStripeTwo)) {
  init();
}

void UpravljanjePistom::init() {
  m_redStripeOne->write(1);
  m_redStripeTwo->write(1);
  m_yellowStripeOne->write(1);
  m_yellowStripeTwo->write(1);
  m_smjerLijevoDesno->write(1);
}

void UpravljanjePistom::promijeniSmjerKretanjaAviona(void) {
  m_smjerLijevoDesno->write(!m_smjerLijevoDesno->read());
  m_smjerDesnoLijevo->write(!m_smjerDesnoLijevo->read());
}

void UpravljanjePistom::zabranaKoristenja(void) {
  if (m_zabranjenoKoristenje) {
    m_smjerLijevoDesno->write(1);
    m_smjerDesnoLijevo->write(0);
    m_yellowStripeOne->write(1);
    m_yellowStripeTwo->write(1);
    m_zabranjenoKoristenje = false;
    return;
  }

  m_smjerLijevoDesno->write(0);
  m_smjerDesnoLijevo->write(0);
  m_yellowStripeOne->write(0);
  m_yellowStripeTwo->write(0);
  m_zabranjenoKoristenje = true;
}

void UpravljanjePistom::maintananceAlarm(void) {
  for (int i = 4; i > 0; i--) {
    for (int j = 4; j > 0; j--) {
      wait_us(500000);
      m_smjerLijevoDesno->write(!m_smjerLijevoDesno->read());
      m_smjerDesnoLijevo->write(!m_smjerDesnoLijevo->read());
    }

    if (i > 0) {
      wait_us(3000000);
    }
  }
}