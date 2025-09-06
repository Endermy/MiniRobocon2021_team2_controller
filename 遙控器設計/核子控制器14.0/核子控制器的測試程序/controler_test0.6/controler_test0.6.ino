#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;
const int LCD_COLS = 20;
const int LCD_ROWS = 4;

void setup() {
  for (int digital_pin = 38 ; digital_pin < 50 ; digital_pin ++ ) {
    pinMode(digital_pin, INPUT_PULLUP);
  }
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  int status;
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if (status)
  {
    hd44780::fatalError(status);
  }
  int num = 1;
  lcd.noCursor();
  lcd.clear();
  for (int Cursor = 16 ; Cursor < 20 ; Cursor ++ ) {
    lcd.setCursor(Cursor, 0);
    lcd.print(num);
    num++;
  }
  num = 1;
  for (int Cursor = 12 ; Cursor < 20 ; Cursor ++ ) {
    lcd.setCursor(Cursor, 2);
    lcd.print(num);
    num++;
  }

}


void loop() {
  int snapshot [16];
  delay (100);
  char shoting_pin = A0;
  for ( int newlength = 0 ; newlength < 4 ; newlength ++ ) {
    snapshot[newlength] = analogRead(shoting_pin);
    shoting_pin++;
  }
  shoting_pin = 38;
  for ( int newlength = 4 ; newlength < 16 ; newlength ++ ) {
    snapshot[newlength] = digitalRead(shoting_pin);
    shoting_pin++;
  }
  lcd.setCursor(16, 1);
  for (int sc_round = 7 ; sc_round > 3 ; sc_round--) {
    if (snapshot[sc_round] == 1) {
      lcd.print('X');
    } else if (snapshot[sc_round] == 0) {
      lcd.print('O');
    }
  }
  lcd.setCursor(12, 3);
  for (int sc_round = 8 ; sc_round < 16 ; sc_round++) {
    if (snapshot[sc_round] == 1) {
      lcd.print('X');
    } else if (snapshot[sc_round] == 0) {
      lcd.print('O');
    }
  }
  lcd.setCursor(0, 0);
  lcd.print(snapshot[0]);
  lcd.print("   ");
  lcd.setCursor(0, 1);
  lcd.print(snapshot[1]);
  lcd.print("   ");
  lcd.setCursor(0, 2);
  lcd.print(snapshot[2]);
  lcd.setCursor(0, 3);
  lcd.print(snapshot[3]);
}
