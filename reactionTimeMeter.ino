#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

const int greenButtonPin = 5;
const int redButtonPin = 6;
const int buzzerPin = 7;
const int relayPin = 8;

int greenButtonState = 0;
int redButtonState = 0;

void setup()   {
  pinMode(greenButtonPin, INPUT_PULLUP);
  pinMode(redButtonPin, INPUT_PULLUP); 
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);               
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  //display.display();
  //delay(1000);
  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(50,0);
  display.println("mini");
  display.setCursor(38,8);
  display.println("Projects!");
  display.setTextColor(BLACK, WHITE);
  display.setCursor(2,18);
  display.println(" REACTION TIME METER ");
  display.display();
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Select mode using");
  display.setTextColor(BLACK, WHITE);
  display.println("GREEN BUTTON");
  display.display();
  delay(3000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0,0);
  display.setTextColor(BLACK, WHITE);
  display.println("1. VISUAL");
  display.setTextColor(WHITE);
  display.println("2. AUDIO");
  display.println("3. TOUCH");
  display.println("SELECT WITH RED");
  display.display();
  delay(1000);
  display.clearDisplay();
}

int greenButtonCount = 0;
int greenButtonValid = 1;
int redButtonValid = 1;
void loop() {
  greenButtonState = digitalRead(greenButtonPin);
  if (greenButtonState == LOW && greenButtonValid == 1) {
    greenButtonValid = 0;
    greenButtonCount += 1;
    updateMenu(greenButtonCount);      
  }
  if (greenButtonState == HIGH){
    greenButtonValid = 1;
  }
  redButtonState = digitalRead(redButtonPin);
  if (redButtonState == LOW && redButtonValid == 1) {
      redButtonValid = 0;
      loadTest(greenButtonCount);
      
  }
  if (redButtonState == HIGH){
      redButtonValid = 1;
  }
}

void loadTest(int greenButtonCount){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  if (greenButtonCount%3==0){
      //VISUAL TEST
      display.setTextColor(WHITE);
      display.println("White circle will");
      display.println("appear at random time");
      display.println("press RED as fast as you can");
      display.display();
      delay(3000);
      display.clearDisplay();
      display.display();
      delay(2000);

      int randomNumber = random(0,30);
      int delaysec = randomNumber*100;
      delay(randomNumber);
      display.fillCircle(display.width()/2, display.height()/2, 10, WHITE);
      display.display();
      int t1 = millis();
      while (digitalRead(redButtonPin)==HIGH){
            
      }
      int t2 = millis();
      int reactionTime = t2 - t1;

      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.println("Reaction time(ms) =");
      display.println(reactionTime);
      display.display();
      delay(3000);
      updateMenu(greenButtonCount);
  }
  if (greenButtonCount%3==1){
      //AUDIO TEST
      display.setTextColor(WHITE);
      display.println("Buzzer will");
      display.println("buzz at random time");
      display.println("press RED as fast as you can");
      display.display();
      delay(2000);

      int randomNumber = random(0,30);
      int delaysec = randomNumber*100;
      delay(randomNumber);

      digitalWrite(buzzerPin, HIGH);
      int t1 = millis();
      while (digitalRead(redButtonPin)==HIGH){
            
      }
      digitalWrite(buzzerPin, LOW);
      int t2 = millis();
      int reactionTime = t2 - t1;

      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.println("Reaction time(ms) =");
      display.println(reactionTime);
      display.display();
      delay(3000);
      updateMenu(greenButtonCount);      
  }
  if (greenButtonCount%3==2){
      //TOUCH TEST
      display.setTextColor(WHITE);
      display.println("Touch plate will");
      display.println("move at random time");
      display.println("press RED as fast as you can");
      display.display();
      delay(2000);

      int randomNumber = random(0,30);
      int delaysec = randomNumber*100;
      delay(randomNumber);

      digitalWrite(relayPin, HIGH);
      int t1 = millis();
      while (digitalRead(redButtonPin)==HIGH){
            
      }
      digitalWrite(relayPin, LOW);
      int t2 = millis();
      int reactionTime = t2 - t1;

      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.println("Reaction time(ms) =");
      display.println(reactionTime);
      display.display();
      delay(3000);
      updateMenu(greenButtonCount);
  }
}

void updateMenu(int greenButtonCount) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  if (greenButtonCount%3==0){
    display.setTextColor(BLACK, WHITE);    
  } else {
    display.setTextColor(WHITE);  
  }
  display.println("1. VISUAL");
  if (greenButtonCount%3==1){
    display.setTextColor(BLACK, WHITE);    
  } else {
    display.setTextColor(WHITE);  
  }
  display.println("2. AUDIO");
  if (greenButtonCount%3==2){
    display.setTextColor(BLACK, WHITE);    
  } else {
    display.setTextColor(WHITE);  
  }
  display.println("3. TOUCH");
  display.setTextColor(WHITE);
  display.println("SELECT WITH RED");
  display.display();
}

















   

