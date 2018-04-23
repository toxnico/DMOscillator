/*
 * This example shows how to make the integrated led
 * blink 3 times fast every second.
 * It illustrate the use of DMTimer coupled with DMOscillator.
 * Tick tick tick!....Tick tick tick!....Tick tick tick!

 * Nico
 */

#include <dmtimer.h>
#include <dmoscillator.h>

DMTimer *t = NULL;
DMOscillator *osc = NULL;

void setup(){
  //configure the timer to trigger every second
  t = new DMTimer(1000000);
  //configure the pin oscillator on pin 13
  osc = new DMOscillator(13, OscillationMode::count);
}

void loop(){

  //every second...
  if(t->isTimeReached())
    osc->oscillateHz(5, 3); //blink 3 times at 5Hz

  //update the oscillator at every loop
  osc->update();
}
