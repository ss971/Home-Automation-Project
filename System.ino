#include <DHT11.h>
DHT11 dht11(5);

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 3;        

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int timer = 10000;  
long unsigned int lastHigh = 0;
long unsigned int tempStandard = 0;
boolean lockLow = true;
boolean takeLowTime;  

boolean movement = false;

int pirPin = 3;    //the digital pin connected to the PIR sensor's output
int ledPin = 7;
int buzzerPin = 13;

int debugCount = 0;

int enablePin = 2;
int Signal1 = 9;
int Signal2 = 10; 

#define anInput     A0                        //analog feed from MQ135

/////////////////////////////
//SETUP
void setup(){
  Serial.begin(9600);
  pinMode(enablePin, OUTPUT);
  pinMode(Signal1,OUTPUT);
  pinMode(Signal2,OUTPUT);
  pinMode(anInput,INPUT);                     //MQ135 analog feed set for input
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
  }

////////////////////////////
//LOOP
void loop() {
  //digitalWrite(enablePin,HIGH);
  //digitalWrite(Signal1,LOW);
  //digitalWrite(Signal2,HIGH);  
  int temperature = dht11.readTemperature();
    // Check the result of the reading.
    // If there's no error, print the temperature value.
    // If there's an error, print the appropriate error message.
  if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT) {
     Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C");
      if (temperature - tempStandard > 5)
      {
          digitalWrite(enablePin,HIGH);
          digitalWrite(Signal1,LOW);
          digitalWrite(Signal2,HIGH);
      }
      else
      {
        digitalWrite(enablePin,LOW);
      }
  } else {
      //Print error message based on the error code.
      Serial.println(DHT11::getErrorString(temperature));
  }

  if(digitalRead(pirPin) == HIGH) {
    //Serial.print("^");
    if (movement) {
      // nothing to do here
    } else {
        digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state         
        Serial.print("motion detected at "); 
        Serial.print(millis()/1000); 
        Serial.println(" sec"); 
        movement = true;
        //digitalWrite(buzzerPin, HIGH);
        Serial.print("\n");
    }
    lastHigh = millis();
    debugCount = 0;         
  } else {
    //Serial.print("v");
    if (movement) {
      // switch off if ran out of timer
      if (millis() - lastHigh > timer)
      {
        digitalWrite(ledPin,LOW);
        //digitalWrite(buzzerPin, LOW);
        Serial.print("motion ended at "); 
        Serial.print(millis()/1000); 
        Serial.println(" sec");
        movement = false;
        Serial.print("\n");
      } else {
        // if (++debugCount > 1000/50) {
        //  Serial.print("X ");
        //  debugCount = 0;
        //}
      } 
        //the led visualizes the sensors output pin state  
    } else {
      // nothing to do here

    }
         
  }
  int co2now[10];                               //int array for co2 readings
  int co2raw = 0;                               //int for raw value of co2
  int co2ppm = 0;                               //int for calculated ppm
  int zzz = 0;                                  //int for averaging
  int normalCO2 = 55;

  for (int x = 0;x<10;x++)  //samplpe co2 10x over 2 seconds
  {                   
    co2now[x]=analogRead(A0);
    delay(200);
  }

  for (int x = 0;x<10;x++)  //add samples together
  {                     
    zzz=zzz + co2now[x];  
  }
  
  co2ppm = zzz/10;                            //divide samples by 10
                  //get calculated ppm
  if (co2ppm > normalCO2)
  {
    digitalWrite(buzzerPin, HIGH);
  }
  else
  {
    digitalWrite(buzzerPin,LOW);
  }
  Serial.print("AirQuality=");
  Serial.print(co2ppm);  // prints the value read
  Serial.println(" PPM");
  delay(50);
}
