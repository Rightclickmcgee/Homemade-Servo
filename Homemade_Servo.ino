/************************************************************
 * Project Name : Homemade Servo Control
 * File Name    : homemade_servo.ino
 * Author       : Your Name
 * Date Created : YYYY-MM-DD
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
 *   POT_FB  -> A0 (Feedback potentiometer wiper)
 *   POT_CMD -> A1 (Command potentiometer wiper)
 *
 * Notes:
 *   - PWM (analogWrite) is used on ENA for speed control.
 *   - Feedback potentiometer must not be driven into hard stops.
 *   - fbMin/fbMax should be calibrated before running.
 *
 ************************************************************/

// Pin Map

// Motor Driver

const int PIN_IN1 = ; // digital output
const int PIN_IN2 = ; // digital output

const int PIN_ENA = ; // PWM Pin

// Feedback Potentiometer (attached to output gear)

const int PIN_FB = A0; // analog input

// Command Potentiometer (control dial)
const int PIN_CMD = A1; // analog input

// Ranges for Possible Feedback (input read as 10bit value 0-1023)
// We don't know the exact range in degrees of the potentiometer, so we will represent the target value set by the command potentiometer to be a value 0-1024

int FB_Min = 0; // RAW ADC Value Min
int FB_Max = 1023; // RAW ADC Value Max

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
