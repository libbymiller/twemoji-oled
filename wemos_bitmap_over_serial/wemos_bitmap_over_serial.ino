#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>
 
#define OLED_RESET 0
Adafruit_SSD1306 display(OLED_RESET);
 
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
 
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 


char myBitmap [600] = "";

int startingPoint = 0;
int count = 0;
int thingyCount = 0;


void setup() {
  // put your setup code here, to run once:
  //Serial.begin(115200);
  Serial.begin(230400);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  //Serial.println("showing splashscreen");
  display.display();     // show splashscreen  
  //Serial.println("waiting 2 secs");

  delay(2000);
  display.clearDisplay();
//  display.drawBitmap(0,0, myBitmap1f49a, 48,48, WHITE);
//  display.display();
}

byte getVal(char c)
{
   if(c >= '0' && c <= '9'){
     return (byte)(c - '0');
   }else{
     return (byte)(c-'a'+10);
   }
}

char myTiny = '\0';

void loop() {
    while (Serial.available() > 0)
    {
        char recieved = Serial.read();
        //Serial.print("recieved ");
        //Serial.print(recieved);
        //Serial.println("...");

        if ( (recieved != '\n') && (startingPoint%2 == 1)){
           //Serial.print("combining ... ");
           //Serial.print(myTiny);
           //Serial.print(recieved);
           //Serial.println("");

           byte bb = getVal(recieved) + getVal(myTiny) * 16 ;
           //byte bb = '0'+'x'+getVal(recieved) + getVal(myTiny) * 16 ;

           //Serial.println(getVal(recieved));
           //Serial.println(getVal(myTiny));
           ////Serial.print(bb, HEX);
           //Serial.print(count);
           //Serial.print(" ");
           //Serial.print(bb);
           //Serial.print(" ");
           //Serial.println(bb, HEX);
           myBitmap[count] = bb;
           count = count + 1;

        }else{
           // process the last 2 bits into a char
           myTiny = recieved;
        }
        
        // Process message when pipe character is recieved
        //if (recieved == '\n')
       //ugh! mno idea why new lines doesn't work
       if (recieved == '|')

        {
            
            Serial.println("Arduino Received: new line");
            display.clearDisplay();

            //Serial.println(startingPoint);
            display.drawBitmap(0,0, (uint8_t*) myBitmap, 48,48, WHITE);

            display.display();
            //Serial.println("HELLO");
            int len = sizeof(myBitmap);
            //Serial.println(len);
            //for(int i = 0; i < len; i++) {
              // Serial.print(myBitmap[i], HEX);
            //}
            //Serial.println("");
            startingPoint = 0;
            thingyCount = 0;
            count = 0;

        }else{
            startingPoint = startingPoint + 1;
        }

    }
}
