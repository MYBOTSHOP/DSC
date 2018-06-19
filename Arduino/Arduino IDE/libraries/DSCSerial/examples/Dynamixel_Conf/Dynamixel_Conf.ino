/*
  MYBOTSHOP Dynamixel Servo Controllerboard (DSC)
  
  Product: https://www.mybotshop.de/Raspberry-Pi-Dynamixel-Servo-Controllerboard
  German Quick Start Guide: https://www.mybotshop.de/DSC
  English Quick Start Guide: https://www.mybotshop.de/DSC_EN

  Please read the manual carfeully before using the DSC.

  modified 01.04.2018
  by MYBOTSHOP.DE
  
*/

#include <DynamixelSerial1.h>

void setup(){
Dynamixel.begin(1000000,0);  // Inicialize the servo at 1Mbps and Pin Control 0
delay(1000);
}

void loop(){
  
  Dynamixel.ledStatus(1,OFF);
  Dynamixel.move(1,random(200,800));  // Move the Servo with ID1 radomly from 200 to 800
  delay(1000);
  
  Dynamixel.setTempLimit(1,80);  // Set Max Temperature to 80 Celcius
  Dynamixel.setVoltageLimit(1,65,160);  // Set Operating Voltage from 6.5v to 16v
  Dynamixel.setMaxTorque(1,512);        // 50% of Torque
  Dynamixel.setSRL(1,2);                // Set the SRL to Return All

  Dynamixel.ledStatus(1,ON);           // Turn ON the LED
  
  delay(1000);
  
}
