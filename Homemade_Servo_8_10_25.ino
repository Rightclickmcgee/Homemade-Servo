/************************************************************
 * Project Name : Homemade Servo Control
 * File Name    : homemade_servo.ino
 * Author       : Charlie Aymie, Kyle Colebourn
 * Date Created : 2025-08-09
 * Board        : Arduino Uno (ATmega328P)
 * Description  : 
 *   This sketch controls a DC motor with a motor driver
 *   and feedback potentiometer to act as a homemade servo.
 *   An external potentiometer sets the target position.
 *
 * Hardware:
 *   - Arduino Uno
 *   - DC motor with gearbox
 *   - Motor driver (e.g., L298N or TB6612FNG)
 *   - Potentiometer for feedback (linked to output shaft)
 *   - Potentiometer for control input
 *
 * Pin Assignments:
 *   IN1  -> D5  (Motor driver input 1)
 *   IN2  -> D6  (Motor driver input 2)
 *   ENA  -> D9  (Motor driver enable/PWM)
 *   POT_FB  -> A0 (Feedback potentiometer)
 *   POT_CMD -> A1 (Command potentiometer)
 *
 * Notes:
 *   - PWM (analogWrite) is used on ENA for speed control.
 *   - Feedback potentiometer must not be driven into hard stops.
 *   - fbMin/fbMax should be calibrated before running.
 *
 ************************************************************/

// Pin Map

// Motor Driver

// Input Pins Control Direction of Motor (0 0 & 1 1 = OFF, 1 0 = Forward, 0 1 = Backward in order In1 In2)
const int PIN_IN1 = 5; // digital output
const int PIN_IN2 = 6; // digital output

const int PIN_ENA = 9; // PWM Pin

// Feedback Potentiometer (attached to output gear)

const int PIN_FB = A0; // analog input

// Command Potentiometer (control dial)
const int PIN_CMD = A1; // analog input

// Ranges for Possible Feedback (input read as 10bit value 0-1023)
// We don't know the exact range in degrees of the potentiometer, so we will represent the target value set by the command potentiometer to be a value 0-1023
// *** Need to Observe Min and Max ADC value from potentiometers we buy so that know roughly what ranges to map in code (+-5 or 10 just to be safe)

int FB_Min = 0; // RAW ADC Value Min
int FB_Max = 1023; // RAW ADC Value Max

// Ranges for Command ()

int CMD_Min = 0; // RAW ADC Value Min
int CMD_Max = 1023; // RAW ADC Value Max

// Potentiometer Value Variables

int cmdValue = 0; // Command potentiometer value
int fbValue = 0; // Feedback potentiometer value
int error = 0; // Error between command and feedback
int deadbandRange = 10; // +/- range for target ADC value

void adjust_servo_position() {
  // This function will move the servo from its current position to the desired position
  // Arduino pwm is 8bit Value (0-255)
  // Move fast if far away from target, slower when closer (smooth motion)

  int e = error;
  int a = abs(error);

  // Set direction of  spin (*** Assuming Forward is Clockwise Here - Need to Change if Not ***)
  if (e<0) {
    digitalWrite(PIN_IN1, HIGH);
    digitalWrite(PIN_IN2, LOW);
  } else {
    digitalWrite(PIN_IN1, LOW);
    digitalWrite(PIN_IN2, HIGH);
  }

  // Based on error, set motor speed (8bit PWM w values 0-255)

  if (a>200) {
    analogWrite(PIN_ENA, 200);
  } else if (a>50) {
    analogWrite(PIN_ENA, 120);
  } else {
    analogWrite(PIN_ENA, 80);
  }

}

void setup() {
  // Motor control pins

  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_ENA, OUTPUT);   // Use analogWrite() to initialize PWM
}

void loop() {
  // Read & Map Potentiometers

  int rawCMD = analogRead(PIN_CMD);
  int rawFB = analogRead(PIN_FB);

  cmdValue = map(rawCMD, CMD_Min, CMD_Max, 0, 1023); // Map to common measure of travel
  cmdValue = constrain(cmdValue, 0, 1023); // Constrain in case of overshoot

  fbValue = map(rawFB, FB_Min, FB_Max, 0, 1023); // Map to common measure of travel
  fbValue = constrain(fbValue, 0, 1023); // Constrain in case of overshoot

  // Calculate Error

  error = cmdValue - fbValue;

  // Call Servo adjustment

  if (abs(error) > deadbandRange) {
  adjust_servo_position(); 
  } else {
    // Disable Motor

    analogWrite(PIN_ENA, 0);
    digitalWrite(PIN_IN1, HIGH);
    digitalWrite(PIN_IN2, HIGH);
  }

}
