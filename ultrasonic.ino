int echo=6;
int trig=7;
int motor1=2;
int motor2=3;
int motor3=4;
int motor4=5;
float duration,distance;
void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,INPUT);
  pinMode(7,OUTPUT);
Serial.begin(9600);
}

void loop() {
Serial.read();
digitalWrite(7,LOW);
delay(10);
digitalWrite(7,HIGH);
delay(10);
digitalWrite(7,LOW);
duration=pulseIn(3,HIGH);
distance=duration/58.8;
Serial.print(distance);
Serial.println("cm");
delay(500);
if(distance>15){
  forward();
}
else if(distance<15){
  back();
  delay(100);
  right();
}
}
void forward(){
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
}
void back(){
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
}
void right(){
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
}
void left(){
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
}
void hold(){
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
}

