*
  MYBOTSHOP Dynamixel Servo Controllerboard (DSC)
  
  Product: https://www.mybotshop.de/Raspberry-Pi-Dynamixel-Servo-Controllerboard
  German Quick Start Guide: https://www.mybotshop.de/DSC
  English Quick Start Guide: https://www.mybotshop.de/DSC_EN

  Please read the manual carefully before using the DSC.

  modified 01.04.2018
  by MYBOTSHOP.DE
  
*/


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 0 as an output.
  pinMode(0, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(0, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}
