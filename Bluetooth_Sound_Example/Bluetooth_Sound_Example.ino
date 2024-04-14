
#include <SoftwareSerial.h>
#include <ArduinoBlue.h>
#include "Adafruit_Soundboard.h"

//#define DEBUG

#define SERIAL_BAUD 115200
#define BLUETOOTH_BAUD 9600
#define SFX_BAUD 9600

#define SFX_RX 5
#define SFX_TX 7
#define SFX_RST 9

ArduinoBlue bluetooth(Serial1);

SoftwareSerial sfx_serial = SoftwareSerial(SFX_TX, SFX_RX);
Adafruit_Soundboard sfx = Adafruit_Soundboard(&sfx_serial, NULL, SFX_RST);


void setup() {
#ifdef DEBUG
  Serial.begin(SERIAL_BAUD);
  while (!Serial);
#endif

  Serial1.begin(BLUETOOTH_BAUD);
  sfx_serial.begin(SFX_BAUD);
  while (!Serial1 || !sfx_serial);

#ifdef DEBUG
  Serial.print("HM10 serial started at "); 
  Serial.println(BLUETOOTH_BAUD);

  Serial.print("SFX serial started at ");
  Serial.println(SFX_BAUD);
#endif

  sfx.reset();
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  blink(5);

  uint8_t files = sfx.listFiles();
}

void loop() {
//  Serial1.listen();  // listen the HM10 port
  
  while (Serial1.available() > 0) {   // if HM10 sends something then read
    int button = bluetooth.getButton();

#ifdef DEBUG
    Serial.print("Button: ");
    Serial.println(button);
#endif

    int trackNumber = (int) button;

    digitalWrite(LED_BUILTIN, HIGH);
    sfx.playTrack(trackNumber);
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void blink(int times) {
  for (int i = 0; i < times + 1; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
}
