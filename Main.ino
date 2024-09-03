int flexData;
int flexSensor = A0;

int echoPin = 6;
int triggerPin = 7;

int flexCount = 0;
int ultrasonicCount = 0;
void setup() {
    Serial.begin(9600);
    pinMode(flexSensor, INPUT);
    pinMode(echoPin, INPUT);
    pinMode(triggerPin, OUTPUT);
}

void loop() {
    // Flex sensor
    flexData = analogRead(flexSensor);
    Serial.print("Flex value: ");
    Serial.print(flexData);
    Serial.println("");

    // Ultrasonic sensor
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    int dist1 = duration * 0.034 / 2;
    int dist2 = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.print(dist1);
    Serial.println(" cm");

    // GOOD POSTURE
    // Flex sensor : A constant flex measured at relaxed position of sensor
    // with an error of + - 20% is allowed.
    int idealFlex = 145;  // varies due to erroneous sensor
    int allowedFlexError = (20 * idealFlex) / 100;
    if (abs(idealFlex - flexData) > allowedFlexError) flexCount++;
    if (flexCount == 20) {
        flexCount = 0;
        // bluetooth, notify the user
    }

    // Ultrasonic sensor : We use 2 ultrasonic sensors (placed diagonally) and
    // measure the distance on both. This checks if the user's back is parallel
    // to the chair
    int idealDifference = 0;
    int allowedDifference = 10;
    if (abs(dist1 - dist2) > allowedDifference) ultrasonicCount++;
    if (ultrasonicCount == 20) {
        ultrasonicCount = 0;
        // bluetooth, notify the user
    }
    Serial.println("");
    delay(1000);
}
