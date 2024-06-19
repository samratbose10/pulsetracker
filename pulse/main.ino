#include <PulseSensorPlayground.h>
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST);
const int PulseWire = 0;
const int LED = LED_BUILTIN;
int Threshold = 550;

PulseSensorPlayground pulseSensor;

void draw(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(0, 22, "BPM: ");
  u8g.setPrintPos(50, 22);
  u8g.print(pulseSensor.getBeatsPerMinute());
}

void setup() {
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED);
  pulseSensor.setThreshold(Threshold);

  if (pulseSensor.begin()) {
    // Optional: 
    // Serial.println("PulseSensor object created!");
  }

  u8g.setColorIndex(1); // pixel on
  pinMode(8, OUTPUT);
}

void loop() {
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while (u8g.nextPage());

  // Check for heartbeat
  if (pulseSensor.sawStartOfBeat()) {

    // Serial.println("♥  A HeartBeat Happened ! ");
  }

  delay(20);
}
