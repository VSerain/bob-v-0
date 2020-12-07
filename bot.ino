#include "./DCMotor.h";
#include "./AbstarctServo.h";
#include "./Head.h";
#include "./Manager.h";

DCMotor leftMotor(6, 4, 9);
DCMotor rightMotor(11, 10 ,12);
AbstarctServo frontWheel(3);
Head head(5, 8, 7);

int bipPin = 2;

Manager bot(head, frontWheel, leftMotor, rightMotor, 0);

void setup() {
  Serial.begin(9600);
  pinMode(bipPin, OUTPUT);
  leftMotor.load();
  rightMotor.load();
  head.load();
  frontWheel.offset = -8;
  frontWheel.load();

  
  digitalWrite(bipPin, HIGH);
  delay(500);
  digitalWrite(bipPin, LOW);
}

void loop() {
  int error = bot.loop();
  // BIP BIP
  for(int i = 0; i < error; i++) {
    digitalWrite(bipPin, HIGH);
    delay(100);
    digitalWrite(bipPin, LOW);
  }
}
