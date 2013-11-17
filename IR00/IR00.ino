// IR00 : program to test the reception of IR light by an IR Receiver
// see www.pcarion.com for more information
 
// Pin 2 is connected to the IR receiver
int pinIRReceiver = 2;

// this counter is incremented in the interrupt handler each time 
// there is a change of state of the input
int count = 0;

// this counter is used in the loop() to keep track
// of the last counter displayed.
int count0 = 0;

// the setup routine runs once when you press reset:
void setup() {  
  Serial.begin(9600);

  // the pin for the IR receiver is an INPUT
  pinMode(pinIRReceiver, INPUT);

  // we initialize the counter  
  count = 0;  
  count0 = 0;
    
  // attach interrupt 0 (pin 2 for uno)
  // see: http://arduino.cc/en/Reference/attachInterrupt 
  attachInterrupt(0, interruptHandler, CHANGE); 
  
  Serial.println("Starting....");
}

// the loop routine runs over and over again forever:
void loop() {
  if (count != count0) {
    Serial.println(count,DEC);
    count0 = count;
  }
}

void interruptHandler() {
  // value of the IR input.
  int value = digitalRead(pinIRReceiver);

  // we don't use the value for now.
  // we just increment a counter  
  count++;
}
