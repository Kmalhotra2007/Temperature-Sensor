/*
  FILE          : assignment_3_compiling_program().ino
  PROJECT       : PROG8125 - Assignment #3
  PROGRAMMER    : Kunal Malhotra
  FIRST VERSION : 2016-07-06
  DESCRIPTION   :The following code accepts an analog input of temperature, and depending on the temperature vvalu it blinks different colors through the RGB LED. If the Temperature 
                 is notwithin the required range a white light is turned On.
                Initially the Pin Numbers are declared, void setup consists of initialisation if pin number as well as LCD.
                The following code accepts the temperature value as an analog input.
                The function MappingTheSensorValue() maps the value to the required temperature value.
                The function AveragingTheValue()takes a sample of values and averages them so as to stabilise the temperature value.
                The function PrintingOnLCD(UsedSensorValue) displays the temperature value on the top right corner of the LCD with a degree sign at the end
                The function LedDependingOnTemperature(UsedSensorValue)print blinks different colors on the LED depending on the input temperature.
                Void loop () consists of functions with their parameters, it also depicts the flow of the program.At first the input valus are mapped to required values.
                second, the average of a particular number of input values is taken.Third,the value is printed on the top right corner of the LCD with a degree symbol.
                Fourth, The LED is blinked on the basis of the current input temperature.
                The Pin Number connection from LCD to Teensy are as follows-
                  * LCD RS pin to digital pin 12
                  * LCD Enable pin to digital pin 11
                  * LCD D4 pin to digital pin 5
                  * LCD D5 pin to digital pin 4
                  * LCD D6 pin to digital pin 3
                  * LCD D7 pin to digital pin 2
                  * LCD R/W pin to ground
                  * LCD VSS pin to ground
                  * LCD VCC pin to 5V
                  * 10K resistor:
                  * ends to +5V and ground
                  * wiper to LCD VO pin (pin 3)               
 */           
#include <LiquidCrystal.h>                                                                                   //Header file including the library of LCD
#define SAMPLESIZE 350                                                                                       // Setting value of SAMPLESIZE as 350(we are going to take 350 values of 
                                                                                                             // temperature for calculating the average
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);                                                                       //Declaring pin numbers for LCD
const int8_t AnalogPinNumber = 17;                                                                           //Pin Number for the Temperature Sensor
const int8_t RedPin = 23;                                                                                    //
const int8_t GreenPin = 22;                                                                                  //Pin Numbers for different Pins of RGB LED as constant as they are not
const int8_t BluePin = 20;                                                                                   //going to change
const int32_t BaudRate = 9600;                                                                               //Baud Rate for initialisation if Serial Port
const int32_t DelayForSerial = 2000;                                                                         // Delay Time Required to initialise the Serial Port
const int32_t DelayForLCD = 1000;                                                                            // Delay Time used for LCD's, this is done so that the LCD has some time
                                                                                                             //before it prints the temperature on the LCD
const int32_t FullSaturationFreequency = 255;                                                                // Defining the full saturation freequency for the 3colors on an RGB LED
const int32_t MinimumLEDFreequency = 0 ;                                                                     // Minimum freequency for different LED's in the RGB LED
const int32_t GreenForOrange =20 ;                                                                           // Setting the freequency of Green LED as  20 to mix and blink orange color
const int32_t GreenForYellow = 50;                                                                           //Setting the freequency of Green LED as  50 to mix and blink yellow color
float MappingSensorValue();                                                                                  //                         
float AveragingTheValue();                                                                                   //
void PrintingOnLCD(float ValueForLCD);                                                                       // 
void BlinkYellowColor();                                                                                     //Declaring Function Prototypes so that the compiler knows what to 
void BlinkOrangeColor();                                                                                     //expect in the program
void BlinkBlueColor();                                                                                       //
void BlinkRedColor();                                                                                        //
void BlinkWhiteColor();                                                                                      //
void LedDependingOnTemperature(float SensorValue);                                                           //
byte smiley[8] = {
B00000, B01010,
B00000,
B00000,
B10001,
B01110,
B00000,
B00000
};                                                                                                           // Declaring an array of numbers to succesfullt print smiley face on the LCD
void setup()
{
  Serial.begin(BaudRate);                                                                                    // Initialising the Serial Port
  delay(DelayForSerial);                                                                                     // Delay required for initialiseing of serial port
  lcd.begin(16, 2);                                                                                          // Initilisation of LCD
  lcd.print(char(0));                                                                                        // Initilisation of LCD for the smiley face
  pinMode(AnalogPinNumber, INPUT_PULLUP);                                                                    // Declaring Analog Pin Number as Input 
  lcd.createChar (0, smiley);                                                                                // Using this function to print smiley face on the LCD          
}
//
//FUNCTION    : BlinkOrangeColor
//DESCRIPTION :This function consists of the commands required to illuminate the Orange color by mixing of different colors in a RGB LED.
//              
//PARAMETERS  : This function does not has any parameters.
//
//RETURNS     : This Function is not returning any value.
void BlinkOrangeColor()
{
  analogWrite(RedPin, FullSaturationFreequency);                                                              // Assigning Red LED to 255 freequency
  analogWrite(GreenPin, GreenForOrange);                                                                      // Assigning Green LED to 20 freequency
  analogWrite(BluePin, MinimumLEDFreequency);                                                                 // The blue LED is turned off for this color
}
//
//FUNCTION    : BlinkYellowColor
//DESCRIPTION :This function consists of the commands required to illuminate the Yellow color by mixing of different colors in a RGB LED.
//              
//PARAMETERS  : This function does not has any parameters.
//
//RETURNS     : This Function is not returning any value.
void BlinkYellowColor()
{
  analogWrite(RedPin, FullSaturationFreequency);                                                              //Assigning Red LED to 255 freequency
  analogWrite(GreenPin, GreenForYellow);                                                                      //Assigning Green LED to 50 freequency
  analogWrite(BluePin, MinimumLEDFreequency);                                                                 //The blue LED is turned off for this color
}
//
//FUNCTION    : BlinkYellowColor
//DESCRIPTION :This function consists of the commands required to illuminate the Blue color by mixing of different colors in a RGB LED.
//              
//PARAMETERS  : This function does not has any parameters.
//
//RETURNS     : This Function is not returning any value.
void BlinkBlueColor()
{
  analogWrite(BluePin, FullSaturationFreequency);                                                             //Assigning Blue LED to 255 freequency
  analogWrite(RedPin, MinimumLEDFreequency);                                                                  //The red LED is turned off for this color
  analogWrite(GreenPin, MinimumLEDFreequency);                                                                //The green LED is turned off for this color
}
//
//FUNCTION    : BlinkRedColor
//DESCRIPTION :This function consists of the commands required to illuminate the Blue color by mixing of different colors in a RGB LED.
//              
//PARAMETERS  : This function does not has any parameters.
//
//RETURNS     : This Function is not returning any value.
void BlinkRedColor()
{
  analogWrite(RedPin, FullSaturationFreequency);                                                               //Assigning Red LED to 255 freequency
  analogWrite(BluePin, MinimumLEDFreequency);                                                                  //The blue LED is turned off for this color
  analogWrite(GreenPin, MinimumLEDFreequency);                                                                 //The green LED is turned off for this color
}
//
//FUNCTION    : BlinkWhiteColor
//DESCRIPTION :This function consists of the commands required to illuminate the White color by mixing of different colors in a RGB LED.
//              
//PARAMETERS  : This function does not has any parameters.
//
//RETURNS     : This Function is not returning any value.
void BlinkWhiteColor()
{
  analogWrite(RedPin, FullSaturationFreequency);                                                               //Assigning Red LED to 255 freequency                                                                                   
  analogWrite(GreenPin, FullSaturationFreequency);                                                             //Assigning Green LED to 255 freequency
  analogWrite(BluePin, FullSaturationFreequency);                                                              //Assigning Blue LED to 255 freequency
}
//
//FUNCTION    : LedDependingOnTemperature
//DESCRIPTION :This function is used to blink different colors on a RGB LED depending on the temperature read by the analog input.It uses if and else if conditional statements
//              for making decesions and blinking LED's          
//              
//PARAMETERS  : float sensor value - it consists of the temperature read by the sensor
//
//RETURNS     : This Function is not returning any value.
void LedDependingOnTemperature(float SensorValue)
{
  if ((SensorValue >= -15.00) && (SensorValue <= 5.0))                                                        //Checks if the Sensor value is between -15 to 5
  {
    BlinkBlueColor();                                                                                         //If the condition is satisfied, this function is called to turn on blue color
  }
  else if ((SensorValue >= 5.1) && (SensorValue <= 15.0))                                                     //Checks if the Sensor value is between 5.1 to 15
  {
    BlinkYellowColor();                                                                                       //If the condition is satisfied, this function is called to turn on yellow color
  }
  else if ((SensorValue >= 15.1) && (SensorValue <= 25.00))                                                   //Checks if the Sensor value is between 15.1 to 25
  {
    BlinkOrangeColor();                                                                                       //If the condition is satisfied, this function is called to turn on orange color                                                                                   
  }
  else if ((SensorValue >= 25.1) && (SensorValue <= 150.00))                                                  //Checks if the Sensor value is between 25.1 to 150
  {
    BlinkRedColor();                                                                                          //If the condition is satisfied, this function is called to turn on red color
  }
  else if ((SensorValue >= -40) && (SensorValue <= -14.99))                                                   //Checks if the Sensor value is between -40 to -14.99
  {
    BlinkWhiteColor();                                                                                        //If the condition is satisfied, this function is called to turn on white color
  }
}
//
//FUNCTION    : PrintingOnLCD
//DESCRIPTION :This function sets the cursor positions and prints the temperature on the rightmost corner of the LCD. The first line consists of the temperature in Celsius scale
//             and the second line consists of the temperature in farenheit scale.
//              
//PARAMETERS  : float ValueForLCD - it consists of the value that is going to be printed on the LCD
//
//RETURNS     : This Function is not returning any value.
void PrintingOnLCD(float ValueForLCD)
{
  lcd.setCursor (9, 0);                                                                                       // The cursor is set to the 10th place in first row
  lcd.printf( "%5.2f%cC  ", ValueForLCD, (char)223);                                                          // Prints the temperature value in celsius upto 2 decimal places along with
                                                                                                              // a degree sign in the end.
  delay(DelayForLCD);                                                                                         // a delay of 1000 seconds is provided so that the LCD is initialised 
                                                                                                              //properly
  lcd.setCursor (9, 1);                                                                                       //The cursor is set to the 10th place in second row
  lcd.printf( "%5.2f%cF  ", (ValueForLCD *1.8)+32  , (char)223);                                              // The temperature is printed in Faranheit at the right mst corer of second
                                                                                                              //line with a degree sign in the end.
  delay(DelayForLCD);                                                                                         //a delay of 1000 seconds is provided so that the LCD is initialised 
                                                                                                              //properly
 Serial.printf("The Temperature is %.2f celcius or %.2f Farenheit \n",ValueForLCD , ((ValueForLCD *1.8)+32)); //Printing the Celsius and Farenheit value on the Serial Port                                                                                                              
}
//
//FUNCTION    : MappingSensorValue
//DESCRIPTION :This function converts the value received from the analog input to an actual understandable value.In short this function is used to map the input value.
//             After the input value has been mapped, mathematical functions are performed so as to convert the value to current required temperature value..
//              
//PARAMETERS  : This function has no parameters
//
//RETURNS     : CurrentSensorValue - This value is the final current value that is obtained from the sensor.This value is being used by other function to further calculate the average
//                                   of a particular number of temperature samples.
float MappingSensorValue()
{
  float CurrentSensorValue;                                                                                  //Declaring a cariable of float type, it stores the analog input value
  CurrentSensorValue = (float)analogRead(AnalogPinNumber);                                                   //Input value being sored in CurrentSensorValue
  CurrentSensorValue = (CurrentSensorValue * 3.3) / 1024.0;                                                  //  
  CurrentSensorValue = CurrentSensorValue - .5;                                                              // Mathematical Functions performed to obtain the required temperature value
  CurrentSensorValue = CurrentSensorValue / 0.01;                                                            //
  return CurrentSensorValue;                                                                                 // returning CurrentSensorValue to the function
}
//
//FUNCTION    : AveragingTheValue()
//DESCRIPTION :This function converts takes 350 input values and averages them , this way we get a stable temperature value. Withough this function the input temperature value.
//             would have been bouncing really fast from one value to another.
//             After the input value has been mapped, mathematical functions are performed so as to convert the value to current required temperature value..
//              
//PARAMETERS  : This function has no parameters
//
//RETURNS     : Average - This value is the the average of 350 samples of temperature. Based on this value LED's of different colors are being illuminated.
float AveragingTheValue()
{
  float sum = 0 ;                                                                                             //Initiating the variables to zero
  float Average = 0;                                                                                          //
  for (int16_t i = 0 ; i < SAMPLESIZE ; i++)                                                                  //For loop is used to collect 350 samples
  {
    sum = sum + MappingSensorValue() ;                                                                        //The sum of these values are stored in a variable called sum
  }
  Average = sum / SAMPLESIZE;                                                                                 // Average is calculated by dividind the sum of values to the total Sample
                                                                                                              //size
  return Average;                                                                                             //Returning the final average value to the fuction, its a float type value.
}
void loop()
{
  lcd.setCursor(0,1);                                                                                         //set cursor to bottom left second line
  lcd.print(char(0));                                                                                         //Prints smiley face at the start on the LCD
  float UsedSensorValue = 0;                                                                                  //Initialising the float type variable to zero
  UsedSensorValue = AveragingTheValue();                                                                      // Storing the returned value of AveragingTheValue() in UsedSensorValue
  PrintingOnLCD(UsedSensorValue);                                                                             //Calling these functions with UsedSensorValue as its parameter.
  LedDependingOnTemperature(UsedSensorValue);                                                                 //We are able to do this because the parameters for these functions are 
                                                                                                              //float types , same as UserSensorValue.
}
