#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// LCD 설정 (주소 0x27 또는 0x3F, 부품에 따라 다를 수 있음)
LiquidCrystal_I2C lcd(0x20, 16, 2); // LCD I2C 주소(보통 0x27)

// Keypad 설정
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // R1, R2, R3, R4
byte colPins[COLS] = {5, 4, 3, 2}; // C1, C2, C3, C4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String input = "";

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("학번 입력:");
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key >= '0' && key <= '9') {
      if (input.length() < 8) { // 학번 8자리 제한
        input += key;
        lcd.setCursor(0,1);
        lcd.print(input + "        "); // 입력값 표시(오른쪽 여백 클리어)
      }
    } else if (key == '#') { // 엔터(입력 완료)
      if (input.length() > 0) {
        Serial.println(input); // 시리얼로 학번 송신
        lcd.setCursor(0,1);
        lcd.print("전송 완료!     ");
        delay(700);
        input = "";
        lcd.setCursor(0,1);
        lcd.print("                "); // 클리어
      }
    } else if (key == '*') { // 전체 삭제
      input = "";
      lcd.setCursor(0,1);
      lcd.print("                "); // 클리어
    }
  }
}
