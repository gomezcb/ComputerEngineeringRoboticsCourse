#define CW  0     // clockwise
#define CCW 1     // counterclockwise
#define MOTOR_A 0 // motor A
#define MOTOR_B 1 // motor B

const byte PWMA = 3;  // speed for motor A
const byte PWMB = 11; // speed for motor B
const byte DIRA = 12; // direction control
const byte DIRB = 13; // direction control

void setup() {
	pinMode(PWMA, OUTPUT); // set as outputs
	pinMode(PWMB, OUTPUT);
	pinMode(DIRA, OUTPUT);
	pinMode(DIRB, OUTPUT);

	digitalWrite(PWMA, LOW); // initialize to low
	digitalWrite(PWMB, LOW);
	digitalWrite(DIRA, LOW);
	digitalWrite(DIRB, LOW);
}

void forward(byte spd) {
	digitalWrite(DIRA, CW); // go clockwise
	digitalWrite(DIRB, CW); // go clockwise
	analogWrite(PWMA, spd); // motor A speed, 0~255 pwm strength
	analogWrite(PWMB, spd); // motor B speed, 0~255 pwm strength
}

void turnRight(byte spd) {
	digitalWrite(DIRA, CW);  // clockwise
	digitalWrite(DIRB, CCW); // clockwise
	analogWrite(PWMA, spd);  // motor A speed, 0~255 pwm strength
	analogWrite(PWMB, spd);  // motor B speed, 0~255 pwm strength
}

void turnLeft(byte spd) {
	digitalWrite(DIRA, CCW); // clockwise
	digitalWrite(DIRB, CW);  // clockwise
	analogWrite(PWMA, spd);  // motor a speed, 0~255 pwm strength
	analogWrite(PWMB, spd);  // motor b speed, 0~255 pwm strength
}

void stopArdumoto(byte motor) {
	digitalWrite(DIRA, CW); // clockwise
	digitalWrite(DIRB, CW); // clockwise
	analogWrite(PWMA, 0);   // stop motor A
	analogWrite(PWMB, 0);   // stop motor B
}

void backward(byte spd) {
        digitalWrite(DIRA, CCW); // go counter clockwose
        digitalWrite(DIRB, CCW); // go counter clockwise
        analogWrite(PWMA, spd);  // motor A speed, 0~255 pwm strength
        analogWrite(PWMB, spd);  // motor B speed, 0~255 pwm strength
}

void loop() {
    delay(50);
    forward(255);     // forward
    //backward(255);  // backward
    //delay(5000);
    //turnRight(255); // turn car right
    //turnLeft(127);  // turn car left
}
