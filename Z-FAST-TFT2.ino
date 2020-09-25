#include <TouchScreen.h> //touch library
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#include <SD.h>
#include <SPI.h>

static const int RXPin = 53, TXPin = 51;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
//#include <CurieTime.h>
#define TOUCH_ORIENTATION  0
#define TITLE "TouchScreen.h Calibration"

LCDWIKI_KBV tft(ILI9486,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

TouchScreen t(XP, YP, XM, YM, 300);
TSPoint tp;                      //Touchscreen_due branch uses Point

#define PIXEL_NUMBER  (tft.Get_Display_Width()/4)
#define FILE_NUMBER 4
#define FILE_NAME_SIZE_MAX 20


void Read_Resistive(void)
{
    tp = t.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
}

bool is_pressed(void)
{
    bool state;
    Read_Resistive();
    state = (tp.z > 20 && tp.z < 1000);
    return state;
}
void MainPage(){
    tft.Fill_Screen(BLACK);
   // tft.Fill_Rect(0,0,240,320,YELLOW);
   // tft.Fill_Rect(240,0,240,320, BLUE);

    tft.Set_Text_Size(5);
    tft.Set_Text_colour(YELLOW);
    tft.Set_Text_Back_colour(BLACK);
    tft.Print_String("WELC",102,20);
    tft.Set_Text_Size(5);
    tft.Set_Text_colour(BLUE);
    tft.Set_Text_Back_colour(BLACK);
    tft.Print_String("OME TO",226,20);
    tft.Set_Text_Size(5);
    tft.Set_Text_colour(YELLOW);
    tft.Set_Text_Back_colour(BLACK);
    tft.Print_String("Z-",160,80);
    tft.Set_Text_Size(5);
    tft.Set_Text_colour(BLUE);
    tft.Set_Text_Back_colour(BLACK);
    tft.Print_String("FAST",225,80);
    tft.Set_Text_Size(5);
    tft.Set_Text_colour(YELLOW);
    tft.Set_Text_Back_colour(BLACK);
    tft.Print_String("VEH",142,140);
    tft.Set_Text_Size(5);
    tft.Set_Text_colour(BLUE);
    tft.Set_Text_Back_colour(BLACK);
    tft.Print_String("ICLE",230,140);
    tft.Fill_Rect(150,250,180,70, GREEN);
    tft.Set_Text_Size(5);
    tft.Set_Text_colour(RED);
    tft.Set_Text_Back_colour(GREEN);
    tft.Print_String("DRIVE",170,270);
   
}

uint32_t cx, cy;
uint32_t rx[8], ry[8];
int32_t clx, crx, cty, cby;
float px, py;
int dispx, dispy, text_y_center, swapxy;
uint32_t calx, caly, cals;
char buf[13];
int x, y;
char currentPage;
char selectedUnit;
double lok;
int sat, minuta, sek,brzina,visina;
int in = A15;
unsigned long duration = 0;
float rpm = 0;
float rpm_a = 0;
int counter = 0;
int present = 0;
int previous = 0;
unsigned long elapsed = 0;
unsigned long elapsed_prev = 0;

float  out[100];
int i =0 ;
int z=0 ;
float sum =0;
int k;
int s = millis()/1000;
int m = millis()/60000 ;
int h = millis()/3600000 ;

void speedmeter(){

        if (analogRead(in) < 300 && previous == 0)
  {
    previous = 1;
    duration = elapsed - elapsed_prev;
    elapsed_prev  = micros();    
       rpm =60000000/(duration*4);

  }
  if (analogRead(in) <300 && previous == 1)
  {
    previous = 1;       
  }
  if (analogRead(in) > 300 && previous == 1)
  {
    previous = 0;     
  }
  if (analogRead(in)>300 && previous == 0)
  {
    previous = 0;
    elapsed = micros();

        //// zaher comment 
        rpm=0;
  }
//////////////////////////////////////////////////////////////
   
   
   


//We add a small error in the rpm value (in this case +-2)
if ( (rpm_a-2) < rpm  &&  rpm < (rpm_a+2))
{
  rpm_a = rpm;
  //counter = counter +1;
  //if (counter == 50)
  //{
         out[z] = rpm ; 
     
  /*  Serial.println("RPM:");
    Serial.println(rpm);  
     //Serial.println(analogRead(in));*/
    //counter = 0;
    z = z+1;
  //}
}

if (!( (rpm_a-2) < rpm  &&  rpm < (rpm_a+2)))
{
  rpm_a=rpm;
  out[z] = rpm ; 
  z = z+1;
}

if(z==99)
{
  for (i=0;i<100;i++){
    
    sum = sum +out [i] ; 
    
    }
    sum = sum/100 ;
    k=60*sum*0.001885;
    Serial.println(sum);  
    z= 0 ;
  }

////////////////// next part 

       tft.Print_Number_Int(k, 0, 190, 120, ' ', 10); 
        tft.Print_Number_Int(s, 90, 260, 2, ' ', 10); 
        tft.Print_String(":",70,260);
        tft.Print_Number_Int(m, 50, 260, 2, ' ', 10); 
        tft.Print_String(":",30,260);
        tft.Print_Number_Int(h, 10, 260, 2, ' ', 10); 

      
    //  visina=gps.altitude.meters(); 
      //Serial.println(gps.altitude.value());   
    }
 




void setup() {
  // Serial.begin(9600);
  pinMode(in,INPUT);
//  setTime(10, 00, 00, 26, 10, 2019);
  elapsed = micros();
    Serial.begin(9600);
       ss.begin(GPSBaud);
    digitalWrite(A0, HIGH);
    pinMode(A0, OUTPUT);
    tft.Init_LCD();
    tft.Set_Rotation(3  );
    int ID=tft.Read_ID();
    dispx = tft.Get_Display_Width();
    dispy = tft.Get_Display_Height();
    text_y_center = (dispy / 2) - 6;
    //tft.Fill_Screen(BLACK);
    MainPage();
    currentPage='0';
    selectedUnit='0';

 
 

}

void loop() {

 
  
  digitalWrite(13, HIGH);
  TSPoint p = t.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if(currentPage=='0'){
  
  if (p.z > 20 && p.z < 1000) 
  {
      if (150< p.x < 350 && 250 < p.y < 310) 
      {
            drawFrame(150,250,330,320);
     currentPage='1';
     tft.Fill_Screen(WHITE);
     DRIVE();
     speedmeter();
      }
  
   }
  }
  else if(currentPage=='1'){
    if (p.z > 20 && p.z < 1000) 
     {
      if (0< p.x < 50 && 0 < p.y < 30) {
         drawFrame(0,0,50,30);
         currentPage='0';
         tft.Fill_Screen(WHITE);
         MainPage();
      }
  
   }
  }
 
  
}
void drawFrame(int x1, int y1, int w, int h){
   tft.Draw_Rectangle(x1, y1, w, h);
    tft.Fill_Rect(x1,y1,w-x1,h-y1,RED);
    tft.Fill_Rect(x1,y1,w-x1,h-y1,WHITE);

}

void DRIVE(){
     tft.Fill_Screen(GREEN);
     tft.Fill_Rect(0,0,52,30,RED);
    tft.Set_Text_Size(2);
    tft.Set_Text_colour(BLACK);
    tft.Set_Text_Back_colour(RED);
    tft.Print_String("BACK",3,8);
    tft.Set_Text_Size(5);
    tft.Set_Text_colour(BLACK);
    tft.Set_Text_Back_colour(GREEN);
   // tft.Print_String("00",190,120);
    tft.Print_String("KM",190,160);
    tft.Print_String("SPEED",150,80);
    tft.Draw_Rectangle(145, 75, 300, 200);
    tft.Set_Text_Size(3);
    tft.Print_String("00",370,260);
    tft.Print_String("DISTANCE",325,230);
    tft.Print_String("M",380,290);
    tft.Draw_Rectangle(320, 225, 470, 315);
   // tft.Print_String("00:00",10,260);
    tft.Print_String("TIME",20,230);
    tft.Draw_Rectangle(5, 225, 120, 315);
    tft.Draw_Rectangle(345, 0, 470, 50);
    tft.Print_String("100%",370,60);
    tft.Draw_Rectangle(320, 6, 345, 44);
    tft.Fill_Rect(350,2,28,48,YELLOW);
    tft.Fill_Rect(380,2,28,48,YELLOW);
    tft.Fill_Rect(410,2,28,48,YELLOW);
    tft.Fill_Rect(440,2,28,48,YELLOW);
  /* while(currentPage=='1'){
   while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
     
     sat=gps.time.hour(); 
      minuta=gps.time.minute(); 
      sek=gps.time.second(); 
      brzina=gps.speed.kmph();
    //  visina=gps.altitude.meters(); 
      //Serial.println(gps.altitude.value());   
    }
        tft.Print_Number_Int(brzina, 0, 30, 2, ' ', 10); 
        tft.Print_Number_Int(sek, 90, 260, 2, ' ', 10); 
        tft.Print_String(":",70,260);
        tft.Print_Number_Int(minuta, 50, 260, 2, ' ', 10); 
        tft.Print_String(":",30,260);
        tft.Print_Number_Int(sat, 10, 260, 2, ' ', 10); 

 }


}*/
}
