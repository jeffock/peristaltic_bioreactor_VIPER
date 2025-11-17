/*
* nov 17, 2025
* 
* changelog: 
* - implement serial port communication
*/

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
