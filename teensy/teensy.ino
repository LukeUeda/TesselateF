#include "include/Constants.hpp"
#include "include/Config.hpp"

#include "include/Motor.hpp"
#include "include/LedController.hpp"
#include "include/Receiver.hpp"
#include "include/Meltylock.hpp"
#include "include/RobotState.hpp"

Motor leftMotor(LEFT_MOTOR_CONFIG);
Motor rightMotor(RIGHT_MOTOR_CONFIG);

LedController ledController(LED_PINS);

Receiver receiver(CHANNEL_CONFIGS, CHANNEL_PINS);

Meltylock meltylock(ACCEL_RADIUS, TRANSLATION_OFFSET);
//IntervalTimer meltylockTimer; // Timer to ensure periodic running of essential processes

float max_accel = 0;

RobotState robotState;

void setup(){
  // Set up PPM control of VESCS
  analogWriteResolution(ANALOG_WRITE_RESOLUTION_BITS);
  analogWriteFrequency(LEFT_MOTOR_CONFIG.pin, ANALOG_WRITE_FREQUENCY);
  analogWriteFrequency(RIGHT_MOTOR_CONFIG.pin, ANALOG_WRITE_FREQUENCY);

  // Attach interrupts to receiver pins for reading pulsewidths
	attachInterrupt(CHANNEL_PINS[0], ISR_Channel_0, CHANGE);
	attachInterrupt(CHANNEL_PINS[1], ISR_Channel_1, CHANGE);
	attachInterrupt(CHANNEL_PINS[2], ISR_Channel_2, CHANGE);
	attachInterrupt(CHANNEL_PINS[3], ISR_Channel_3, CHANGE);
	attachInterrupt(CHANNEL_PINS[4], ISR_Channel_4, CHANGE);
	attachInterrupt(CHANNEL_PINS[5], ISR_Channel_5, CHANGE);
  
  // Setup timer ISR for melty lock
  //meltylockTimer.begin(ISR_Melty_Lock, MELTYLOCK_ISR_INTERVAL);

  Serial.begin(9600);
}

void loop(){
  
  // Setting robot mode
  if(receiver.inFailsafe()){ // Failsafe triggered by receiver channel failure
    robotState.setRobotMode(FAILSAFE);
  } else {
    robotState.rcToMode(receiver.getValue(5), receiver.getValue(4));
  }

  // Robot mode operations
  switch(robotState.getRobotMode()){
    case FAILSAFE:
      leftMotor.disable();
      rightMotor.disable();

      ledController.setPattern(FAILSAFE_PATTERN);
      break;
    case TANK_DRIVE:
      leftMotor.enable();
      rightMotor.enable();

      leftMotor.setReverse(true);
      rightMotor.setReverse(true);
      
      leftMotor.setSetpoint(-receiver.getValue(2) - receiver.getValue(1));
      rightMotor.setSetpoint(-receiver.getValue(2) + receiver.getValue(1));
      
      ledController.setPattern(LOADING);
      break;
    case MELTY:
      leftMotor.enable();
      rightMotor.enable();

      leftMotor.setReverse(true);
      rightMotor.setReverse(false);
      
      // Steering
      meltylock.setSteering(receiver.getValue(1));

      // Spin and Translation
      if(meltylock.getHeadingState() == HEADING_LEFT){
        leftMotor.setSetpoint(receiver.getValue(3) + TRANSLATE_DECEL_FACTOR * receiver.getValue(2));
        rightMotor.setSetpoint(-receiver.getValue(3) + TRANSLATE_ACCEL_FACTOR * receiver.getValue(2));
      } else {
        leftMotor.setSetpoint(receiver.getValue(3) - TRANSLATE_ACCEL_FACTOR * receiver.getValue(2));
        rightMotor.setSetpoint(-receiver.getValue(3) - TRANSLATE_DECEL_FACTOR * receiver.getValue(2));
      }

      ledController.setPattern(SIMPLE_ARC);
      break;
    case RADIUS_ADJUST:
      leftMotor.enable();
      rightMotor.enable();

      leftMotor.setReverse(true);
      rightMotor.setReverse(false);
      
      // Radius Adjust
      meltylock.adjustRadius(receiver.getValue(1));

      // Spin
      leftMotor.setSetpoint(receiver.getValue(3));
      rightMotor.setSetpoint(-receiver.getValue(3));

      ledController.setPattern(SIMPLE_ARC);
      break;
    default:
      leftMotor.disable();
      rightMotor.disable();
  }

  meltylock.readAccelerometer();

  ISR_Melty_Lock();

  // Debug Messages
  if(DEBUG){
    //receiver.displayValues();
    //receiver.displayPulsewidths();
    //robotState.displayState();
    //meltylock.displayAcceleration();
    //meltylock.displayAngularVelocity();
    meltylock.displayRadius();
    if(meltylock.getAcceleration() > max_accel){
      max_accel = meltylock.getAcceleration();
    }
    //Serial.println(max_accel);
    //Serial.println(meltylock.getHeading());
  }
}

// Interrupt driven functions: Reciever channels and essential meltylock processes
void ISR_Channel_0(){ receiver.isr(0); }
void ISR_Channel_1(){ receiver.isr(1); }
void ISR_Channel_2(){ receiver.isr(2); }
void ISR_Channel_3(){ receiver.isr(3); }
void ISR_Channel_4(){ receiver.isr(4); }
void ISR_Channel_5(){ receiver.isr(5); }

void ISR_Melty_Lock(){
  meltylock.updateParameters();           // Radius and translation offset adjusted
  meltylock.setAngularVelocity();         // Calculate most current angular velocity
  meltylock.updateHeadingError();         // Apply angular velocity to heading error
  ledController.updateLed(meltylock.getHeading());  // Update leds for current heading error
  meltylock.setLastUpdateTime();
}
