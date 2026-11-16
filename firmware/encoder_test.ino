
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_DRV2605.h>

// --------------------------------------------------
// PINS
// --------------------------------------------------

#define SDA_PIN 12
#define SCL_PIN 11
#define EN_PIN 21

#define PRESS_EFFECT 24
#define RELEASE_EFFECT 26

// AS5601 I2C address
#define AS5601_ADDRESS 0x36

// AS5601 registers
#define RAW_ANGLE_REG 0x0C
#define MAGNITUDE_REG 0x1B
#define STATUS_REG 0x0B

// Push threshold
#define PUSH_THRESHOLD 1800

// --------------------------------------------------
// HARDWARE
// --------------------------------------------------

Adafruit_DRV2605 haptic;

// --------------------------------------------------
// PUSH STATE
// --------------------------------------------------

bool pushState = false;

// --------------------------------------------------
// AS5601
// --------------------------------------------------

uint16_t readAS5601(uint8_t reg) {
  Wire.beginTransmission(AS5601_ADDRESS);
  Wire.write(reg);

  if (Wire.endTransmission(false) != 0) {
    return 0xFFFF;
  }

  if (Wire.requestFrom(AS5601_ADDRESS, (uint8_t)2) != 2) {
    return 0xFFFF;
  }

  uint16_t value = Wire.read();
  value = (value << 8) | Wire.read();

  return value;
}

void readEncoder() {
  uint16_t rawAngle = readAS5601(RAW_ANGLE_REG);
  uint16_t magnitude = readAS5601(MAGNITUDE_REG);

  if (rawAngle == 0xFFFF || magnitude == 0xFFFF) {
    Serial.println("AS5601 communication error!");
    return;
  }

  rawAngle &= 0x0FFF;
  magnitude &= 0x0FFF;

  float angle = rawAngle * (360.0f / 4096.0f);

  // Magnitude-based push detection
  if (!pushState && magnitude > PUSH_THRESHOLD) {
    pushState = true;

    Serial.println("PUSH: PRESSED");
    playHaptic(PRESS_EFFECT);
  }
  else if (pushState && magnitude < PUSH_THRESHOLD) {
    pushState = false;

    Serial.println("PUSH: RELEASED");
    playHaptic(RELEASE_EFFECT);
  }

  Serial.printf(
    "Angle: %7.2f deg | Raw: %4u | Magnitude: %4u | Push: %s\n",
    angle,
    rawAngle,
    magnitude,
    pushState ? "PRESSED" : "RELEASED"
  );
}

// --------------------------------------------------
// HAPTICS
// --------------------------------------------------

void playHaptic(uint8_t effect) {
  haptic.setWaveform(0, effect);
  haptic.setWaveform(1, 0);
  haptic.go();
}

// --------------------------------------------------
// SETUP
// --------------------------------------------------

void setup() {
  Serial.begin(115200);

  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH);

  // I2C
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(100000);

  Serial.println();
  Serial.println("AS5601 Encoder Test");
  Serial.println("------------------------------");

  // DRV2605
  if (!haptic.begin()) {
    Serial.println("DRV2605 not detected!");
    while (1) delay(10);
  }

  haptic.useLRA();
  haptic.selectLibrary(6);
  haptic.setMode(DRV2605_MODE_INTTRIG);

  Serial.println("DRV2605 ready!");

  // Check AS5601
  Wire.beginTransmission(AS5601_ADDRESS);

  if (Wire.endTransmission() != 0) {
    Serial.println("AS5601 not detected!");
  } else {
    Serial.println("AS5601 ready!");
  }

  Serial.println("------------------------------");
  Serial.println("Angle | Raw | Magnitude | Push");
  Serial.println();
}

// --------------------------------------------------
// MAIN LOOP
// --------------------------------------------------

void loop() {
  static unsigned long lastReadTime = 0;

  if (millis() - lastReadTime >= 50) {
    lastReadTime = millis();
    readEncoder();
  }
}
