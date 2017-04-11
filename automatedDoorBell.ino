/*
Analog input, analog output, serial output

Reads an analog input pin, maps the result to a range from 0 to 255
and uses the result to set the pulsewidth modulation (PWM) of an output pin.
Also prints the results to the serial monitor.

The circuit:
* potentiometer connected to analog pin 0.
Center pin of the potentiometer goes to the analog pin.
side pins of the potentiometer go to +5V and ground
* LED connected from digital pin 9 to ground

created 29 Dec. 2008
modified 9 Apr 2012
by Tom Igoe

This example code is in the public domain.

*/

// These constants won't change.  They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int doorPin = A2;

int sensorValue = 0;        // value read from the pot
int testValue = 0;
float prevVoltage = 0;
float voltage = 0;          // value read from the pot in volts
char rx_byte = 0;
unsigned long currentTime = 0;
unsigned long ringTime = 0;
int openDoorDelay = 0;

bool monitoring = true;
bool debug = false;
int monitoringNumber = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  if (monitoring == true) {
    Serial.begin(9600);
  }
  pinMode(doorPin, OUTPUT);
  digitalWrite(doorPin, LOW);
  Serial.println("All set up and ready to go !");
}

void printData() {
  if (debug == true) {
    Serial.print("Current Time : ");
    Serial.print(currentTime);
    Serial.print("\tVoltage: ");
    Serial.println(voltage);
  }
}

void setDoorOpening(int minDelay, int maxDelay) {
  openDoorDelay = random(minDelay, maxDelay);
  ringTime = millis();
  if (debug == true) {
    Serial.print("\tRing time : ");
  }
  Serial.println(ringTime);
  if (debug == true) {
    Serial.print("\tOpen door delay : ");
  }
  Serial.println(openDoorDelay); 
}

void openDoor() {
  if (debug == true) {
    Serial.print("\tRingtime : ");
    Serial.print(ringTime);
    Serial.print("\tdelay: ");
    Serial.println(openDoorDelay);
  }
  digitalWrite(doorPin, HIGH);
  Serial.println("Opening the door");
  currentTime = millis();
  while(millis() < currentTime + 1000) {}
  digitalWrite(doorPin, LOW);
  ringTime = 0;
  openDoorDelay = 0;
}

void loop() {
  
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the volts range:
  voltage = sensorValue * (5.0 / 1023.0);
  if (voltage > prevVoltage) {
    prevVoltage = voltage;
    if (debug == true) {
      Serial.print("Top Voltage: ");
    }
    if (monitoring == true) {
      Serial.println(prevVoltage);
    }
  }
  currentTime = millis();
  
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();       // get the character
    if (rx_byte == 'o' && ringTime == 0) {
      setDoorOpening(0, 1);
    } else if (rx_byte =='m') {
      Serial.println("Monitoring enabled. Send 'e' to stop monitoring");
      Serial.print("Monitoring Session Number : ");
      Serial.println(monitoringNumber);
      Serial.println(rx_byte);
      monitoring = true;
      monitoringNumber += 1;
    } else if (rx_byte == 'e') {
      monitoring = false;
      debug = false;
    } else if (rx_byte == 'd') {
      Serial.println("Debugging enabled. Send 'r' to stop monitoring");
      monitoring = true;
      debug = true;
    } else if (rx_byte == 'r') {
      debug = false;
    } else if (rx_byte == 'o') {
      monitoring = false;
      debug = false;
    }
  }
  
  printData();
  
  if (ringTime > 1 && millis() >= ringTime + openDoorDelay) {
    openDoor();
  }
  
  if (voltage > 0.9 && ringTime == 0) {
    Serial.println("Setting up opening timer");
    setDoorOpening(5000, 3000);
  }
  currentTime = millis();
  //while(millis() < currentTime + 1) {}
}



