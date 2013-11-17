// IR01 : program to test the reception of IR light by an IR Receiver
// see www.pcarion.com for more information
 
// Pin 13 is connected to a led
int pinLed = 13;

// Pin 2 is connected to the IR receiver
int pinIRReceiver = 2;

// the setup routine runs once when you press reset:
void setup() {  
  // the pin for the led is an output
  pinMode(pinLed, OUTPUT);     

  // the pin for the IR receiver is an INPUT
  pinMode(pinIRReceiver, INPUT);
  
  digitalWrite(pinLed, LOW);

  // attach interrupt 0 (pin 2 for uno)
  // see: http://arduino.cc/en/Reference/attachInterrupt 
  attachInterrupt(0, interruptHandler, CHANGE); 
}

// the loop routine runs over and over again forever:
void loop() {
}

void interruptHandler() {
  // value of the IR input.
  int value = digitalRead(pinIRReceiver);
  digitalWrite(pinLed, (value == HIGH) ? LOW : HIGH);
}
