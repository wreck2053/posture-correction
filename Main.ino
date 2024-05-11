#include <SoftwareSerial.h>

const int flexPin = A0;
const int trigPin = 9;
const int echoPin = 10;

SoftwareSerial bluetooth(2, 3);

void setup() {
    Serial.begin(9600);
    bluetooth.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
    int flexValue = analogRead(flexPin);  // flex sensor

    long duration, distance;  // ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    Serial.print("Flex level: "); Serial.println(flexValue);
    Serial.print("Distance: "); Serial.println(distance);

    bluetooth.print("Flex level: "); bluetooth.println(flexValue);
    bluetooth.print("Distance: "); bluetooth.println(distance);

    // warning conditions
    if (distance > 60) {
        Serial.println("Warning: Object too close!");
        bluetooth.println("Warning: Object too close!");
    }

    if (flexValue > 250 || flexValue < 150) {
        Serial.println("Warning: Flex value out of range!");
        bluetooth.println("Warning: Flex value out of range!");
    }

    delay(1000);
}
