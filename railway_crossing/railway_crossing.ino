#include <Servo.h>

const int SENSOR_1_PIN = A0;
const int SENSOR_2_PIN = A1;
const int SERVO_PIN = A2;

const int LED_WHITE_PIN = 3;
const int LED_RED_LEFT_PIN = 4;
const int LED_RED_RIGHT_PIN = 5;
const int SPEAKER_PIN = 8;

const int BLINK_DELAY = 400;

const float LIGHT_CHANGE_THRESHOLD = 0.2;

Servo gateServo;

int sensor1Value = 0;
int sensor2Value = 0;
int prevSensor1Value = 0;
int prevSensor2Value = 0;
int vonat = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_WHITE_PIN, OUTPUT);
  pinMode(LED_RED_LEFT_PIN, OUTPUT);
  pinMode(LED_RED_RIGHT_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);

  gateServo.attach(SERVO_PIN);

  prevSensor1Value = analogRead(SENSOR_1_PIN);
  prevSensor2Value = analogRead(SENSOR_2_PIN);
}

float percentage(int previous, int actual) {
  return 1.0*(actual-previous)/previous;
}

void loop() {
  sensor1Value = analogRead(SENSOR_1_PIN);
  sensor2Value = analogRead(SENSOR_2_PIN);

  float change1 = percentage(prevSensor1Value, sensor1Value);
  float change2 = percentage(prevSensor2Value, sensor2Value);
  prevSensor1Value = sensor1Value;
  prevSensor2Value = sensor2Value;

  Serial.print("sensor 1: ");
  Serial.print(sensor1Value);
  Serial.print("(");
  Serial.print(change1*100);
  Serial.print("%)");
  Serial.print(" sensor 2: ");
  Serial.print(sensor2Value);
  Serial.print("(");
  Serial.print(change1*100);
  Serial.println("%)");

  if (change1 < -1*LIGHT_CHANGE_THRESHOLD) {
    vonat = 1;
    gateServo.write(0);
  }
  if (change2 < -1*LIGHT_CHANGE_THRESHOLD && vonat == 1) {
     vonat = 2;
  }
  if (change2 > LIGHT_CHANGE_THRESHOLD && vonat == 2) {
     vonat = 0;
     gateServo.write(90);
  }

  if (vonat == LOW) {
    digitalWrite(LED_WHITE_PIN, HIGH);
    digitalWrite(LED_RED_LEFT_PIN, LOW);
    digitalWrite(LED_RED_RIGHT_PIN, LOW);
    delay(BLINK_DELAY);
    digitalWrite(LED_WHITE_PIN, LOW);
    delay(BLINK_DELAY);
  }

  else {
    digitalWrite(LED_WHITE_PIN, LOW);
    digitalWrite(LED_RED_LEFT_PIN, LOW);
    digitalWrite(LED_RED_RIGHT_PIN, HIGH);
    tone(SPEAKER_PIN, 262);
    delay(BLINK_DELAY);
    digitalWrite(LED_RED_LEFT_PIN, HIGH);
    digitalWrite(LED_RED_RIGHT_PIN, LOW);
    noTone(SPEAKER_PIN);
    delay(BLINK_DELAY);
  }
}
