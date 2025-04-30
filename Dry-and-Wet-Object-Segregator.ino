#include <Servo.h>

// Pin definitions
const int trigPin = 7;
const int echoPin = 8;
const int servoPin = 9;
const int moisturePin = 2; // Digital pin for soil moisture sensor // Analog pin for soil moisture sensor
const int moistureThreshold = 500; // Adjust this based on calibration for wet/dry detection

Servo myServo;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(servoPin);
  myServo.write(100);
  delay(1000);
}

void loop() {
  long duration = measureDistance();
  long distance = duration * 0.0344 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm");

  if (distance < 7) {
    delay(1200);
    bool isWet = digitalRead(moisturePin); // Read digital value (HIGH = Wet, LOW = Dry)
    // Digital sensor directly gives wet/dry status // Wet if above threshold, else dry

    Serial.print(", Moisture: ");
    Serial.print(isWet);
    Serial.print(" -> ");
    Serial.println(isWet ? "Wet" : "Dry");

    if (isWet) {
      Serial.println("Wet object detected! Moving clockwise.");
      myServo.write(180);
    } else {
      Serial.println("Dry object detected! Moving counterclockwise.");
      myServo.write(20);
    }
    delay(1200);
    Serial.println("Returning to 100 degrees.");
    myServo.write(100);
    delay(1200);
  } else {
    Serial.println(" - No object detected. Servo remains at 100 degrees.");
  }
  delay(1200);
}

long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
}
