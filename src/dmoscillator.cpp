#include "dmoscillator.h"

/**
 * Constructor
 */
DMOscillator::DMOscillator(int pin, OscillationMode mode) {
  this->_pin = pin;
  this->setMode(mode);

  pinMode(this->_pin, OUTPUT);
  this->_intervalChecker = new DMTimer();
}

void DMOscillator::update() {

  //Disabled?
  if(!_isEnabled)
    return;

  unsigned long m = micros();

  if(_mode != OscillationMode::infinite)
  {

    //Time elapsed?
    if(_mode == OscillationMode::duration && m > _endTime)
    {
      _isEnabled = false;
      return;
    }

    //Count mode, and blink count over?
    if(_mode == OscillationMode::count && _onOffCounter >= _maxCount)
    {
      _isEnabled = false;
      return;
    }
  }

  //Check if we need to toggle state
  if(_intervalChecker->isTimeReached(m, this->_interval))
  {
    _pinState = !_pinState;
    digitalWrite(_pin, _pinState ? HIGH : LOW);
    if(!_pinState)
      _onOffCounter++;
  }
}

/**
 * Start oscillations for a given duration, with a period given in us
 */
void DMOscillator::oscillate(unsigned long period, unsigned long durationOrCount) {

  //oscillation end time:
  if(_mode == OscillationMode::duration)
    this->_endTime = micros() + durationOrCount;

  //oscillation period
  this->_interval = period/2;

  //max oscillations count
  this->_maxCount = durationOrCount;

  //oscillation counter
  this->_onOffCounter = 0;

  //enables the oscillator
  this->_isEnabled = true;

  //immediately starts oscillations
  this->_pinState = false;
  this->update();
}

void DMOscillator::stop() {
  this->_isEnabled = false;
}

/**
 * Starts oscillations at a given frequency in Hz, for a given duration.
 * 1Hz -> 1 on + 1 off per second
 */
void DMOscillator::oscillateHz(unsigned long frequency, unsigned long durationOrCount){
  this->oscillate(1000000 / (frequency), durationOrCount);
}

void DMOscillator::oscillate(unsigned long period) {
  oscillate(period, 0);
}

void DMOscillator::oscillateHz(unsigned long frequency) {
  oscillateHz(frequency, 0);
}
