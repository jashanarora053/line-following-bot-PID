//--Defining Pins--  

// --- Sensor Pins ---  
const int S1_PIN = 2; // Left-most sensor  
const int S2_PIN = 3;  
const int S3_PIN = 4; // Center sensor  
const int S4_PIN = 5;  
const int S5_PIN = 6; // Right-most sensor  

// -- Motor Driver Pins (assuming it to be L298N motordriver) --  
// Left Motor  
const int L_IN1 = 7;  
const int L_IN2 = 8;  
const int L_ENA = 9; // PWM Speed Control  

// Right Motor  
const int R_IN3 = 11;  
const int R_IN4 = 12;  
const int R_ENB = 10; // PWM Speed Control  

// --- PID Tuning Parameters ---  
double Kp = 30;  
double Ki = 0.1;  
double Kd = 20;  
/*We used 'double' bcz we might have to store very precise decimal values*/  

// ---Base Speed for motor with which it will move by default (0-255)---  
const int BASE_SPEED = 130;  

// --- Global PID Variables ---  
int error = 0;  
int lastError = 0;  
double integral = 0;  
double derivative = 0;  
double correction = 0;  

void setup() {  

// Initialize Sensor Pins as Inputs pinMode(S1_PIN, INPUT);  
pinMode(S2_PIN, INPUT);  
pinMode(S3_PIN, INPUT);  
pinMode(S4_PIN, INPUT);  
pinMode(S5_PIN, INPUT);  

// Initialize Motor driver Pins as Outputs pinMode(L_IN1, OUTPUT);  
pinMode(L_IN2, OUTPUT);  
pinMode(L_ENA, OUTPUT);  
pinMode(R_IN3, OUTPUT);  
pinMode(R_IN4, OUTPUT);  
pinMode(R_ENB, OUTPUT);  

// Initialize Serial Monitor  
Serial.begin(9600);  
Serial.println("Started"); //just to confirm it has started successfully  
delay(1000); //wait for setting the bot on position  

}  

void loop() {  
error = calculateError();
calculatePID();
controlMotors();
lastError = error;

int calculateError() {  
// Read sensor values then accordong to diff cases  
int s1 = digitalRead(S1_PIN);  
int s2 = digitalRead(S2_PIN);  
int s3 = digitalRead(S3_PIN);  
int s4 = digitalRead(S4_PIN);  
int s5 = digitalRead(S5_PIN);  

if (s1 == 0 && s2 == 0 && s3 == 1 && s4 == 0 && s5 == 0) return 0; // Center  
else if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 0 && s5 == 0) return -1; // Slight Right  
else if (s1 == 0 && s2 == 1 && s3 == 0 && s4 == 0 && s5 == 0) return -2; // Right  
else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 0 && s5 == 0) return -3; // Hard Right  
else if (s1 == 1 && s2 == 0 && s3 == 0 && s4 == 0 && s5 == 0) return -4; // Far Right  
else if (s1 == 0 && s2 == 0 && s3 == 1 && s4 == 1 && s5 == 0) return 1; // Slight Left  
else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 1 && s5 == 0) return 2; // Left  
else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 1 && s5 == 1) return 3; // Hard Left  
else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0 && s5 == 1) return 4; // Far Left  
else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0 && s5 == 0) {  
/*Line lost.Use last known error to try to turn back. If lastError was positive, we were on the left, so keep turning right. If lastError was negative, we were on the right, so keep turning left.*/  
if (lastError > 0) return 5; // Turn hard right  
else return -5; // Turn hard left  
}  

else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1) {  
return 0;  
//Intersection or wide black area,just go straight assuming it is not end point  
}  
return lastError;  
}  

void calculatePID() {  
integral = integral + error;  
derivative = error - lastError;  
correction = (Kp * error) + (Ki * integral) + (Kd * derivative);  

// --- Integral Windup Prevention ---  
// If the robot is stuck or off the line for a long time, the  
// 'integral' term can get huge which may cause problem so we need to cap it that bound it when it crosses a partcular value.  
if (integral > 200) integral = 200;  
if (integral < -200) integral = -200;  

}  

void controlMotors() {  
// Calculate final speeds for each motor  
int leftSpeed = BASE_SPEED + correction;  
int rightSpeed = BASE_SPEED - correction;  

// Constrain speeds to the valid PWM range (-255 to 255)  
leftSpeed = constrain(leftSpeed, -255, 255);  
rightSpeed = constrain(rightSpeed, -255, 255);  

// --- Set Left Motor ---  
if (leftSpeed >= 0) {  
// Forward  
digitalWrite(L_IN1, HIGH);  
digitalWrite(L_IN2, LOW);  
analogWrite(L_ENA, leftSpeed);  
}  

else {  
// Reverse  
digitalWrite(L_IN1, LOW);  
digitalWrite(L_IN2, HIGH);  
analogWrite(L_ENA, abs(leftSpeed)); }  

// --- Set Right Motor ---  
if (rightSpeed >= 0) {  
// Forward  
digitalWrite(R_IN3, HIGH);  
digitalWrite(R_IN4, LOW);  
analogWrite(R_ENB, rightSpeed);  
}  

else {  
// Reverse  
digitalWrite(R_IN3, LOW);  
digitalWrite(R_IN4, HIGH); 
analogWrite(R_ENB, abs(rightSpeed));  
//Here i used abs function bcz magnitude of speed has to be positive}  
}  

 
 

 
