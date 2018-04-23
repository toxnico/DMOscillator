# DMTimer
An Arduino pin oscillator, based on micros().

It generates a square signal on the selected pin.

Can genarate signal for a limited duration, a limited number of pulses, or infinitely.

The simplest use could be:
```cpp
void setup(){
  /*
   * OscillationMode can be one of [duration, count, infinite]
   * In infinite mode, just pass the frequency.
   * In other modes, pass either the duration in us, or oscillation count as 2nd argument of oscillateHz()
   */
  osc = new DMOscillator(13, OscillationMode::infinite);

  osc->oscillateHz(5);
}

void loop(){
  //call update() at every loop
  osc->update();

}

```
