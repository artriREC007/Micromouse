//Ultrasonic Sensor 1
const int trigPin = 7;
const int echoPin = 6;
//Ultrasonic Sensor 2
const int trigPin2 = A0;
const int echoPin2 = A1;
//Ultrasonic Sensor 3
const int trigPin3 = A2;
const int echoPin3 = A3;

//L298N Motor Driver
// Motor A connections
int enA = 9;
int in1 = 11;
int in2 = 12;
// Motor B connections
int enB = 10;
int in3 = 4;
int in4 = 5;

//Encoder
#define CLK1 1
#define CLK2 2
#define DT1 6 //See the hardware
#define DT2 7
float duration1,duration2,duration3,distance1,distance2,distance3;
const float pi = 3.14; // Pi value 
const int R = 3;  //Radius of the wheel from center to edge
const int N = 40; //no of steps for one rotation
float distance = 0;

int counter1 = 0;
int counter2 = 0;
int currentStateCLK1;
int lastStateCLK1;
int currentStateCLK2;
int lastStateCLK2;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  Serial.begin(9600);

  // Motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	
	// // Turn off motors - Initial state
	// digitalWrite(in1, LOW);
	// digitalWrite(in2, LOW);
	// digitalWrite(in3, LOW);
	// digitalWrite(in4, LOW);

  pinMode(CLK1,INPUT);
  pinMode(CLK2,INPUT);
  lastStateCLK1 = digitalRead(CLK1);  
  lastStateCLK2 = digitalRead(CLK2);    
}

void loop() {
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin2, HIGH);
  digitalWrite(trigPin3, HIGH);

  duration1 = pulseIn(echoPin, HIGH);
  duration2 = pulseIn(echoPin2, HIGH);
  duration3 = pulseIn(echoPin3, HIGH);

  distance1 = (duration1*.0343)/2;
  distance2 = (duration2*.0343)/2;
  distance3 = (duration3*.0343)/2;

  // Serial.print("Distance: ");
  // Serial.println(distance);

	directionControl();//Later conditions will be added
	speedControl();

  //Encoders Distance Measurement
  currentStateCLK1 = digitalRead(CLK1);
	if (currentStateCLK1 != lastStateCLK1 && currentStateCLK1 == 1){
		if (digitalRead(DT1) != currentStateCLK1) {
			counter1 ++;
     } 
     else {
			counter1 --;
     }
   } 
  if (currentStateCLK2 != lastStateCLK2 && currentStateCLK2 == 1){
		if (digitalRead(DT2) != currentStateCLK2) {
			counter2 ++;
     } 
     else {
			counter2 --;
     }
   } 
   //Distance Measurement
  // distance = ((2*pi*R)/N) * counter ;//cm
  // lastStateCLK = currentStateCLK;
}

void directionControl() {
	analogWrite(enA, 255);
	analogWrite(enB, 255);

	// Turn on motor A & B
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
	delay(2000);
	
	// Now change motor directions
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	delay(2000);
	
	// Turn off motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

// This function lets you control speed of the motors
void speedControl() {
	// Turn on motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	
	// Accelerate from zero to maximum speed
	for (int i = 0; i < 256; i++) {
		analogWrite(enA, i);
		analogWrite(enB, i);
		delay(20);
	}
	
	// Decelerate from maximum speed to zero
	for (int i = 255; i >= 0; --i) {
		analogWrite(enA, i);
		analogWrite(enB, i);
		delay(20);
	}
	
	// Now turn off motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}
