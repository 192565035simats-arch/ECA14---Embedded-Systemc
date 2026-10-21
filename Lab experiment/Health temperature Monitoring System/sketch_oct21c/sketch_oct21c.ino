
#include <Wire.h>

const byte LM75_ADDRESS = 0x48;
const byte PULSE_PIN = 8;

const unsigned long TEMP_INTERVAL = 1000;
const unsigned long BPM_INTERVAL = 5000;

unsigned long lastTempTime = 0;
unsigned long lastBpmTime = 0;

unsigned long pulseCount = 0;
int previousPulseState = LOW;

float readTemperature() {
  Wire.beginTransmission(LM75_ADDRESS);
  Wire.write(0x00);  // Temperature register

  if (Wire.endTransmission(false) != 0) {
    return -999.0;
  }

  if (Wire.requestFrom(LM75_ADDRESS, (byte)2) != 2) {
    return -999.0;
  }

  int msb = Wire.read();
  int lsb = Wire.read();

  int16_t raw = (int16_t)((msb << 8) | lsb);

  // LM75 temperature register: signed value / 256
  return raw / 256.0;
}

void setup() {
  pinMode(PULSE_PIN, INPUT);

  Wire.begin();
  Serial.begin(9600);

  Serial.println("Temperature and Pulse Monitor");
  Serial.println("System started");
}

void loop() {
  unsigned long now = millis();

  // Count each LOW-to-HIGH pulse transition
  int currentPulseState = digitalRead(PULSE_PIN);

  if (currentPulseState == HIGH &&
      previousPulseState == LOW) {
    pulseCount++;
  }

  previousPulseState = currentPulseState;

  // Display temperature every second
  if (now - lastTempTime >= TEMP_INTERVAL) {
    lastTempTime = now;

    float temperature = readTemperature();

    if (temperature != -999.0) {
      Serial.print("Temperature: ");
      Serial.print(temperature, 1);
      Serial.println(" C");
    } else {
      Serial.println("LM75AD not detected at 0x48");
    }
  }

  // Calculate BPM every five seconds
  if (now - lastBpmTime >= BPM_INTERVAL) {
    float elapsedSeconds =
        (now - lastBpmTime) / 1000.0;

    float bpm = pulseCount * 60.0 / elapsedSeconds;

    Serial.print("Pulse Rate: ");
    Serial.print(bpm, 0);
    Serial.println(" BPM");

    pulseCount = 0;
    lastBpmTime = now;
  }
}

