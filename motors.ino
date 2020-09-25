int motorright1=6;
int motorright2=7;
int motorleft1=8;
int motorleft2=9;
void setup() {
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
}

void loop() {
digitalWrite(6,HIGH);
digitalWrite(7,LOW);
delay(10000);
//الموتور الايمن يتحرك الي الامام
digitalWrite(8,LOW);
digitalWrite(9,HIGH);
delay(1000);

//الموتور الايسر يتحرك للخلف
digitalWrite(6,LOW);
digitalWrite(7,HIGH);
delay(10000);

//الموتور الايمن يتحرك للخلف
digitalWrite(8,HIGH);
digitalWrite(9,LOW);
delay(10000);

//الموتور الايسر يتحرك للامام
}
