#ifndef DMOSCILLATOR_H
#define DMOSCILLATOR_H

#include "Arduino.h"
#include <dmtimer.h>

enum OscillationMode {
  duration,  // basé sur une durée de clignotement
  count,     // basé sur un nombre d'alternances
  infinite   // aucune condition d'arrêt
};

class DMOscillator {
private: //private members
  int _pin = 0;
  bool _isEnabled = false;
  unsigned long _interval = 0;
  unsigned long _endTime  = 0;
  unsigned long _maxCount = 0;
  unsigned long _onOffCounter = 0;
  bool _pinState = false;

  OscillationMode _mode;

  DMTimer* _intervalChecker;

public: //public members
  //DMOscillator constructor
  DMOscillator(int pin, OscillationMode mode);
  void setMode(OscillationMode mode) { this->_mode = mode; }
  void update();
  void stop();
  void oscillate(unsigned long period, unsigned long durationOrCount);
  void oscillateHz(unsigned long frequency, unsigned long durationOrCount);

  //for infinite mode, no need to pass another argument
  void oscillate(unsigned long period);
  void oscillateHz(unsigned long frequency);

};

#endif //DMOSCILLATOR_H
