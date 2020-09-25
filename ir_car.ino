#define ts 300
int sensR=A0;
int sensL=A1;
int motorright1=6;
int motorright2=7;
int motorleft1=8;
int motorleft2=9;
int enb1=3;
void setup() {
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensR=analogRead(A0);
  sensL=analogRead(A1);
 // Serial.print("sensR = ");
 // Serial.print(sensR);
 // Serial.print("sensL = ");
  //Serial.println(sensL);
 // delay(500);
  if (sensR > 300 && sensL > 300){
    forward();
  }
else if(sensR > 300 && sensL < 300){
  back();
  delay(350);
  right();
  delay(300);
}
else if (sensR < 300 && sensL > 300){
  back();
  delay(350);
  left();
  delay(300);
 
}
else if (sensR < 300 && sensL < 300){
  back();
  delay(350);
  right();
  delay(300);
  
}
}


void back(){
  digitalWrite(motorright1,HIGH);
  digitalWrite(motorright2,LOW);
  digitalWrite(motorleft1,HIGH);
  digitalWrite(motorleft2,LOW);
  analogWrite(enb1,150);
}
void forward(){
  digitalWrite(motorright1,LOW);
  digitalWrite(motorright2,HIGH);
  digitalWrite(motorleft1,LOW);
  digitalWrite(motorleft2,HIGH);
  analogWrite(enb1,130);
}
void right(){
  digitalWrite(motorright1,HIGH);
  digitalWrite(motorright2,LOW);
  digitalWrite(motorleft1,LOW);
  digitalWrite(motorleft2,HIGH);
  analogWrite(enb1,150);
}
void left(){
  digitalWrite(motorright1,LOW);
  digitalWrite(motorright2,HIGH);
  digitalWrite(motorleft1,HIGH);
  digitalWrite(9,LOW);
  analogWrite(enb1,150);
}
void hold(){
  digitalWrite(motorright1,LOW);
  digitalWrite(motorright2,LOW);
  digitalWrite(motorleft1,LOW);
  digitalWrite(motorleft2,LOW);
  analogWrite(enb1,150);
}

