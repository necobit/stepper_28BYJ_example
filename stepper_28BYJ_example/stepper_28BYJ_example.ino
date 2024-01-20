//M5Stanp S3用
int motorSpeed = 6000;  //モーター速度初期値
int speedMin = 6000;    //モーター最低速度　数値が大きいと遅くなる
int speedMax = 5000;    //モーター最高速度　数値が小さいと速くなる
int stopTime = 10;      //ターン時の待機時間
int nowTime;
int dir = 1;
int spd = 1;
int counter;
int endpoint;
int steps = 4096;  //1回転のステップ数
int end = 0;
int angle = 45;  //回転させたい角度、360で一回転で逆転、720で二回転で逆転　
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
  endpoint = map(steps, 0, steps, 0, 4096 * angle / 360);
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
      counter++;
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
      counter--;
    }
  }

  //指定された角度まで行ったら減速フラグを立てる
  if (counter >= endpoint | counter <= -endpoint) {
    counter = 0;
    spd = 0;
    end = 1;
  }

  //回転数を上げる
  if (spd) {
    motorSpeed = motorSpeed * 0.95;  //一番右の数字を1に近づけるとスピードの変化がゆっくりになる
    if (motorSpeed <= speedMax) {
      motorSpeed = speedMax;
      spd = 0;
    }
  }

  if (end) {
    // 回転数を下げる
    if (!spd) {
      motorSpeed = motorSpeed * 1.05;  //一番右の数字を1に近づけるとスピードの変化がゆっくりになる
      if (motorSpeed >= speedMin) {
        motorSpeed = speedMin;
        spd = 1;
        dir = !dir;
        delay(stopTime);
        nowTime = millis();
        end = 0;
      }
    }
  }
}
