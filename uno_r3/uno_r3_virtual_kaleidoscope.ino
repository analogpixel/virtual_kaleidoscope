#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include <Adafruit_TFTLCD.h>

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

// calibration mins and max for raw data when touching edges of screen
// YOU CAN USE THIS SKETCH TO DETERMINE THE RAW X AND Y OF THE EDGES TO GET YOUR HIGHS AND LOWS FOR X AND Y
#define TS_MINX 210
#define TS_MINY 210
#define TS_MAXX 915
#define TS_MAXY 910

//SPI Communication
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

//Color Definitons
#define BLACK     0x0000
#define BLUE      0x001F
#define GREY      0xCE79
#define LIGHTGREY 0xDEDB
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define MINPRESSURE 1
#define MAXPRESSURE 1000
#define BOXSIZE 70


TouchScreen ts = TouchScreen(XP, YP, XM, YM, 364);
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

//Screen height without hidden pixel
double center_y= tft.height() /2;
//Centering the mid square
double center_x = tft.width() / 2;
//Space between squares
double padding = 10;

void setup() {
   Serial.begin(9600);

  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);

  //Background color
  tft.fillScreen(YELLOW);

}

int x=0;
int y=0;

long ranx;
long rany;
long c;

void loop() {
 
  tft.fillScreen(YELLOW);
  for (int i=0; i < 100; i++) { 
    ranx = random(tft.width() );
    rany = random(tft.height() );
    c = random(60000);

    tft.fillCircle(ranx,rany, 40,  c);
  }
  delay(60); 
}

