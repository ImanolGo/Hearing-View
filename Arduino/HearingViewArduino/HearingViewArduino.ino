/*
    Arduino code for Hearing View.
    Reads a digital input on pin 2 and writes it in the serial port
    The sensor input is monitored by contolling the digital output pin 13,
    connected and onboard LED
 
 */

// digital pin 2 has digital proximity sensor
int proximitySensor = 2;
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// digital pin 3 has digital output to control the chair's light
int lightControlPin = 4;

int lastButtonState = -1;

int inByte;// incoming serial byte

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
    } 
   
   
    else if(inByte== '1')
    {
      digitalWrite(lightControlPin, HIGH);  
    }  
  }
  
  // read the input pin:
  int buttonState = digitalRead(proximitySensor);
  // print out the state of the button:
  
  if(lastButtonState != buttonState) {
    
    // save the last sensor status
    lastButtonState = buttonState; 
   
   if (buttonState == 1) {     
      // turn LED on:    
      digitalWrite(led, HIGH);  
    } 
    else {
      // turn LED off:
      digitalWrite(led,LOW); 
    }

    // print out the value you read:
   Serial.print(buttonState);
   delay(1);        // delay in between reads for stability
  }
}
