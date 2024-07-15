#include "SoftPWM.h"

void setup() {
  // Begin software PWM
  SoftPWMBegin();

  // Initalize RGB off
  SoftPWMSet(8, 0);
  SoftPWMSet(9, 0);
  SoftPWMSet(10, 0);
}

void loop() {
  /*
  *  An RGB color value is based on a 0-255 value for how bright each specific node should be.
  *  By mixing parts of each color, we can make a unique color. However, RGB doesn't make sense
  *  in most people's heads. Take a look at the link below for a color selector.
  *
  *  https://htmlcolorcodes.com/
  */

  // R diode
  SoftPWMSet(8, 0);

  // G diode
  SoftPWMSet(9, 255);

  // B diode
  SoftPWMSet(10, 0);
}
