#include "../include/Receiver.hpp"
#include <Arduino.h>

Receiver::Receiver(ChannelConfig _channel_configs[CHANNEL_COUNT], int _channel_pins[CHANNEL_COUNT]){
	for(int i = 0; i < CHANNEL_COUNT; i++){
		channel_pins[i] = _channel_pins[i];
		channel_configs[i] = _channel_configs[i];
	}

	failsafe_triggered = true;
}

uint16_t Receiver::getPulsewidth(int channel){
	return pulsewidths[channel];
}

float Receiver::getValue(int channel){
	switch(channel_configs[channel].type){
		case TWO_POS:
			return 1;
			break;
		case THREE_POS:
			if(abs(pulsewidths[channel] - channel_configs[channel].min_pulse) <= SWITCH_POS_THRESHOLD){
				return 1;
			}
			else if(abs(pulsewidths[channel] - channel_configs[channel].middle_pulse) <= SWITCH_POS_THRESHOLD){
				return 0;
			}
			else if(abs(pulsewidths[channel] - channel_configs[channel].max_pulse) <= SWITCH_POS_THRESHOLD){
				return -1;
			}
			break;
		case STICK:
			if(pulsewidths[channel] <= channel_configs[channel].min_pulse){
				return -1;
			}
			
			if(pulsewidths[channel] >= channel_configs[channel].max_pulse){
				return 1;
			}

			float pulse_error = pulsewidths[channel] - channel_configs[channel].middle_pulse;
			
			if(abs(pulse_error) < PULSE_DEADZONE){
				return 0;
			}

			if(pulse_error < 0){
				return pulse_error / (channel_configs[channel].middle_pulse - channel_configs[channel].min_pulse);
			} else {
				return pulse_error / (channel_configs[channel].max_pulse - channel_configs[channel].middle_pulse);
			}

			break;
	}

	return 0;
}

bool Receiver::inFailsafe(){
	if(millis() - last_pulse_time > FAILSAFE_THRESHOLD){
		failsafe_triggered = true;
	} else {
		failsafe_triggered = false;
	}
	return failsafe_triggered;
}

void Receiver::displayPulsewidths(){
	for (int i = 0; i < CHANNEL_COUNT; i++){
		Serial.print(pulsewidths[i]);
		Serial.print(",");
	}

	Serial.print(millis() - last_pulse_time);
	Serial.print(", ");

	if(failsafe_triggered){
		Serial.print("FAILSAFE HAS BEEN TRIGGERED");
	}

	Serial.println();
}

void Receiver::displayValues(){
	for (int i = 0; i < CHANNEL_COUNT; i++){
		Serial.print(getValue(i));
		Serial.print(",");
	}

	if(failsafe_triggered){
		Serial.print("FAILSAFE HAS BEEN TRIGGERED");
	}

	Serial.println();
}

void Receiver::isr(int channel){
	uint8_t current_state = digitalRead(channel_pins[channel]);
	
	if(current_state == 1){
		pulse_starts[channel] = micros();
	} else {
		pulsewidths[channel] = (uint16_t)(micros() - pulse_starts[channel]);
	}
	
	last_pulse_time = millis();
}
