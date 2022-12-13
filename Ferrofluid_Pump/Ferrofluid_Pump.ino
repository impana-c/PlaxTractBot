
const int motor= 10; //motor connected to digital pin 10

void setup(){
  pinMode(motor, OUTPUT); //sets the digital pin as output
}

void loop(){
  digitalWrite(motor,HIGH); 
  delay(3000000); //turns motor on for 5 seconds 
  Serial.println("Ferrofluid Pump Done!"); 
  //digitalWrite(motor,LOW);
  //delay(30000); //turns motor off for 30 seconds
}
