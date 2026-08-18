#include <virtuabotixRTC.h>
virtuabotixRTC RTC(4, 3, 2);
char time[6];

const int serialdata = 5;
const int shiftclock = 6;
const int latchclock = 7;

const int display_pins[4] = {8, 9, 10, 11};
const int dp = 12;
const int numbers[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};
int digits[4];

void setup() {
  // put your setup code here, to run once:
  //RTC.setDS1302Time(0, 2, 18, 2, 18, 8, 2026);

  pinMode(serialdata, OUTPUT);
  pinMode(shiftclock, OUTPUT);
  pinMode(latchclock, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(display_pins[i], OUTPUT);
    digitalWrite(display_pins[i], HIGH);
  }

  pinMode(dp, OUTPUT);
  digitalWrite(dp, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  RTC.updateTime();
  snprintf(time, sizeof(time), "%02d%02d", RTC.hours, RTC.minutes);

  digits[0] = time[3] - '0';
  digits[1] = time[2] - '0';
  digits[2] = time[1] - '0';
  digits[3] = time[0] - '0';
  Serial.println(digits[0]);
  for (int i = 0; i < 4; i++) {
    if (i == 2) {
      digitalWrite(dp, HIGH);
    }
    shiftOut(serialdata, shiftclock, MSBFIRST, numbers[digits[i]]);
    digitalWrite(latchclock, HIGH);
    digitalWrite(display_pins[i], LOW);
    delay(2);
    digitalWrite(display_pins[i], HIGH);
    digitalWrite(dp, LOW);
    digitalWrite(latchclock, LOW);
  }
}
