#include <LiquidCrystal.h>
const int rs = 11, en = 10, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  lcd.print("Ready in...");
  for(int i = 5 ;i>=1 ; i--){
    lcd.display();
    lcd.print(i);
    delay(1000);
    lcd.clear();
    lcd.print("Ready in...");

  }
  lcd.clear();
  for(;;){
  delay(100);
  lcd.noDisplay();
  delay(500);
  lcd.display();
  lcd.print("ZigZag Team");
  delay(500);
  lcd.clear();
  }
}
