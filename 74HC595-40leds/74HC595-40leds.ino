#define SER 4
#define RCLK 6
#define SRCLK 7

void setup() {
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);

  digitalWrite(SRCLK, LOW);
  digitalWrite(RCLK, LOW);
}

void writeShift(int value, int current) {

  for (int index = 0; index < 5; index++) {
    if (index == 4 - current) {
      shiftOut(SER, SRCLK, MSBFIRST, value);
    } else {
      shiftOut(SER, SRCLK, MSBFIRST, 0);
    }
  }
  
  digitalWrite(RCLK, HIGH);
  digitalWrite(RCLK, LOW);
  delay(20);
}

int value = 1;

void loop() {
  for (int currentByte = 0; currentByte < 5; currentByte++) {
    while (value <= 128) {
      writeShift(value, currentByte);
      value <<= 1;
    }
    value = 1;
  }
  
  value = 64;
  
  for (int currentByte = 4; currentByte >= 0; currentByte--) {
    while (value > 0) {
      writeShift(value, currentByte);
      value >>= 1;
    }
    value = 128;
  }

  value = 2;
}
