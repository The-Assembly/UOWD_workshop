/* 
   Robot Movement Based on Ultrasonic sensor HC-SR04 by Judhi Prasetyo
   Original HC-SR04 adaptation code by Tautvidas Sipavicius
 */

const int trigPin = 6; // connect pin 2 to Trigger on HC-SR04
const int echoPin = 7; // connect pin 4 to Echo on HC-SR04

/* Additional codes by Judhi P. (Nov 2016)
 * Robot forward/stop/reverse based on object distance
 *  
 * (stop)<---dmax<---(forward)-->dmed<---(stop)--->dmin--->(reverse)
 *  
 *  
*/
const int dmax = 25; // if object is beyond this distance, robot will stop
const int dmed = 15; // if object is between dmax and dmed, robot will move forward
const int dmin = 5; // if object is closer thatn this distance, robot will reverse

// connect motor controller pins to Arduino digital pins
// motor one
const int enA = 13;
const int in1 = 12;
const int in2 = 11;
// motor two
const int enB = 10;
const int in3 = 9;
const int in4 = 8;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop()
{
  long duration, cm;

  //pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  Serial.print(cm);
  Serial.print(" cm: ");
  
  if (cm >= dmax)
    {
      RobotStop();
    }
  if ((cm < dmax) && (cm > dmed))
    {
      RobotForward();
    }
  if ((cm <= dmed) && (cm > dmin))
    {
      RobotStop();
    }
   if (cm <= dmin)
    {
      RobotReverse();
    }
 
  delay(100);
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void RobotStop()
{
  Serial.println("Stop ");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void RobotForward()
{
  Serial.println("Forward");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);  
  analogWrite(enA, 200);
  analogWrite(enB, 200);
}

void RobotReverse()
{
  Serial.println("Reverse");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);  
  analogWrite(enA, 200);
  analogWrite(enB, 200);
}
