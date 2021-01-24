// IMPORTANT: ELEGOO_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Elegoo_TFTLCD.h FOR SETUP.
//Technical support:goodtft@163.com

#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

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

#define NUMOBJ 10

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

long centerx = tft.width() / 2;
long centery = tft.height() / 2;

// https://www.barth-dev.de/about-rgb565-and-how-to-convert-into-it/
// rgb 565 is required
long rgb(byte red, byte green, byte blue) {
  // return ((long)R << 16L) | ((long)G << 8L) | (long)B;
  return (((red & 0xf8)<<8) + ((green & 0xfc)<<3) + (blue>>3));
}


typedef struct
 {
     int x;
     int y;
     int r;
     float th;
     int c;
     int xinc = 1;
     int yinc=1;
     int type;
 }  object;

object objects[NUMOBJ];
long colors[8];

void setup(void) {
  Serial.begin(9600);
  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  randomSeed(analogRead(0));

  /*
  colors[0] = rgb(164,3,31);
  colors[1] = rgb(242,220,93);
  colors[2] = rgb(98,148,96);
  colors[3] = rgb(58,68,93);
  colors[4] = rgb(5,178,220);
*/
  colors[0] = rgb(255,0,0);
  colors[1] = rgb(0,255,0);
  colors[2] = rgb(0,0,255);
  colors[3] = rgb(255,0,255);
  colors[4] = rgb(0,255,255);



  for (int i=0; i < NUMOBJ; i++) {
    objects[i].x = random(0, tft.width());
    objects[i].y = random(0, tft.height() );
    objects[i].th = random(100) / 100;
    objects[i].c = colors[  i % 5 ] ;
    objects[i].xinc = random(5,10);
    objects[i].yinc = random(5,18);
    objects[i].r = max(objects[i].xinc, objects[i].yinc);
    objects[i].type = random(0,2);
  }

  tft.reset();

  uint16_t identifier = tft.readID();
  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
    identifier=0x9341;
    Serial.println(F("Found 0x9341 LCD driver"));
  }else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9341;

  }

  tft.begin(identifier);
  tft.fillScreen(BLUE);

}

int x=0;
int y=0;

long ranx;
long rany;
long c;


// inside the kaliedoscope
long x1 = centerx;
long y1 = centery+160;
long x2 = 0;
long y2 = centery-140;
long x3 = tft.width();
long y3 = centery-130;

float theta = 0;
int count = 0;

void loop(void) {

  //tft.fillTriangle(x1,y1,x2,y2,x3,y3, BLUE);

  theta = theta + .1;

  for (int i=0; i < NUMOBJ; i++) {
    //long _x = objects[i].r  * cos(objects[i].th);
    // long _y = objects[i].r  * sin(objects[i].th);
    objects[i].x = objects[i].x + objects[i].xinc;
    objects[i].y = objects[i].y + objects[i].yinc;
    if (objects[i].x > tft.width() || objects[i].x < 0) { objects[i].xinc = objects[i].xinc * -1; }
    if (objects[i].y > tft.height() || objects[i].y < 0) { objects[i].yinc = objects[i].yinc * -1; }

    //tft.fillCircle(objects[i].x + _x, objects[i].y + _y, 10,  objects[i].c);
    if (objects[i].type == 0) {
      tft.fillCircle(objects[i].x, objects[i].y, objects[i].r, objects[i].c);
    } else if (objects[i].type == 1) {
      tft.fillRect(objects[i].x, objects[i].y, objects[i].r, objects[i].r, objects[i].c);
    }

  }

  count++;
  if (count == 500) {
    for (int i=0; i < 300; i+=20) {
      tft.fillCircle( tft.width()/2, tft.height()/2, i, BLUE);
    }
  count = 0;
  }

  //delay(20);

  /*
  for (int i=0; i < 8; i++) {
    //long _x = objects[i].r  * cos(objects[i].th);
    //long _y = objects[i].r  * sin(objects[i].th);
    //tft.fillCircle(objects[i].x + _x,objects[i].y+ _y, 10,  BLUE);
    tft.fillCircle(objects[i].x, objects[i].y, 40, BLUE);

   // objects[i].th += .1;
  }
  */
}
