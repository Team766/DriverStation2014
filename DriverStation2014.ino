// DriverStation: UnoJoy 'Black Box'
// the 2014 version has been programmed so that it is
// fully cross-compatible with the silver KOP joystick,
//incase of the regular OI failure. That is why one
//of the digital channels writes to an analog - 
//on the joystick mode the throttle lever is used.
#include "UnoJoy.h"

void setup() 
{ 
  setupPins();
  setupUnoJoy();
//  Serial.begin(9600);
} 

void loop() 
{ 
  dataForController_t controllerData = getControllerData();
  setControllerData(controllerData); 
 
}

void setupPins(void){
  // Set all the digital pins as inputs
  // also analog pins
  // with the pull-up enabled, except for the 
  // two serial line pins
  
  for (int i = 2; i <= 10; i++){
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  
  //these ports are used for the auton switch,
  //which has a LED on it
  pinMode( 11, OUTPUT);
  digitalWrite( 11, HIGH);
  pinMode( 13, OUTPUT);
  digitalWrite( 13, LOW);
}

dataForController_t getControllerData(void){
  
  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  dataForController_t controllerData = getBlankDataForController();
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins
  
  
  
  controllerData.triangleOn = !digitalRead(10); 
  controllerData.circleOn = !digitalRead(3); 
  controllerData.squareOn = !digitalRead(6);
  controllerData.crossOn = !digitalRead(7);
//  controllerData.dpadUpOn = !digitalRead(5); 
  controllerData.l1On = !digitalRead(2);
  controllerData.r3On = !digitalRead(5);
  
  controllerData.r1On = !digitalRead(8);
  controllerData.l3On = !digitalRead(9);
  
  controllerData.l2On = !digitalRead(12);
  
  controllerData.dpadUpOn = !digitalRead(A0);
  controllerData.dpadDownOn = !digitalRead(A1);
  controllerData.dpadLeftOn = !digitalRead(A2);
  controllerData.dpadRightOn = !digitalRead(A3);  
/*   
  
  Key for which name corresponds to which button
  
  
  controllerData.triangleOn //button 4
  controllerData.circleOn //button 3
  controllerData.squareOn //button 1
  controllerData.crossOn //button 2
  controllerData.dpadUpOn //POV hat
  controllerData.dpadDownOn
  controllerData.dpadLeftOn 
  controllerData.dpadRightOn 
  controllerData.l1On      //button 5
  controllerData.r1On      //button 6
  controllerData.selectOn  //button 9
  controllerData.startOn   //button 10
  controllerData.l2On      // button 7
  controllerdata.r2On      //button 8
  controllerData.l3On      //button 11
  controllerData.r3On      //button 12
  controllerData.homeOn //button 13 */
  
/*
  // Test here, the UnoJoy interface will not work
  // with this enabled
  for (int i = 2; i <= 10; i++){
    if(!digitalRead(i)){
    Serial.println("on:");
    Serial.print(i);
    }
//    digitalWrite(i, HIGH);
  }*/
  
  // Set the analog sticks
  //  Since analogRead(pin) returns a 10 bit value,
  //  we need to perform a bit shift operation to
  //  lose the 2 least significant bits and get an
  //  8 bit number that we can use  
 
  //For 2014 we only have 1 analog axis, which
  //is the throttle lever used as a switch
  float grip = 700;
  if(!digitalRead(4)){
    grip = 300;
  }
  controllerData.rightStickY = grip;
  
  
  
//  Serial.println(analogRead(A0));
  
  // And return the data!
  return controllerData;
}

