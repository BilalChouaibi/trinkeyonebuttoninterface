/////////Declare and Initialize Variables////////////////////////////
#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <Adafruit_GFX.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT);
// How many internal neopixels do we have? some boards have more than one!
#define NUMPIXELS        1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
//We need to track how long the momentary pushbutton is held in order to execute different commands
//This value will be recorded in seconds
float pressLength_milliSeconds = 0;

// Define the *minimum* length of time, in milli-seconds, that the button must be pressed for a particular option to occur
int selection = 100;
int enter = 400;        

//The Pin your button is attached to
int buttonPin = 12;
int picbefore = 0;
int pic = 0;
void setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  display.clearDisplay();
  display.setTextSize(2);  
  // Initialize the pushbutton pin as an input pullup
  // Keep in mind, when pin 2 has ground voltage applied, we know the button is being pressed
  pinMode(buttonPin, INPUT_PULLUP);     

  //Start serial communication - for debugging purposes only
  Serial.begin(9600);
  #if defined(NEOPIXEL_POWER)
  // If this board has a power control pin, we must set it to output and high
  // in order to enable the NeoPixels. We put this in an #if defined so it can
  // be reused for other boards without compilation errors
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
  #endif                                     
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(20); // not so bright
} // close setup


void loop() {
  pixels.fill(0x000000);
  pixels.show();
  //Record *roughly* the tenths of seconds the button in being held down
  while (digitalRead(buttonPin) == LOW ){ 

    delay(100);  //if you want more resolution, lower this number 
    pressLength_milliSeconds = pressLength_milliSeconds + 100;   

    //display how long button is has been held
    Serial.print("ms = ");
    Serial.println(pressLength_milliSeconds);

  }//close while
  if (pressLength_milliSeconds >= enter){
    blinkgreen();
    pic+=10;
    picbefore = picbefore - 10;
    Serial.print("pic= ");
    Serial.println(pic);
    Serial.print("previouspic= ");
    Serial.println(picbefore);
  } 

  //option 1 - Execute the first option if the button is held for the correct amount of time
  else if(pressLength_milliSeconds >= selection){
    blinkorange();
    pic+=1;
    picbefore = picbefore - 1;
    Serial.print("pic= ");
    Serial.println(pic);
    Serial.print("previouspic= ");
    Serial.println(picbefore);
    if (pic == 5){
      pic = 1;
    }
  }//close if options
  if (pic == 0)
{
  header();
  display.setTextSize(2);
  display.setCursor(32,11); display.print ("PRESS");
  display.setCursor(48, 28); display.print("TO");
  display.setCursor(32, 45); display.print("ENTER");
  refresh();
}
//Selection////////////////////////////////////////////////////
if (pic == 1)
{
  header();
  display.setTextSize(1);
  display.setCursor(0,11);  display.print ("> Nextcloud");
  display.setCursor(0,20);  display.print ("Nintendo");
  display.setCursor(0,29);  display.print ("Bookys");
  //display.setCursor(0,47);  display.print (" HELP");
  display.setCursor(0,56);  display.print ("Project Info");
  refresh();
}

if (pic == 2)
{
  header();
  display.setCursor(0,11);  display.print ("Nextcloud");
  display.setCursor(0,20);  display.print ("> My Nintendo");
  display.setCursor(0,29);  display.print ("Bookys");
  //display.setCursor(0,47);  display.print (" HELP");
  display.setCursor(0,56);  display.print ("Project Info");
  refresh();
}

if (pic == 3)
{
  header();
  display.setCursor(0,11);  display.print ("Nextcloud");
  display.setCursor(0,20);  display.print ("My Nintendo");
  display.setCursor(0,29);  display.print ("> Bookys");
  //display.setCursor(0,47);  display.print (" HELP");
  display.setCursor(0,56);  display.print ("Project Info");
  refresh();
}
if (pic == 4)
{
  header();
  display.setCursor(0,11);  display.print ("Nextcloud");
  display.setCursor(0,20);  display.print ("My Nintendo");
  display.setCursor(0,29);  display.print ("Bookys");
  //display.setCursor(0,47);  display.print (" HELP");
  display.setCursor(0,56);  display.print ("> Project Info");
  refresh();
}

//Enter Selection////////////////////////////////////////////////////
if (pic == 11)
{
  header();
  display.setCursor(0,11);  display.print ("Nextcloud on nfc");
  display.setCursor(0,56);  display.print ("> Retour");
  refresh();
}
if (pic == 21){
  pic = 1;
}if (pic == 12)
{
  if (picbefore != pic-10){
    pic = pic - 1;
  }
  header();
  display.setCursor(0,11);  display.print ("My Nintendo on nfc");
  display.setCursor(0,56);  display.print ("> Retour");
  refresh();
}
if (pic == 22){
  pic = 2;
}
if (pic == 13)
{
    if (picbefore != pic-10){
    pic = pic - 1;
  }
  header();
  display.setCursor(0,11);  display.print ("Bookys on nfc");
  display.setCursor(0,56);  display.print ("> Retour");
  refresh();
}
if (pic == 23){
  pic = 3;
}
if (pic == 14)
{
    if (picbefore != pic-10){
    pic = pic - 1;
  }
  header();
  display.setCursor(0,11);  display.print ("PROJECT INFO");
  display.setCursor(0,20);  display.print ("Editor: Bilal");
  display.setCursor(0,56);  display.print ("> Retour");
  refresh();
}
if (pic == 24){
  pic = 4;
}
  //every time through the loop, we need to reset the pressLength_Seconds counter  pressLength_milliSeconds = 0;
  pressLength_milliSeconds = 0;
} // close void loop
void header()
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(22,0);  display.print(" nfc-emulator");
  display.drawLine (0,9,128,9, WHITE);
}

void refresh()
{
  display.display();
  delay(00);
  display.clearDisplay();
}
void blinkorange(){
  pixels.fill(0xFF0000);
  pixels.show();
  delay(100); // wait half a second
}
void blinkgreen(){
  pixels.fill(0xFF7F00);
  pixels.show();
  delay(100);
}
void nfcinject(char site){

}