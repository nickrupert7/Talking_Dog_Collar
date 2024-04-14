#include "Adafruit_Soundboard.h"
#include <SoftwareSerial.h>

#define SFX_RX 5
#define SFX_TX 7

// Connect to the RST pin on the Sound Board
#define SFX_RST 9

SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);

// You can also monitor the ACT pin for when audio is playing!
// pass the software serial to Adafruit_soundboard, the second
// argument is the debug port (not used really) and the third
// arg is the reset pin
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);

void setup() { 
  Serial.begin(9600);
  while (!Serial || !ss);
  Serial.println("Adafruit Sound Board!");

//  if (!sfx.reset()) {
//    Serial.println("Failed to connect to sound board");
//    while (true);
//  }
   
  // set to FX board default baud rate
  ss.begin(9600); 

}

void loop() {
  // try sending a playback command
  sfx.playTrack((int) 0);
  delay(500);
  sfx.playTrack((int) 1);
  delay(500);
  sfx.playTrack((int) 2);
  delay(500);
  

  Serial.println ("test loop end");
  while (true);
}
