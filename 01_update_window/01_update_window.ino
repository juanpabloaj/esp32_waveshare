
#include <GxEPD.h>
#include <GxGDEP015OC1/GxGDEP015OC1.h>    // 1.54" b/w
//#include <GxGDEH029A1/GxGDEH029A1.h>      // 2.9" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <Fonts/FreeSansBold12pt7b.h>

/*
BUSY  4
RST   21
DC    22
CS    5
CLK   18
DIN   23
GND   GND
3.3V  3.3V
*/

GxIO_Class io(SPI, SS, 22, 21);
GxEPD_Class display(io, 16, 4);

const char* name = "FreeSansBold12pt7b";
const GFXfont* f = &FreeSansBold12pt7b;

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(115200);
  Serial.println("Starting...");
  display.init(115200);
  display.setRotation(1);
  display.fillScreen(GxEPD_BLACK);
  display.setFont(f);
  display.update();
  delay(2000);
}

void loop() {
  Serial.println("loop ...");
  showRandomNumber();
  delay(1000);
}

void showRandomNumber() {
  String randomString = String(random(1, 60));

  uint16_t box_x = 40;
  uint16_t box_y = 10;
  uint16_t box_w = 120;
  uint16_t box_h = 100;
  uint16_t cursor_y = box_y + 16;

  display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
  display.setTextColor(GxEPD_WHITE);
  display.setCursor(box_x+4, cursor_y+38);
  display.print("rand: " + randomString);
  display.updateWindow(box_x, box_y, box_w, box_h, true);
}
