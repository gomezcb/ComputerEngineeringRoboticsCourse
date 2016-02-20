// CSE 541: Robotics and Control
// Carlos Gomez & Richard Quon
// Project 3
// Mobile Controlled Robot Code

#include <SPI.h>
#include <WiFi.h>
#include <NewPing.h> // for ultrasonic sensor

int spd = 150; // initialize motor speed

#define CW      0 // clockwise -> 0
#define CCW     1 // counter clockwise -> 1
#define MOTOR_A 0 // motor A -> 0
#define MOTOR_B 1 // motor B -> 1

const byte PWM_A = 3; // PWM control (speed) for motor A
const byte PWM_B = 6; // PWM control (speed) for motor B
const byte DIR_A = 5; // direction control for motor A
const byte DIR_B = 4; // direction control for motor B

int status = WL_IDLE_STATUS;     // indicates wifi does nothing
boolean clientConnected = false; // clients connetion status
WiFiServer server(23);           // global variable

void setup() {
  Serial.begin(9600); // start serial
  while(!Serial);     // waiting for connection
  
  pinMode(PWM_A, OUTPUT); // set output pins
  pinMode(PWM_B, OUTPUT);
  pinMode(DIR_A, OUTPUT);
  pinMode(DIR_B, OUTPUT);

  digitalWrite(PWM_A, LOW); // initialize pins to LOW
  digitalWrite(PWM_B, LOW);
  digitalWrite(DIR_A, LOW);
  digitalWrite(DIR_B, LOW);

  //printNetworks(); // print networks to serial monitor
  //connectOpenNetwork("CSUSB-ACCESS"); // connect to open network
  connectClosedNetwork("CSE541", "CSE541SPRING2015"); // connect to closed network
  server.begin();  // start the server
}

void printNetworks() {
  Serial.println("Scanning Networks..."); // scan networks
  byte num = WiFi.scanNetworks();         // get list of wifi networks
  
  for(int network = 0; network < num; network++) { // possible networks 
    Serial.print(network); // print network data
    Serial.print(") ");
    Serial.print(WiFi.SSID(network)); // network SSID or name
    Serial.print("    Strength: ");
    Serial.print(WiFi.RSSI(network)); // networks strength in dBm
    Serial.print(" dBm    Security: ");
    Serial.println(WiFi.encryptionType(network)); // type of network security
  }
}

// connect open network
void connectOpenNetwork(char ssid[]) {
  Serial.print("Connecting to ");
  Serial.println(ssid); // network name
  
  status = WiFi.begin(ssid);     // connect to the network
  while(status != WL_CONNECTED); // wait till connected 
  
  // if connected to network
  Serial.print("Connected to: ");
  Serial.println(WiFi.localIP()); // print the IP address
}

// connect to closed network
void connectClosedNetwork(char ssid[], char password[]) {
  Serial.print("Connecting To ");
  Serial.println(ssid); // print network name
  
  delay(50);
  status = WiFi.begin(ssid, password); // connect to the network
  delay(1000);
  
  while(status != WL_CONNECTED); // wait till connected
  
  // if connected to network
  Serial.print("Connected to: ");
  Serial.println(WiFi.localIP()); // print the IP address
}

void forward(byte spd) {
  digitalWrite(DIR_A, CW); // 0, clockwise
  digitalWrite(DIR_B, CW); // 0, clockwise
  analogWrite(PWM_A, spd); // speed of A
  analogWrite(PWM_B, spd); // speed of B
}

void backward(byte spd) {
  digitalWrite(DIR_A, CCW); // 1, counter clockwise
  digitalWrite(DIR_B, CCW); // 1, counter clockwise
  analogWrite(PWM_A, spd);  // speed of A
  analogWrite(PWM_B, spd);  // speed of B
}

void turnLeft(byte spd) {
  digitalWrite(DIR_A, CW);      // 0, clockwise
  digitalWrite(DIR_B, CW);      // 1, counter clockwise
  analogWrite(PWM_A, spd);      // speed of A
  analogWrite(PWM_B, spd - 50); // speed of B
}

void turnRight(byte spd) {
  digitalWrite(DIR_A, CW);      // 1, counter clockwise
  digitalWrite(DIR_B, CW);      // 0, clockwise
  analogWrite(PWM_A, spd - 50); // speed of A
  analogWrite(PWM_B, spd);      // speed of B
}

void stop_robot() {
  digitalWrite(DIR_A, CW); // 0, clockwise
  digitalWrite(DIR_B, CW); // 0, clockwise
  analogWrite(PWM_A, 0);   // stop motor A
  analogWrite(PWM_B, 0);   // stop motor B
}

void inc_speed(int spd) {
 // increment code
 spd = spd + 5;
 return;
}

void dec_speed(int spd) { 
 // decrement code
 spd = spd - 5;
 return;
}

void loop() {
  delay(50);      // delay
  //printNetworks(); // print networks to serial monitor

  // test motor control with wifi shied conected
  // backward();
  // forward();
  // turnLeft();
  // turnRight();
  
  Serial.println(spd); // print the speed to serial monitor
  
  WiFiClient client = server.available(); // connect to inclimng client

  if (client) {            // if client active
    if(!clientConnected) { // If client not already connected, print message
      client.flush();      // Clears communication channel
      Serial.println("New Client"); // Alerts via serial of new connection
      client.println("Hi!");  // message to client
      clientConnected = true; // client connect to not repeat process
     }

    if(client.available() > 0) { // Checks if client sent data
      char temp = {0};
      temp = client.read(); // Read char sent by client and save
      server.write(temp);   // Send character back to client
        
      if (temp == 'f') { // move car forwards
        forward(spd);
      }

      else if (temp == 'b') { // move car backwards
        backward(spd);
      }

      else if (temp == 'l') { // turn car left
        turnLeft(spd);
      }

      else if (temp == 'r') { // turn car right
        turnRight(spd);
      }

      else if (temp == 's') { // stop the car
        stop_robot();
      }

      else if (temp == 'i') { // increment speed
        spd = spd + 5;
        //inc_speed(spd);
      }

      else if (temp == 'd') { // decrement speed
        spd = spd - 5;
        //dec_speed(spd);
      }
    }
  }
}
