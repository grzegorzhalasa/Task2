#include <Wire.h>

#define LED_ON_L 0x06
#define LED_ON_H 0x07
#define LED_OFF_L 0x08
#define LED_OFF_H 0x09

#define PCA9633_ADDRESS 0x62 // I2C address of PCA9633

void setup() {
  Wire.begin(); // initialize I2C communication
  delay(100); // wait for the device to power up

  // enable auto-increment mode
  Wire.beginTransmission(PCA9633_ADDRESS);
  Wire.write(0x00);
  Wire.write(0xA0);
  Wire.endTransmission();
}

void loop() {
  rainbow(10); // delay 10ms between colors
}

void setLed(uint8_t led, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  // set the color of a single LED
  Wire.beginTransmission(PCA9633_ADDRESS);
  Wire.write(LED_ON_L + 4 * led);
  Wire.write(0);
  Wire.write(0);
  Wire.write(0);
  Wire.write(0);
  Wire.write(LED_OFF_L + 4 * led);
  Wire.write(r);
  Wire.write(g);
  Wire.write(b);
  Wire.write(w);
  Wire.endTransmission();
}

void rainbow(uint16_t delay_ms) {
  for (uint16_t i = 0; i < 256; i++) {
    uint8_t r, g, b, w;
    rainbowColor(i, &r, &g, &b, &w);
    setLed(0, r, g, b, w);
    delay(delay_ms);
  }
}

void rainbowColor(uint8_t value, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* w) {
  if (value < 85) {
    *r = value * 3;
    *g = 255 - value * 3;
    *b = 0;
  } else if (value < 170) {
    value -= 85;
    *r = 255 - value * 3;
    *g = 0;
    *b = value * 3;
  } else {
    value -= 170;
    *r = 0;
    *g = value * 3;
    *b = 255 - value * 3;
  }
  *w = 255; // white LED at full brightness
}
