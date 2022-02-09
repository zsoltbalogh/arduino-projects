const int SENSOR_1_PIN = A0;

const int LED_WHITE_PIN = 3;
const int LED_RED_LEFT_PIN = 4;
const int LED_RED_RIGHT_PIN = 5;

const int BLINK_DELAY = 400;

const int LIGHT_THRESHOLD = 50;

int sensor1Value = 0;
int vonat = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_WHITE_PIN, OUTPUT);
  pinMode(LED_RED_LEFT_PIN, OUTPUT);
  pinMode(LED_RED_RIGHT_PIN, OUTPUT);
}

void loop() {
  sensor1Value = analogRead(SENSOR_1_PIN);

  Serial.print("sensor 1: ");
  Serial.println(sensor1Value);
  
  if (sensor1Value < LIGHT_THRESHOLD) {  
    vonat = 1;
  }
  else {
     vonat = 0;
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
    delay(BLINK_DELAY);
    digitalWrite(LED_RED_LEFT_PIN, HIGH);
    digitalWrite(LED_RED_RIGHT_PIN, LOW);
    delay(BLINK_DELAY);
  }
}
