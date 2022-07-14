/*
 * To run this code, plug the Arduino board into the computer using the 
 * communication cable. Go to 'Tools', then 'Board' and select 'Arduino Uno'.
 * Then, go to 'Tools', then 'Port' and select the highlighted port. If there 
 * are more than one, try one then try the other!
 * 
 * Click the checkmark to compile and check if there is any notation/typesetting
 * errors. Click the right arrow to upload the code to the board. 
 */


#include <avr/wdt.h>
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.cpp"

//#include "DeviceDriverSet_xxx0.cpp"

DeviceDriverSet_Motor AppMotor;
Application_xxx Application_SmartRobotCarxxx0;
  


/* 
This section defines the sensor pins for your car. 
 */
#define leftSensor A2//left sensor is defined as A2
#define middleSensor A1 //middle sensor is defined as A1
#define rightSensor A0//define the variable rightSensor to be pin A0

//the middle sensor is connected to pin A1; the left sensor is connected to port A2.

/*
This section creates variables that can be stored as integers. Remember 
  the values that are returned from the sensor ranges from 0-1023. 
  Integers!
 */
 
int rightValue; //initialize the integer variable rightValue
int leftValue; //initialize a value for left sensor
int middleValue; //initialize a value for middle sensor

void setup() {
    AppMotor.DeviceDriverSet_Motor_Init(); //internal code to initialize the motors. 
    delay(2000);
    
     
  Serial.begin(9600); //standard rate of communication from Arduino Board to computer.
}


void loop() {
  
  rightValue = analogRead(rightSensor); //stores the right sensor reading in the integer variable rightValue
  //black is greater than 650
  leftValue = analogRead(leftSensor);
  middleValue = analogRead(middleSensor);

  if (middleValue<650){
    ApplicationFunctionSet_SmartRobotCarMotionControl(1,50);
    }
    //back up if center is off tape
   else if (rightValue < 650 &&leftValue > 650){
    ApplicationFunctionSet_SmartRobotCarMotionControl(2,100);
   }
   else if (leftValue < 650 && rightValue > 650){
    ApplicationFunctionSet_SmartRobotCarMotionControl(3,100);
   }
   else {
    ApplicationFunctionSet_SmartRobotCarMotionControl(0,100);
    //drive forward
   }
   
/* 
  ApplicationFunctionSet_SmartRobotCarMotionControl(0,100);
  while (middleValue<750){
    ApplicationFunctionSet_SmartRobotCarMotionControl(1,50);
  }
  while(rightValue < 750){
    ApplicationFunctionSet_SmartRobotCarMotionControl(4,50);
   
  }
  while(leftValue <750){
    ApplicationFunctionSet_SmartRobotCarMotionControl(6,50);
  }
  while (middleValue<750){
    ApplicationFunctionSet_SmartRobotCarMotionControl(1,50);
  }
 */ 
  

/*
Open the Serial Monitor. Click 'Tools' above, then 'Serial Monitor'.
check
 */
  Serial.print("R:");
  Serial.println(rightValue);
  
 

  //How does serial print work? 
  Serial.print("C:");
  Serial.print(middleValue); //this line of code will display the middle sensor's data value. 
  Serial.print('\t');
   Serial.print("L:"); //this line of code will add a space between printed data.
  Serial.println(leftValue); //notice the ln? This will display the right sensor's data value and then start the next printed info on the line below. 
  delay(2000);
}
