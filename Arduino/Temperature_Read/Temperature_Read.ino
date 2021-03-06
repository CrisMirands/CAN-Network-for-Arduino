int pin = A1;    // select the input pin for the potentiometer
float tempV, tempK, tempC;  // variable to store the value coming from the sensor

void setup() {
Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  tempV = analogRead(pin); 
  tempK = (tempV/1023)*500;
  tempC = tempK - 273.15;  
  Serial.println("Temperature K"); 
  Serial.println(tempK);
  Serial.println("Temperature C"); 
  Serial.print(tempC);
  Serial.println("\n");
  delay(1000);

}
