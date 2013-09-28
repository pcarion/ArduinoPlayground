// IR01 : program to test the reception of IR light by an IR Receiver
// Copyright (c) 2013 Pierre Carion
 
// Pin 13 is connected to a led
int pinLed = 13;

// Pin 2 is connected to the IR receiver
int pinIRReceiver = 2;

// time (in us) of last change of state
unsigned long time0; 

// time since the start of the application
unsigned long timeStart; 

int isOver;

// storage of state durations
#define NB_TIME_SLICES 200
unsigned int timeSlices[NB_TIME_SLICES];
int indexSlice;

#define MAX_TIME_SLICE 60000

// time out at the end of the reception
#define TIMEOUT_END_SECONDS 20

// the setup routine runs once when you press reset:
void setup() {  
  Serial.begin(9600);
  
  // the pin for the led is an output
  // the pin for the IR receiver is an INPUT
  pinMode(pinLed, OUTPUT);     
  pinMode(pinIRReceiver, INPUT);
  
  // we keep track of the starting time of the application
  time0 = micros();
  
  timeStart = time0;
  
  // preparation to store durations
  indexSlice = 0;
  isOver = -1;
  
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
  
  if (isOver < 0) {
    unsigned long time = micros();
    
    unsigned int durationSinceStartOfApplication = (unsigned int) ((time - timeStart)/1000000);

    // we declare the end of the reception if
    // - we reach the end of the storage buffer
    // - we have at least 5 durations and we have not received any new change of state since TIMEOUT_END seconds
    if ((indexSlice >= NB_TIME_SLICES) || ((indexSlice > 5) && (durationSinceStartOfApplication > TIMEOUT_END_SECONDS))) {
      Serial.print("# nb time slices:");
      Serial.println(indexSlice,DEC);
      for(int i = 0; i < indexSlice ; i++) {
        Serial.println(timeSlices[i],DEC);
      }
      // we don't wanbt this list to be displayed multiple times
      isOver = 1;
    }
  }
}

void interruptHandler() {
  if (isOver < 0) {
    unsigned long time = micros();
    
    // value of the IR input. Not used in this sample
    int value = digitalRead(pinIRReceiver);
    
    unsigned long duration = (unsigned int) (time - time0);
    
    if (duration > MAX_TIME_SLICE) {
      duration = MAX_TIME_SLICE;
    }
    
    if (indexSlice < NB_TIME_SLICES) {
      timeSlices[indexSlice] = (int)duration;
      indexSlice++;
    }
    // we store the new time value
    time0 = time;
  }
}
