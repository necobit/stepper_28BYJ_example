//M5Stanp S3用
int motorSpeed = 6000;  //モーター速度初期値
int speedMin = 6000;  //モーター最低速度　数値が大きいと遅くなる
int speedMax = 5000;  //モーター最高速度　数値が小さいと速くなる
int interval = 2000;  //最高速を維持する時間（msec）
int stopTime = 10;  //ターン時の待機時間
int nowTime;
int dir = 1;
int spd = 1;
int lookup[8] = { B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001 };
int pin_1n1 = 1;
int pin_1n2 = 3;
int pin_1n3 = 5;
int pin_1n4 = 7;

void setup() {
  pinMode(pin_1n1, OUTPUT);
  pinMode(pin_1n2, OUTPUT);
  pinMode(pin_1n3, OUTPUT);
  pinMode(pin_1n4, OUTPUT);
}

void loop() {

  //正回転
  if (dir) {
    for (int i = 0; i < 8; i++) {
      digitalWrite(pin_1n1, bitRead(lookup[i], 0));
      digitalWrite(pin_1n2, bitRead(lookup[i], 1));
      digitalWrite(pin_1n3, bitRead(lookup[i], 2));
      digitalWrite(pin_1n4, bitRead(lookup[i], 3));
      delayMicroseconds(motorSpeed);
    }
  }

  // 逆回転
  if (!dir) {
    for (int i = 7; i >= 0; i--) {
      digitalWrite(pin_1n1, bitRead(lookup[i], 0));
      digitalWrite(pin_1n2, bitRead(lookup[i], 1));
      digitalWrite(pin_1n3, bitRead(lookup[i], 2));
      digitalWrite(pin_1n4, bitRead(lookup[i], 3));
      delayMicroseconds(motorSpeed);
    }
  }

  //回転数を上げる
  if (spd) {
    motorSpeed = motorSpeed * 0.95;
    if (motorSpeed <= speedMax) {
      motorSpeed = speedMax;
      spd = 0;
    }
  }
  if (nowTime + interval < millis()) {
    // 回転数を下げる
    if (!spd) {
      motorSpeed = motorSpeed * 1.05;
      if (motorSpeed >= speedMin) {
        motorSpeed = speedMin;
        spd = 1;
        dir = !dir;
        delay(stopTime);
        nowTime = millis();
      }
    }
  }
}
