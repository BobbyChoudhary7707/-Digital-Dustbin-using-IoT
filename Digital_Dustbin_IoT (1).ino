#include <Servo.h>

Servo dustbinServo;

// Sensor Pins
int metalSensor = 2;        // Metal sensor digital pin
int moistureSensor = A0;    // Moisture sensor analog pin
int ldrSensor = A1;         // LDR sensor analog pin

// Servo Pin
int servoPin = 9;

// Threshold values (Adjust after testing)
int moistureThreshold = 500;
int ldrThreshold = 300;

void setup() {
  
  Serial.begin(9600);

  pinMode(metalSensor, INPUT);
  
  dustbinServo.attach(servoPin);
  dustbinServo.write(90);   // Default position

  Serial.println("Digital Dustbin System Started");
}

void loop() {

  int metalValue = digitalRead(metalSensor);
  int moistureValue = analogRead(moistureSensor);
  int ldrValue = analogRead(ldrSensor);

  Serial.print("Metal: ");
  Serial.print(metalValue);
  Serial.print(" Moisture: ");
  Serial.print(moistureValue);
  Serial.print(" LDR: ");
  Serial.println(ldrValue);

  // ---- Metal Waste ----
  if (metalValue == LOW) {
    Serial.println("Metal Waste Detected");
    dustbinServo.write(0);   // Metal compartment
    delay(3000);
    resetServo();
  }

  // ---- Wet Waste ----
  else if (moistureValue > moistureThreshold) {
    Serial.println("Wet Waste Detected");
    dustbinServo.write(45);  // Wet compartment
    delay(3000);
    resetServo();
  }

  // ---- Dry / Plastic Waste ----
  else if (ldrValue < ldrThreshold) {
    Serial.println("Dry/Plastic Waste Detected");
    dustbinServo.write(135); // Dry compartment
    delay(3000);
    resetServo();
  }

  else {
    Serial.println("No Waste Detected");
  }

  delay(1000);
}

// Function to reset servo to default
void resetServo() {
  dustbinServo.write(90);
  delay(2000);
}
