int pwmPin = 12; // assigns pin 12 to variable pwm
int motorPin = 11; //assigns pin 11 to motor speed
int pot = A0; // assigns analog input A0 to variable pot
int c1 = 0;   // declares variable c1
int c2 = 0;   // declares variable c2
float motorSpeed;

void setup()  // setup loop
{
  pinMode(pwmPin, OUTPUT); 
  pinMode(motorPin, OUTPUT);
  motorSpeed = 0.45;
  analogWrite(motorPin, 255 * motorSpeed);
  pinMode(pot, INPUT);  
  delay(200);
}

void loop()
{
  motorSpeed = 0.12; // To change the motor's speed, change this number!
  analogWrite(motorPin, 255 * motorSpeed);

  c2= analogRead(pot); 
  c1= 1024-c2; // subtracts c2 from 1000 and saves the result in c1

  digitalWrite(pwmPin, HIGH); 
  delayMicroseconds(c1);   
  digitalWrite(pwmPin, LOW);  
  delayMicroseconds(c2);  
}
