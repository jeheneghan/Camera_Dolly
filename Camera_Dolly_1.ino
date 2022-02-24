// This code (C++) operates a bi-directional camera dolly that is controlled by two switches and a potentiometer
//
// The direction switch changes the direction of the stepper motor
// The enable switch enables the stepper motor so that it can be moved freely
// The limit switches stop the stepper motor at the end of the rail
// & the potentiometer controls the speed of the stepper motor
//
// ***RPMs and steps per revolution are given as reference but not used since steps/unit time is sufficient

// Define constants
const int maxRPM = 50;
const int minRPM = 30;

// Connections to A4988
const int dirPin = 3; // Direction
const int stepPin = 2; // Step
const int enaPin = 4; // Enable Motor

//AccelStepper stepper(1, stepPin, dirPin);

// Inputs
const int potPin1 = 0; // Potentiometer
const int limitPin = 7; // Limit Switches - White Wires
const int dirSwitchPin = 8; // Direction Switch Pin - Red wire
const int onPin = 12; // Enables and Disables Steppers - Orange Wire

// Motor steps per rotations
const int stepsPerRev = 400;

// Variables
int potValue = 0;
int stepDelay = 5000;
int limitInput;
bool limitFlag = true;

void setup() {

  Serial.begin(9600);
  
  // Setup the pins as Outputs
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(enaPin,OUTPUT);

  // Setup input pins
  pinMode(potPin1,INPUT);
  pinMode(limitPin,INPUT);
  pinMode(dirSwitchPin,INPUT);
  pinMode(onPin,INPUT);
}

void loop() {
  // Handle Inputs
  potValue = analogRead(potPin1);
  stepDelay = map(potValue, 0, 1023, 1000, 10000);
  Serial.print(stepDelay);
  Serial.print("\t");
  Serial.print(digitalRead(limitPin));
  Serial.print("\t");
  Serial.print(digitalRead(dirSwitchPin));
  Serial.print("\t");
  Serial.println(digitalRead(onPin));

  if (digitalRead(onPin) == HIGH)
  {
    digitalWrite(enaPin,LOW);
    limitFlag = false;
  }
  else
  {
    digitalWrite(enaPin,HIGH);
    limitFlag = true;
  }

  if (digitalRead(dirSwitchPin) == HIGH)
  {
    digitalWrite(dirPin,HIGH);
  }
  else
  {
    digitalWrite(dirPin,LOW);
  }
  
  if (limitFlag)
  {
    if (digitalRead(limitPin) == LOW)
    {
      digitalWrite(stepPin,HIGH);
      limitFlag = false;
    }
    else
    {
    // Handle Outputs
    //control_stepper(stepDelay);
    control_stepper(stepDelay);
    }
  }
  

}

void control_stepper(int STEP_DELAY) {

      digitalWrite(stepPin,HIGH);
      delayMicroseconds(STEP_DELAY); 
      digitalWrite(stepPin,LOW);
      delayMicroseconds(STEP_DELAY);  
}
