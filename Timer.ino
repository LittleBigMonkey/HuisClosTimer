//#include <ArduinoSTL.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


Adafruit_SSD1306 display(128, 64, &Wire, 4);

const int buttonPin = 8;
const int outputPin = 4;

int timer = 1200;

bool done = false;

void setup()
{
    Wire.begin(); //nano SDA-SCL A4-A5

    InitDisplay();

    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(outputPin, OUTPUT);
    digitalWrite(outputPin, LOW);

    print("%02d:%02d", timer / 600, timer / 10 % 60);
}

void InitDisplay()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextSize(4);
    display.setTextColor(WHITE, BLACK);
    display.setTextWrap(false);
}

void loop()
{
 
    if (timer > 0 && digitalRead(buttonPin) == LOW)
    {
        timer--;
        
        if (done) done = false; //reset
  
        if (timer % 10 == 0)
          print("%02d:%02d", timer / 600, timer / 10 % 60);

        if (random(100) < 30)
          display.ssd1306_command(SSD1306_DISPLAYOFF);
        else
          display.ssd1306_command(SSD1306_DISPLAYON);
        
        digitalWrite(outputPin, HIGH);
  
        delay(100);
    }
    else
    {
      if (!done)
      {
        display.ssd1306_command(SSD1306_DISPLAYOFF);
        digitalWrite(outputPin, LOW);

        done = true;
      }

      delay(10);
    }
}

void print(const char* text, ...)
{
    char buf[22];

    va_list vl;
    va_start(vl, text);

    vsnprintf(buf, sizeof(buf), text, vl);

    va_end(vl);

    RefreshDisplay(buf);
}


void RefreshDisplay(char* text)
{
    display.clearDisplay();

    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h); //calc width of new string
    display.setCursor((128 - w) / 2, (64 - h) / 2);
    
    display.println(text);
    display.display();
}
