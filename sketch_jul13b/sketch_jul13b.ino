/*
 * To run this code, plug the Arduino board into the computer using the 
 * communication cable. Go to 'Tools', then 'Board' and select 'Arduino Uno'.
 * Then, go to 'Tools', then 'Port' and select the highlighted port. If there 
 * are more than one, try one then try the other!
 * 
 * Click the checkmark to compile and check if there is any notation/typesetting
 * errors. Click the right arrow to upload the code to the board. 
 */


#include <avr/wdt.h> //imports main files for driving features and turning features.
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.cpp"

//#include "DeviceDriverSet_xxx0.cpp"

DeviceDriverSet_Motor AppMotor; //creates a Motor object
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
int b = 150;//creates a minimum for the right value(good)
int c = 300;//creates a minimum for the center value
int z = 400;//creates minimum for left value
int s = 60;//speed variable

void setup() {
    AppMotor.DeviceDriverSet_Motor_Init(); //internal code to initialize the motors. 
    delay(2000);
    
     
    Serial.begin(9600); //standard rate of communication from Arduino Board to computer.
}


void loop() {
  
    rightValue = analogRead(rightSensor); //stores the right sensor reading in the integer variable rightValue
  
    //black is greater than 250
    leftValue = analogRead(leftSensor); //stores the left sensor reading in the integer variable rightValue
    middleValue = analogRead(middleSensor); //stores the center sensor reading in the integer variable rightValue
    delay(20); //Delay the read miniscule amounts for more accurate move movements

    if(middleValue >= c){
    
      if(leftValue >= z &&rightValue > b){
        ApplicationFunctionSet_SmartRobotCarMotionControl(0,s/2); //if all black move forward
      }
      else if(leftValue >= z && rightValue < b){
        ApplicationFunctionSet_SmartRobotCarMotionControl(2,s); // if mid and left are black go left forward
      }
      else if(rightValue >= z && leftValue < b){
        ApplicationFunctionSet_SmartRobotCarMotionControl(3,s); //if mid and right are black then go right forward
      }
      else{
        ApplicationFunctionSet_SmartRobotCarMotionControl(0,s/2);//if only middle is on black go forward
      }
    }
    else{
      if(leftValue >= z && rightValue < b){
      
        ApplicationFunctionSet_SmartRobotCarMotionControl(2,s);// if only left is black go left
        rightValue = analogRead(rightSensor); //stores the right sensor reading in the integer variable rightValue
        leftValue = analogRead(leftSensor); //stores the left sensor reading in the integer variable rightValue
        middleValue = analogRead(middleSensor); //stores the center sensor reading in the integer variable rightValue
  
      
      
      } 
      else if(rightValue >= b && leftValue < z){
        
        ApplicationFunctionSet_SmartRobotCarMotionControl(3,s); //if only right is black then go right
        rightValue = analogRead(rightSensor); //stores the right sensor reading in the integer variable rightValue
  
      
        leftValue = analogRead(leftSensor); //stores the left sensor reading in the integer variable rightValue
        middleValue = analogRead(middleSensor); //stores the center sensor reading in the integer variable rightValue
  
      
      }
      else{
      
     
        ApplicationFunctionSet_SmartRobotCarMotionControl(1,s/2);
        delay(50);    //if all are white then go backwards with a bit of delay to allow to go backwards a bit
        rightValue = analogRead(rightSensor); //stores the right sensor reading in the integer variable rightValue
  
      
        leftValue = analogRead(leftSensor); //stores the left sensor reading in the integer variable rightValue
        middleValue = analogRead(middleSensor); //stores the center sensor reading in the integer variable rightValue
  
  
     
      }
    }
  

    Serial.print("R:"); //Will print out the numeric value of the color sensed by the right sensor 
    Serial.println(rightValue);
  
 

    //How does serial print work? 
    Serial.print("C:");
    Serial.print(middleValue); //this line of code will display the middle sensor's data value. 
    Serial.print('\t');
    Serial.print("L:"); //this line of code will add a space between printed data.
    Serial.println(leftValue); //notice the ln? This will display the right sensor's data value and then start the next printed info on the line below. 
    delay(100); // adds a delay between each line of data printed
}
