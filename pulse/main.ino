#include <PulseSensorPlayground.h>
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST);
const int PulseWire = 0;
const int LED = LED_BUILTIN;
int Threshold = 550;

PulseSensorPlayground pulseSensor;
#define LM35 A0
#define RED 7
#define GREEN 6

float lm_value;
int tempc;

void draw(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(0, 22, "BPM: ");
  u8g.setPrintPos(50, 22);
  u8g.print(pulseSensor.getBeatsPerMinute());
  
  
  u8g.drawStr(0, 40, "Temp");
  u8g.setPrintPos(50, 40);
  u8g.print(tempc);
  
 
  u8g.drawStr(80, 40, "C");
}

void setup() {
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED);
  pulseSensor.setThreshold(Threshold);

  if (pulseSensor.begin()) {
    // Serial.println("PulseSensor object created!");
  }

  u8g.setColorIndex(1); 
  pinMode(8, OUTPUT);
}

void loop() {
  
  u8g.firstPage();  
  do {
    draw();
  } while (u8g.nextPage());

 
  if (pulseSensor.sawStartOfBeat()) {
    
    // Serial.println("♥  A HeartBeat");
  }

  lm_value = analogRead(LM35);
  tempc = int((lm_value * 500) / 1023); 
  
  if (tempc > 60) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
  }
  else {
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
  }

  delay(20);
}

