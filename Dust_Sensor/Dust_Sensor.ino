int dustPin = 5; 
int ledPin = 12;  
int count = 0;  
int plasCount = 0;
 
float voltsMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
float runningSum = 0;
float runningAvg = 0;
double first = 0;
 
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
}
 
 
void loop()
{
  digitalWrite(ledPin,LOW); // power on the LED
  delayMicroseconds(280);
 
  voltsMeasured = analogRead(dustPin); 
 
  delayMicroseconds(40);
  digitalWrite(ledPin,HIGH);
  delayMicroseconds(9680);

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
    delay(1000);
  }
}
