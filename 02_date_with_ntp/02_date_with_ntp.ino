#include<NTPClient.h>
#include<WiFi.h>
#include<WiFiUdp.h>

#include <GxEPD.h>
#include <GxGDEP015OC1/GxGDEP015OC1.cpp>    // 1.54" b/w
//#include <GxGDEH029A1/GxGDEH029A1.cpp>      // 2.9" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>
#include <Fonts/FreeSansBold12pt7b.h>

const char *ssid = "ssid";
const char *password = "password";

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP);

GxIO_Class io(SPI, SS, 22, 21);
GxEPD_Class display(io, 16, 4);

const char* name = "FreeSansBold12pt7b";
const GFXfont* f = &FreeSansBold12pt7b;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting ...");

  display.init(9600);
  display.setRotation(1);
  display.fillScreen(GxEPD_BLACK);
  display.setFont(f);
  display.update();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting to wifi ...");
  }

  timeClient.begin();
}

void loop() {
  showDateTime();
  delay(10000);
}

void showDateTime() {
  timeClient.update();

  String dateString = timeClient.getFormattedTime();
  Serial.println(dateString);

  uint16_t box_x = 40;
  uint16_t box_y = 40;
  uint16_t box_w = 110;
  uint16_t box_h = 24;
  uint16_t cursor_y = box_y + 20;

  display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
  display.setTextColor(GxEPD_WHITE);
  display.setCursor(box_x+4, cursor_y);
  display.print(dateString);
  display.updateWindow(box_x, box_y, box_w, box_h, true);
}
