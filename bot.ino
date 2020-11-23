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
  frontWheel.load();
  digitalWrite(bipPin, HIGH);
  delay(500);
  digitalWrite(bipPin, LOW);
  leftMotor.stop();
  rightMotor.stop();
}

void loop() {
// frontWheel.rotate(0);
// head.setRotation(0);
  //Serial.println(head.getDistance(0));
  // leftMotor.setSpeed(1);
  // int error = bot.loop();

  // // BIP BIP
  // for(int i = 0; i < error; i++) {
  //   digitalWrite(bipPin, HIGH);
  //   delay(100);
  //   digitalWrite(bipPin, LOW);
  // }
  
}
