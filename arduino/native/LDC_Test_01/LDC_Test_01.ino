#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h" 

/*
#include "TouchScreen.h" // only when you want to use touch screen 
#include "bitmap_mono.h" // when you want to display a bitmap image from library
#include "bitmap_RGB.h" // when you want to display a bitmap image from library 
#include "Fonts/FreeSans9pt7b.h"    // when you want other fonts
#include "Fonts/FreeSans12pt7b.h" // when you want other fonts
#include "Fonts/FreeSerif12pt7b.h" // when you want other fonts
#include "FreeDefaultFonts.h" // when you want other fonts */
#include "SPI.h"  // using sdcard for display bitmap image
#include "SD.h"

#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  Serial.println("Start my LCD DEMO");

  // LCD   =   RD   WR   RS   CS   RST   X
  // UNO   =   A0   A1   A2   A3   A4   A5

  //(int CS=A3, int RS=A2, int WR=A1, int RD=A0, int RST=A4)
  // MCUFRIEND_kbv tft(A3, A2, A1, A0, A4);
  MCUFRIEND_kbv tft(A4, A3, A2, A1, A0);

  uint16_t ID = tft.readID();
  tft.begin(ID);

  tft.fillScreen(DARKGREEN);
  tft.drawLine(0, 0, 319, 479, WHITE);
    tft.drawLine(0, 479, 319, 0, WHITE);

}

void loop() {
  // put your main code here, to run repeatedly:

}
