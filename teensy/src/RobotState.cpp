#include "../include/RobotState.hpp"
#include <Arduino.h>

RobotState::RobotState(){
	mode = FAILSAFE;
};

void RobotState::rcToMode(int input_1, int input_2){
	switch(input_1){
		case 1:
			mode = FAILSAFE;
			break;
		case 0:
			switch(input_2){
				case -1:
					mode = TANK_DRIVE;
					break;
				case 0:
					mode = MELTY;
					break;
			}
			break;
		case -1:
			switch(input_2){
				case -1:
					mode = RADIUS_ADJUST;
					break;
				case 0:
					mode = TRANSLATION_OFFSET_ADJUST;
					break;
				case 1:
					mode = LED_PATTERN_SELECT;
			}
			break;
	}
};

void RobotState::displayState(){
	switch(mode){
		case FAILSAFE:
			Serial.println("FAILSAFE");
			break;
		case TANK_DRIVE:
			Serial.println("TANK_DRIVE");
			break;
		case MELTY:
			Serial.println("MELTY");
			break;
		case RADIUS_ADJUST:
			Serial.println("RADIUS_ADJUST");
			break;
		case TRANSLATION_OFFSET_ADJUST:
			Serial.println("TRANSLATION_OFFSET_ADJUST");
			break;
		case LED_PATTERN_SELECT:
			Serial.println("LED_PATTERN_SELECT");
			break;
	}
};

RobotMode RobotState::getRobotMode(){
	return mode;
};

void RobotState::setRobotMode(RobotMode _mode){
	mode = _mode;
};
