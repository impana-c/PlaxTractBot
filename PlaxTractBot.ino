#include <Servo.h>

Servo servo;
int angle = 10;

int dustPin = 5; 
int ledPin = 12;  
int count = 0;  
int plasCount = 0;

const int motor = 10;

float voltsMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
float runningSum = 0;
float runningAvg = 0;
double first = 0;
bool on = true;
unsigned long myTime;

 
void setup(){
  servo.attach(8);
  servo.write(angle);
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
}
 
 
void loop(){
  myTime = millis();
  digitalWrite(ledPin,LOW);
  delayMicroseconds(280);
 
  voltsMeasured = analogRead(dustPin); 
 
  delayMicroseconds(40);
  digitalWrite(ledPin,HIGH);
  delayMicroseconds(9680);

  while (on == true) {
    if (count < 8){
      Serial.println("Stabilizing...");
      count++;
      }
    else{
      calcVoltage = voltsMeasured * (5.0 / 1024.0);
      dustDensity = 0.17 * calcVoltage - 0.1;
      if (count < 15){
        runningSum += dustDensity;
        runningAvg = runningSum/(count-7);
        Serial.println("Stabilizing...");
        count++;
        first = dustDensity;
      }
      else{
        Serial.print("Dust Density = ");
        Serial.println(dustDensity); //mg/m3
        if ((dustDensity < (runningAvg-0.05)) && (dustDensity < (first-0.03))){
          plasCount++;
          Serial.println("+ plastic!"); 
          }
        else{
          runningSum += dustDensity;
          runningAvg = runningSum/(count-7);
          count++;
          }    
        Serial.print("Running Average = ");
        Serial.println(runningAvg); 
        Serial.print("MicroPlastic Count = ");
        Serial.println(plasCount); 
        Serial.println("");   
        first = dustDensity;          
      }
    }
    
    if (((myTime<25010)&&(myTime>24990))||((myTime<50010)&&(myTime>49990))||((myTime<75010)&&(myTime>74990))||((myTime<100010)&&(myTime>99990))){
      on = false;
      for(angle = 10; angle < 180; angle++)  {                                  
        servo.write(angle);               
        delay(7);                   
      } 
      for(angle = 180; angle > 10; angle--)  {                                
        servo.write(angle);           
        delay(7);       
      } 
      for(angle = 10; angle < 180; angle++)  {                                  
        servo.write(angle);               
        delay(7);                   
      } 
      for(angle = 180; angle > 10; angle--)   {                                
        servo.write(angle);           
        delay(7);       
      } 
    } 
    else if (myTime>124990){
      on = false;
      if ((plasCount>0)&&(plasCount<=5)){
        digitalWrite(motor,HIGH); 
        delay(30000); 
        digitalWrite(motor,LOW);
        Serial.println("Done!"); 
        delay(60000); 
      }
      else if ((plasCount>5)&&(plasCount<=10)){
        digitalWrite(motor,HIGH); 
        delay(60000); 
        digitalWrite(motor,LOW);
        Serial.println("Done!"); 
        delay(60000); 
      }
      else if ((plasCount>10)&&(plasCount<=15)){
        digitalWrite(motor,HIGH); 
        delay(90000); 
        digitalWrite(motor,LOW);
        Serial.println("Done!"); 
        delay(60000);
      }
      else if (plasCount>15){
        digitalWrite(motor,HIGH); 
        delay(120000); 
        digitalWrite(motor,LOW);
        Serial.println("Done!"); 
        delay(60000);
      }
      else {
        Serial.println("Done!"); 
      }
    }
    else {
      on = true;
    }
    
}
