
//OLED libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//In and Out
int in = 13;
int pushbutton=9;
//Variables
unsigned long duration = 0;
float rpm = 0;
float rpm_a = 0;
int counter = 0;
int present = 0;
int previous = 0;
unsigned long elapsed = 0;
unsigned long elapsed_prev = 0;
int disabled = 0;





void setup()   {                
  Serial.begin(9600);
  pinMode(in,INPUT);
  pinMode(pushbutton,INPUT);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done  
  // Clear the buffer.
  display.clearDisplay();

  // text display tests
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("ELECTRONOOBS RPMmeter");
  display.display();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,19);
  display.println("RPM:");
  display.setCursor(80,19);
  display.println(rpm);  
  display.display();

  //We print the ELECTRONOOBS logo
  scrollENlogo();
  
  
  elapsed = micros();
}


void loop() {


if(digitalRead(pushbutton))
{

  //Arduino low power enabled
  if(disabled==0)
  {
    sleep_disable();
    disabled = 1;
  }
///////////////////////one rotation measure///////////////////
   if (digitalRead(in) == 1 && previous == 0)
  {
    previous = 1;
    duration = elapsed - elapsed_prev;
    elapsed_prev  = micros();    
  }
  if (digitalRead(in) == 1 && previous == 1)
  {
    previous = 1;       
  }
  if (digitalRead(in) == 0 && previous == 1)
  {
    previous = 0;     
  }
  if (digitalRead(in) == 0 && previous == 0)
  {
    previous = 0;
    elapsed = micros();    
  }
//////////////////////////////////////////////////////////////
   
   
   
   rpm = 60000000/duration;


//We add a small error in the rpm value (in this case +-2)
if ( (rpm_a-2) < rpm  &&  rpm < (rpm_a+2))
{
  rpm_a = rpm;
  counter = counter +1;
  if (counter == 50)
  {
     // text display tests
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("ELECTRONOOBS RPMmeter");  
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,19);
    display.println("RPM:");
    display.setCursor(80,19);
    display.println(rpm);  
    display.display();
    counter = 0;
  }
}

if (!( (rpm_a-2) < rpm  &&  rpm < (rpm_a+2)))
{
  rpm_a=rpm;
}
}//end if pushbutton=1



else{
  //Variables
  display.display();
  display.clearDisplay();
  delay(10);
  duration = 0;
  rpm = 0;
  rpm_a = 0;
  counter = 0;
  present = 0;
  previous = 0;
  
  //Arduino low power enabled
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  disabled = 0;
}//end pushbutton =0
}//end of void loop








void scrollENlogo(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(7,0);
  display.clearDisplay();
  display.println("ELECTRONOOBS");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("WELCOME");
  display.display();
  delay(1);
 
  display.startscrolldiagright(0x00, 0x07);
  delay(5000);
  display.stopscroll();
  
}
