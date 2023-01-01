#pragma once

#include "mbed.h"

class UpravljanjePistom {

public:
  UpravljanjePistom(PinName smjerLijevoDesno, PinName smjerDesnoLijevo,
                    PinName yellowStripeOne, PinName yellowStripeTwo,
                    PinName redStripeOne, PinName redStripeTwo);

  ~UpravljanjePistom();

  void init(void);

  void promijeniSmjerKretanjaAviona(void);

  void zabranaKoristenja(void);

  void maintananceAlarm(void);

private:
  DigitalOut *m_smjerLijevoDesno;
  DigitalOut *m_smjerDesnoLijevo;
  DigitalOut *m_yellowStripeOne;
  DigitalOut *m_yellowStripeTwo;
  DigitalOut *m_redStripeOne;
  DigitalOut *m_redStripeTwo;
  bool m_zabranjenoKoristenje = false;
};