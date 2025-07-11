#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// LCD 주소
LiquidCrystal_I2C lcd(0x27, 16, 2);

// 키패드
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'*', '7', '4', '1'},
  {'0', '8', '5', '2'},
  {'#', '9', '6', '3'},
  {'D', 'C', 'B', 'A'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String input = "";

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Class Number:");
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key >= '0' && key <= '9') {
      if (input.length() < 8) {
        input += key;
        lcd.setCursor(0,1);
        lcd.print(input + "        ");
      }
    } else if (key == '#') { // 전송
      if (input.length() > 0) {
        Serial.println(input);
        lcd.setCursor(0,1);
        lcd.print("Enter!     ");
        delay(700);
        input = "";
        lcd.setCursor(0,1);
        lcd.print("                ");
      }
    } else if (key == '*') { // 하나만 삭제
      if (input.length() > 0) {
        input.remove(input.length() - 1);
        lcd.setCursor(0,1);
        lcd.print(input + "                ");
      }
    }
  }
}
