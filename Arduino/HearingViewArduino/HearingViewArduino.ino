/*
    Arduino code for Hearing View.
    Reads a digital input on pin 2 and writes it in the serial port
    The sensor input is monitored by contolling the digital output pin 13,
    connected and onboard LED
 
 */
 
 #include <Bounce.h>

// digital pin 2 has digital proximity sensor
int proximitySensor = 2;
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// digital pin 5 has digital output to control the chair's light
int lightControlPin = 5;

//it records the last sensor state
int lastSensorState = -1;

int inByte;// incoming serial byte

const int bounceTime =  5;      // the time to check for debouncing
const int durationTime = 1000;     // the time to check the sensor to be in the same state
Bounce bouncer = Bounce( proximitySensor, bounceTime );


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the proximity sensor's pin an input:
  pinMode(proximitySensor, INPUT);
   // initialize the digital pin as an output.
  pinMode(led, OUTPUT); 
  // initialize the digital pin as an output.
  pinMode(lightControlPin, OUTPUT);  
  
  lastSensorState = bouncer.read();
}

// the loop routine runs over and over again forever:
void loop() {
 
   // if we get a valid byte, write to the light ontrol pin:
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    
    if(inByte== '0')
    {
      digitalWrite(lightControlPin, LOW);  
      digitalWrite(led, LOW);  
    } 
   
   
    else if(inByte== '1')
    {
      digitalWrite(lightControlPin, HIGH);  
      digitalWrite(led,HIGH); 
    }  
  }
  
  bouncer.update();
    // read the input pin:
  int sensorState = bouncer.read() ;
  
  // has our state changed for more the 1/2 a second?
  if ( lastSensorState != sensorState && bouncer.duration() > durationTime ) {

    lastSensorState = sensorState;
    
     // print out the value you read:
     Serial.print(sensorState);
     delay(1);        // delay in between reads for stability  
  }
}
