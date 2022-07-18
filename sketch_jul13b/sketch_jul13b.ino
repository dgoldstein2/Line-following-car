/* 
 * BOB-E
 * Team BOB
 * Code created and Tested by Dakota Goldstein and Carrie Dougherty
 * Started: July 13th 2022
 * Finished: July 16th 2022
 * Competition: July 17th 2022
 */


#include <avr/wdt.h> //imports main files for driving features and turning features.
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.cpp"

DeviceDriverSet_Motor AppMotor; //creates a Motor object
Application_xxx Application_SmartRobotCarxxx0; //creates another object

#define leftSensor A2//left sensor is defined as A2
#define middleSensor A1 //middle sensor is defined as A1
#define rightSensor A0//define the variable rightSensor to be pin A0

int rightValue; //initialize the integer variable rightValue
int leftValue; //initialize a value for left sensor
int middleValue; //initialize a value for middle sensor
int b = 150;//creates a minimum for the right value(good)
int c = 300;//creates a minimum for the center value
int z = 400;//creates minimum for left value
int s = 70;//speed variable

void setup() {
    AppMotor.DeviceDriverSet_Motor_Init(); //internal code to initialize the motors. 
    delay(2000);//delay when initializing the code
    Serial.begin(9600); //standard rate of communication from Arduino Board to computer.
}

void loop() {
  
    rightValue = analogRead(rightSensor); //stores the right sensor reading in the integer variable rightValue
    leftValue = analogRead(leftSensor); //stores the left sensor reading in the integer variable rightValue
    middleValue = analogRead(middleSensor); //stores the center sensor reading in the integer variable rightValue
    delay(20); //Delay the read miniscule amounts for more accurate move movements

    if(middleValue >= c){
      if(leftValue >= z &&rightValue > b){
        ApplicationFunctionSet_SmartRobotCarMotionControl(0,s/2); //if all black move forward
      }
      else if(leftValue >= z && rightValue < b){
        ApplicationFunctionSet_SmartRobotCarMotionControl(2,s/1.5); // if mid and left are black go left forward
        delay(50);//delay for each turn to turn more
      }
      else if(rightValue >= z && leftValue < b){
        ApplicationFunctionSet_SmartRobotCarMotionControl(3,s/1.5); //if mid and right are black then go right forward
        delay(50);//delay to lengthen turn
      }
      else{
        ApplicationFunctionSet_SmartRobotCarMotionControl(0,s/2);//if only middle is on black go forward
      }
    }
    else{
      if(leftValue >= z && rightValue < b){
        ApplicationFunctionSet_SmartRobotCarMotionControl(2,s/1.5);// if only left is black go left
        delay(30); //delay to lengthen turn
        rightValue = analogRead(rightSensor); //stores the right sensor reading in the integer variable rightValue
        leftValue = analogRead(leftSensor); //stores the left sensor reading in the integer variable rightValue
        middleValue = analogRead(middleSensor); //stores the center sensor reading in the integer variable rightValue
      } 
      else if(rightValue >= b && leftValue < z){
        ApplicationFunctionSet_SmartRobotCarMotionControl(3,s/1.5); //if only right is black then go right
        delay(30);//delay to lengthen turn
        rightValue = analogRead(rightSensor); //stores the right sensor reading in the integer variable rightValue
        leftValue = analogRead(leftSensor); //stores the left sensor reading in the integer variable rightValue
        middleValue = analogRead(middleSensor); //stores the center sensor reading in the integer variable rightValue
      }
      else{
        ApplicationFunctionSet_SmartRobotCarMotionControl(1,s/2);
        delay(15);   //if all are white then go backwards with a bit of delay to allow to go backwards a bit
        rightValue = analogRead(rightSensor); //stores the right sensor reading in the integer variable rightValue
        leftValue = analogRead(leftSensor); //stores the left sensor reading in the integer variable rightValue
        middleValue = analogRead(middleSensor); //stores the center sensor reading in the integer variable rightValue
      }
    }
  

    Serial.print("R:"); //Will print out the numeric value of the color sensed by the right sensor 
    Serial.println(rightValue);
    Serial.print("C:");
    Serial.print(middleValue); //this line of code will display the middle sensor's data value. 
    Serial.print('\t');
    Serial.print("L:"); //this line of code will add a space between printed data.
    Serial.println(leftValue); // This will display the left sensor's data value and then start the next printed info on the line below. 
    delay(100); // adds a delay between each line of data printed
}
