
#include <SoftwareSerial.h>
#include <ArduinoBlue.h>

const int SERIAL_BAUD = 115200;
const int HM10_BAUD = 9600;

ArduinoBlue bluetooth(Serial1);

void setup() {
  Serial.begin(SERIAL_BAUD);
  Serial1.begin(HM10_BAUD);
  while (!Serial || !Serial1);
  
  Serial.print("HM10 serial started at "); 
  Serial.println(HM10_BAUD);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  blink(3);
}

void loop() {
//  Serial1.listen();  // listen the HM10 port
  
  while (Serial1.available() > 0) {   // if HM10 sends something then read
    int button = bluetooth.getButton();
    Serial.print("Button: ");
    Serial.println(button);

    blink(button);
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
