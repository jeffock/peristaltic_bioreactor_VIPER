/*
* nov 17, 2025
* 
* changelog: 
* - implement serial port communication
*/

// ---- Pin Definitions ----
const int PUMP_PIN = 12;  // Pin to control pump 
const int MOTOR_PWM_PIN1 = 11;   // Pin to control motor speed via PWM (~11)
const int MOTOR_PWM_PIN2 = 10;   // Pin to control motor speed via PWM (~10)
const int POTENTIOMETER_PIN = A0; // Analog input pin for potentiometer

// ---- Parameters ----
const float INITIAL_MOTOR_SPEED = 0.45; // Initial normalized speed (0-1)
const float RUNNING_MOTOR_SPEED = 0.12; // Running normalized speed (0-1)

// ---- State Variables ----
int potValue = 0;         // Stores raw potentiometer reading
int highTimeMicroseconds = 0;  // Pulse duration high
float currentMotorSpeed;   // Current motor speed (0-1)

void setup()
{
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(MOTOR_PWM_PIN1, OUTPUT);
  pinMode(MOTOR_PWM_PIN2, OUTPUT);
  pinMode(POTENTIOMETER_PIN, INPUT);

  Serial.begin(9600); // Initialize serial communication

  // Set initial motor speed
  currentMotorSpeed = INITIAL_MOTOR_SPEED;
  analogWrite(MOTOR_PWM_PIN1, int(255 * currentMotorSpeed));
  analogWrite(MOTOR_PWM_PIN2, int(255 * currentMotorSpeed));

  delay(200); // Wait for hardware stabilization
}

void loop()
{
  // Check for new motor speed over serial
  if (Serial.available() > 0) {
    float newSpeed = Serial.parseFloat(); // Read float sent from Python
    if (newSpeed >= 0.0 && newSpeed <= 1.0) { // Validate range
      currentMotorSpeed = newSpeed;
    }
  }

  // Apply motor speed PWM
  analogWrite(MOTOR_PWM_PIN1, int(255 * currentMotorSpeed));
  analogWrite(MOTOR_PWM_PIN2, int(255 * currentMotorSpeed));

  // Existing potentiometer pulse timing logic
  potValue = analogRead(POTENTIOMETER_PIN);
  highTimeMicroseconds = 1024 - potValue;

  digitalWrite(PUMP_PIN, HIGH);
  delayMicroseconds(highTimeMicroseconds);
  digitalWrite(PUMP_PIN, LOW);
  delayMicroseconds(potValue);
}
