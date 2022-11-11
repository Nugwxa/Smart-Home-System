// See Demo of project here: https://youtu.be/TOCdedQDdGM

#include <DHT.h> // include the library of DHT11
#define Type DHT11 // define the connected analog


//Pins
int LightPin = A0;                         //Light sensor pin
int BuzzerPin = 2;                         // Buzzer pin
int RedLEDPin = 5;                         // Red LED pin
int BlueLEDPin = 6;                        // Blue LED pin
int WhiteLEDPin = 7;                       // White LED pin
int smokePin = A5;                         // Smoke Sensor pin
int UserButtonPin =  9;                    // Button to control buzzer pin
int DisableBuzzerButtonPin =  3;           // Button to control buzzer pin
int YellowLEDPin = 10;                     // Yellow LED pin
int GreenLEDPin = 11;                      // Green LED pin

int sensePin = 4; DHT HT(sensePin, Type);  // Temperature sensor(DHT11)pin

int MotionPin = 8;                         // Motion sensor pin (for PIR sensor)
int pirState = LOW;                        // At start, no motion detected


//Values
int MotionVal = 0;                         // variable for reading motion change
int LightValue;                            // Light value recieved from the light sensor
float tempC;                               // Temperature value recieved from the DHT11 sensor
int userButtonState = 0;                   // variable for reading the buttons status
int disableBuzzerButtonState = 0;          // variable for reading the buttons status
int SmokeValue;                            //variable for reading the smoke value
int SmokeThreshold = 225;                  // Smoke value that must be exceeded for a certain reaction

bool UserAtHome = true;                    // Determines if user is at home or not
bool BuzzerOn = false;                     // Turns buzzer on or off

void setup() {

Serial.begin(9600);

  HT.begin();
pinMode(BuzzerPin,OUTPUT);        // Declare Buzzer as an output
pinMode(RedLEDPin, OUTPUT);       // Declare Red LED as an output
pinMode(BlueLEDPin, OUTPUT);      // Declare Blue LED as an output
pinMode(WhiteLEDPin, OUTPUT);     // Declare White LED as an output
pinMode(YellowLEDPin, OUTPUT);    // Declare Yellow LED as an output
pinMode(GreenLEDPin, OUTPUT);     // Declare Green LED as an output
pinMode(MotionPin, INPUT);        // Declare Motion sensor as an input
pinMode(smokePin, INPUT);         // Declare smoke detector as an input
}

void loop() {

  
  //UserState control

  userButtonState = digitalRead(UserButtonPin);

  
  if (userButtonState == HIGH && UserAtHome == false) { // If the user presses the home button and UserAtHome = false, set UserAt Home to true and turn on the lights.
    
    digitalWrite(RedLEDPin, HIGH);
    digitalWrite(BlueLEDPin, HIGH);
    digitalWrite(WhiteLEDPin, HIGH);
    Serial.println("User is at home");
    delay(500);
    UserAtHome = true;
  }else if (userButtonState == HIGH && UserAtHome == true) { // If the user presses the home button and UserAtHome = true, set UserAt Home to false and turn off the lights.
    
    digitalWrite(RedLEDPin, LOW);
    digitalWrite(BlueLEDPin, LOW);
    digitalWrite(WhiteLEDPin, LOW);
    Serial.println("User is not at home");
    delay(500);
    UserAtHome = false;
  }

  //DisableBuzzerButtonState control

  disableBuzzerButtonState = digitalRead(DisableBuzzerButtonPin);

  
  if (disableBuzzerButtonState == HIGH) { // check if the button is pressed. If it is, turn off buzzer:
    
    BuzzerOn = false;
  }
  
  
  //Buzzer state
  if (BuzzerOn == true){ //if buzzer is triggered play sound and turn on yellow LED
    tone(2,600); 
    delay(500);
    noTone(2);
    delay(1);
    digitalWrite(YellowLEDPin, HIGH);
    digitalWrite(GreenLEDPin, LOW);
    } else if(BuzzerOn == false){ //stop playing sound and turn off yellow LED
      noTone;
      digitalWrite(YellowLEDPin, LOW);
    digitalWrite(GreenLEDPin, HIGH);
      }

  //Light Sensor
LightValue=analogRead(LightPin);     //Reads the Value of light.
//Serial.println("Light Value: ");
//Serial.println(LightValue);

if (UserAtHome == false && LightValue > 100){                //If user is not at home and the light value is greater than 100(Lights turned on) trigger buzzer
  BuzzerOn = true;
  //Notify User "Light detected in room!"
}



  //Temperature Sensor

 
 tempC = HT.readTemperature(); //Reads the temperature
 //Serial.print( " Temperature = " );
 //Serial.println( tempC, 1 );

 if(tempC>34){ //If the temperature is higher than 34 degrees celcius, trigger buzzer and notify user
  BuzzerOn = true;
  //Notify user "room temperature high";
  }

  //Motion Sensor
  MotionVal = digitalRead(MotionPin);  // read input value
  
  // If movement has been detected and the user is not at home, trigger the alarm and notify user.
  if (UserAtHome == false && MotionVal == HIGH)  
  {            
    //digitalWrite(RedLEDPin, HIGH);  // turn Red LED ON
    BuzzerOn = true;
    //Notify User
  
    if (pirState == LOW) 
  {
      Serial.println("Motion detected!"); // print on output change
      pirState = HIGH;
    }
  } 
  else 
  {
    //digitalWrite(RedLEDPin, LOW); // turn LED OFF
  
    if (pirState == HIGH)
  {
      Serial.println("Motion ended!");  // print on output change
      pirState = LOW;
    }
  }

  //Smoke Sensor
  SmokeValue = analogRead(smokePin); //Read value from smoke pin
  Serial.println("Smoke value: ");
  Serial.println(SmokeValue);
  if(SmokeValue>SmokeThreshold){ // If the detected smoke value is greater than the set threshold(225), Trigger buzzer and notify user
  BuzzerOn = true;
  //Notify user "Smoke Detected";
  }
  
}
