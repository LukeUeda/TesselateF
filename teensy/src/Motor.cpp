#include "../include/Motor.hpp"
#include "../include/Constants.hpp"
#include <Arduino.h>

Motor::Motor(){
	config = {
		.pin = 0,
		.bidirectional = false,
		.reverse = false,
		.max_duty = 0,
		.min_duty = 1,
	};

	pinMode(config.pin, OUTPUT);

	enabled = false;
	setpoint = 0;
	
	if(config.bidirectional){
		duty_cycle = (config.max_duty + config.min_duty)/2;
	} else {
		duty_cycle = config.min_duty;
	}
}

Motor::Motor(MotorConfig _config){
	config = _config;

	pinMode(config.pin, OUTPUT);

	enabled = false;
	setpoint = 0;
}

void Motor::sendControlSignal(){
	analogWrite(config.pin, duty_cycle * ANALOG_WRITE_RESOLUTION);
}

void Motor::setConfig(MotorConfig _config){
	disable(); // Disable to prevent unexpected/unwanted behaviour.
	config = _config;

	pinMode(config.pin, OUTPUT);
}

void Motor::setReverse(bool _reverse){
	if(config.reverse != _reverse){
		config.reverse = _reverse;
	}
}

void Motor::setSetpoint(float _setpoint){
	if(config.bidirectional && config.reverse){
		setpoint *= -1;
	}

	if(_setpoint > 1){
		setpoint = 1;
	}

	if(_setpoint < -1){
		setpoint = -1;
	}

	setpoint = _setpoint;
	
	if(enabled){
		duty_cycle = config.min_duty;
		if(config.bidirectional){
			duty_cycle += (config.max_duty - config.min_duty) * (setpoint + 1)/2;
		} else {
			duty_cycle += (config.max_duty - config.min_duty) * setpoint;
		}

		sendControlSignal();
	}
}

void Motor::enable(){
	enabled = true;
}

void Motor::disable(){
	enabled = false;
	setToStationary();
}

void Motor::setToStationary(){
	if(config.bidirectional){
		duty_cycle = (config.max_duty + config.min_duty)/2;
	} else {
		duty_cycle = config.min_duty;
	}

	sendControlSignal();
}
