// Arduino-Ardumoto obstacle avoiding robot
// Sweeper Robot
// CSUSB Project 1
#include <NewPing.h>

#define TRIGGER_PIN  7   // pin tied to trigger pin on the ultrasonic sensor
#define ECHO_PIN     6   // pin tied to echo pin on the ultrasonic sensor
#define MAX_DISTANCE 200 // max dist. we want to ping for (in cm.)

#define CW  0      // clockwise
#define CCW 1      // counterclockwise
#define MOTOR_A 0  // motor A
#define MOTOR_B 1  // motor B

const byte PWMA = 3;  // speed for motor A
const byte PWMB = 11; // speed for motor B
const byte DIRA = 12; // direction control
const byte DIRB = 13; // direction control

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup

void setup() {
	// setupArdumoto(); // set all pins as outputs
    Serial.begin(9600);

	pinMode(PWMA, OUTPUT); // define outputs
	pinMode(PWMB, OUTPUT);
	pinMode(DIRA, OUTPUT);
	pinMode(DIRB, OUTPUT);

	digitalWrite(PWMA, LOW); // initialize to low
	digitalWrite(PWMB, LOW);
	digitalWrite(DIRA, LOW);
	digitalWrite(DIRB, LOW);
}

void forward(byte spd) {
	driveArdumoto(MOTOR_A, CW,  spd);
	driveArdumoto(MOTOR_B, CCW, spd);
}

void turnRight(byte spd) {
	stopArdumoto(MOTOR_B);           // stop motor
	driveArdumoto(MOTOR_A, CW, spd); // turn right
}

void stopArdumoto(byte motor) {
	driveArdumoto(motor, 0, 0);
}

void driveArdumoto(byte motor, byte dir, byte spd) {
	if (motor == MOTOR_A) {
		digitalWrite(DIRA, dir);
		analogWrite(PWMA, spd);
	}

	else { // (motor == MOTOR_B) {
		digitalWrite(DIRB, dir);
		analogWrite(PWMB, spd);
	}
}

void loop() {
	delay(2000);
	unsigned int uS = sonar.ping(); // seng ping, get ping time in uS
	if( uS / US_ROUNDTRIP_CM > 50 || uS / US_ROUNDTRIP_CM == 0) {
		// move forward
		forward(150);
	}

	else if (uS / US_ROUNDTRIP_CM < 50) {
		turnRight(100);
		delay(500);
	}
}
