/*
* nov 10, 2025
* 
* changelog: 
* - reorganize code for readability/maintainability
* - implement second motor for the double-screw design
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

  // Set initial motor speed
  currentMotorSpeed = INITIAL_MOTOR_SPEED;
  analogWrite(MOTOR_PWM_PIN1, int(255 * currentMotorSpeed));
  analogWrite(MOTOR_PWM_PIN2, MOTOR_PWM_PIN1);

  delay(200); // Wait for hardware stabilization
}

void loop()
{
  // Set the motor to the desired run speed
  currentMotorSpeed = RUNNING_MOTOR_SPEED;
  analogWrite(MOTOR_PWM_PIN1, int(255 * currentMotorSpeed));
  analogWrite(MOTOR_PWM_PIN2, MOTOR_PWM_PIN1);

  // Read potentiometer value and calculate pulse timing
  potValue = analogRead(POTENTIOMETER_PIN);
  highTimeMicroseconds = 1024 - potValue;

  // Generate a PWM-like pulse on a separate pin, duration ~proportional to potentiometer
  digitalWrite(PUMP_PIN, HIGH);
  delayMicroseconds(highTimeMicroseconds);
  digitalWrite(PUMP_PIN, LOW);
  delayMicroseconds(potValue);
}
