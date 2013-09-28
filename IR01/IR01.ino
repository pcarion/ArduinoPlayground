// IR01 : program to test the reception of IR light by an IR Receiver
// Copyright (c) 2013 Pierre Carion
 
// Pin 13 is connected to a led
int pinLed = 13;

int pinLedIR = 12;

// Pin 2 is connected to the IR receiver
int pinIRReceiver = 2;

// time (in us) of last change of state
unsigned long time0; 

int isLedIRON;

// the setup routine runs once when you press reset:
void setup() {  
  Serial.begin(9600);
  
  // the pin for the led is an output
  // the pin for the IR receiver is an INPUT
  pinMode(pinLed, OUTPUT);     
  pinMode(pinLedIR, OUTPUT);
  pinMode(pinIRReceiver, INPUT);
  
  // we keep track of the starting time of the application
  time0 = micros();

  digitalWrite(pinLedIR, LOW);    
  isLedIRON = 0;
    
  // attach interrupt 0 (pin 2 for uno)
  // see: http://arduino.cc/en/Reference/attachInterrupt 
  attachInterrupt(0, interruptHandler, CHANGE); 
}

// the loop routine runs over and over again forever:
void loop() {
  // in the main loop, we simply blink the led
  digitalWrite(pinLed, HIGH);   
  delay(1000);               
  digitalWrite(pinLed, LOW);    
  delay(1000);     
  
  if (isLedIRON > 10) {
    unsigned long time = micros();
    
    if ((time - time0) >= 1000000L) {
      digitalWrite(pinLedIR, LOW);
      isLedIRON = 0;
    }
  }
}

void interruptHandler() {
  // value of the IR input.
  int value = digitalRead(pinIRReceiver);
  if (value == HIGH) {    
    time0 = micros();
    
    isLedIRON++;

    if (isLedIRON > 10) {
      digitalWrite(pinLedIR, HIGH);
   }
  }
}
