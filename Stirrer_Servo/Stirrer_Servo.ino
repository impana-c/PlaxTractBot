#include <Servo.h>
Servo servo;
int angle = 0;
void setup() {
  servo.attach(8);
  servo.write(angle);
}
void loop() 
{ 
 // scan from 0 to 180 degrees
  for(angle = 40; angle < 110; angle++)  
  {                                  
    servo.write(angle);               
    delay(4);                   
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 110; angle > 40; angle--)    
  {                                
    servo.write(angle);           
    delay(4);       
  } 
}
