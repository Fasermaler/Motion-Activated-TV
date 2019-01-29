#include "TM1637.h"
#include <IRremote.h>



// ====================================== USER DEFINED VARIABLES =====================================
// ULTRASOUND PINS
const int trigPin = 11;
const int echoPin = 10;
// INFRARED LED PINS
const int LEDPin = 6;
// THRESHOLD DISTANCE FOR DETECTION
const int detectionDistance = 20;
// LED DISPLAY PINS
const int clk_pin = 8;
const int dio_pin = 7;
// ENABLE DEBUG PRINTS
const bool debug_prints = true;
const bool LED_Display_print = true;

// IR SEND
#include <IRremote.h>
IRsend irsend;
// TM1637 initialization
TM1637 tm1637(clk_pin, dio_pin);

// ===================================== USER DEFINED FUNCTIONS ======================================
// This is the IRblast function that contains the full sequence of IR commands to send to the device
void IRblast() {
  buttonOn();
  delay(7000);
  buttonInput();
  delay(2000);
  buttonDown();
  delay(1000);
  buttonDown();
  delay(1000);
  buttonOk();
  delay(1000);
  buttonOk();
  delay(5000);
  buttonRight();
  delay(1000);
  buttonRight();
  delay(1000);
  buttonOk();
  delay(600000);
}

void buttonInput() {
  irsend.sendNEC(0x20DFD02F, 32);
  delay(40);
}
// On button IR burst
void buttonOn() {
  irsend.sendNEC(0x20DF10EF, 32); // Change this HEX value as necessary
  delay(40);
}

void buttonDown() {
  irsend.sendNEC(0x20DF827D
, 32);
  delay(40);
}

void buttonOk() {
  irsend.sendNEC(0x20DF22DD, 32);
  delay(40);
}

void buttonSwing() {
  irsend.sendNEC(0x807FC837, 32);
  delay(40);
}


void buttonRight() {
  irsend.sendNEC(0x20DF609F, 32);
  delay(40);
}
// ===================================================================================================




//#include <IRLibAll.h>
 
//IRsend mySender;

// ==================================================================================
// =========================== VARIABLE DEFINITIONS =================================
long duration;
int distance;
// Whether a guest is detected
bool guest_detected = false;

// ==================================================================================
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(LEDPin, OUTPUT); // Sets the LEDPin as an OUTPUT
  // INITIALIZE THE LED DISPLAY
  // BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
  // Create new distance variable and set it to the output of the ultrasound function
  int distanceV = ultrasound();
  
  // Guest Detection 
  distanceV < detectionDistance ? (guest_detected = true,IRblast()) : (guest_detected = false);

// ================================ DEBUG PRINTS ====================================
  if (debug_prints) {
    Serial.print(F("Distance: "));
    Serial.print(distanceV);
    guest_detected ? Serial.println(F(" - Guest detected")) : Serial.println("\t");
  }
  if (LED_Display_print) displayDistance(distanceV);
// ==================================================================================

  delay(200);

}

// ULTRASOUND FUNCTION
int ultrasound() {
    // CLEAR THE TRIG PIN
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // ULTRASOUND BURST
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // READS THE REBOUNDED BURST
  duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
  
  return distance > 450 ? 450 : duration*0.034/2;
}

// TM1637 DISPLAY FUNCTION
void displayDistance(int distanceV) {
  // CONVERTS distance int value into an array
  int distanceValueArray[4];
  
  for (char i = 3; i >= 0; distanceValueArray[i--] = distanceV % 10) distanceV /= 10;
  
  // DISPLAY PRINTS
  for(char i=0;i<=3;tm1637.display(i,distanceValueArray[i++]);
      }
