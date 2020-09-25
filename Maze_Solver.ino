// Motors Pins
int Motor_Right1=6;
int Motor_Right2=7;
int Motor_Left1=8;
int Motor_Left2=9;


void setup() {
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  
 // pinMode(11,INPUT);
 // pinMode(12,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  int F=Distance(2,3);
  int R=Distance(4,5);
  int L=Distance(11,12);

  if(F>5 && R<5 && L<5){
    go_forward();
  }
  if(F>5 && R>5 && L>5){
    turn_left();
    delay(100);
  }
  if(F>5 && R>5 && L<5){
    go_forward();
  }
  if(F>5 && R<5 && L>5){
    turn_left();
    delay(100);
  }
  if(F<5 && R<5 && L<5){
    turn_left();
    delay(200);
  }
  if(F<5 && R>5 && L>5){
    turn_left();
    delay(100);
  }
 
  if(F<5 && R>5 && L<5){
    turn_right();
    delay(100);
  }
 
  if(F<5 && R<5 && L>5){
    turn_left();
    delay(100);
  }

}


  int Distance(int echo , int triger){
  pinMode(echo,INPUT);
  pinMode(triger,OUTPUT);
  Serial.read();
  digitalWrite(triger,LOW);
  delay(10);
  digitalWrite(triger,HIGH);
  delay(10);
  digitalWrite(triger,LOW);
  int  duration=pulseIn(echo,HIGH);
  int distance=duration/58.8;
  delay(100);
  return distance;
}

void go_forward(){
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  
}

void go_back(){
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  
}

void turn_left(){
    digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  
}

void turn_right(){
    digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  
}

