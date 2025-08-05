#include "../include/Meltylock.hpp"

#include "../include/Constants.hpp"

Meltylock::Meltylock(float _radius, float _translation_offset){
	Wire.begin();
	Wire.setTimeout(ACCELEROMETER_TIMEOUT_US);

	accel.setI2CAddr(0x19);
	accel.setFullScale(LIS331::HIGH_RANGE);
	accel.setODR(LIS331::DR_400HZ);
	accel.begin(LIS331::USE_I2C);
	accel.axesEnable(true);
  	accel.setHighPassCoeff(LIS331::HPC_16); 

	radius = _radius;
	translation_offset = _translation_offset;

	steering = 0;
	radius_adjust = 0;
	translation_offset_adjust = 0;
	
	last_update_time = 0;
	last_accel_time = 0;

	last_acceleration = {
		.x = 0,
		.y = 0,
		.m = 0
	};
}


void Meltylock::readAccelerometer(){
	if(accel.newXData() || accel.newYData()){
		int16_t x, y, z;

		last_accel_time = micros();
		accel.readAxes(x, y, z);

		// If the accelerometer read has taken too long, reset I2C comms to refresh accelerometer
		if(micros() - last_accel_time  >= ACCELEROMETER_TIMEOUT_US){
			Wire.end();
			delay(10);
			Wire.begin();
		}

		last_acceleration.x = accel.convertToG(400, x) * 9.81;
		last_acceleration.y = accel.convertToG(400, y) * 9.81;
	}
}

void Meltylock::calculateAngularVelocity(float translation){
	last_acceleration.m = sqrt(last_acceleration.x*last_acceleration.x + last_acceleration.y*last_acceleration.y);
	ang_vel = sqrt(last_acceleration.m * 1000/abs(radius)) * RAD_TO_DEG * (1 + (translation * translation_offset_adjust));
}

void Meltylock::updateParameters(float d_radius, float d_translation_offset){
	radius += d_radius;
	translation_offset += d_translation_offset;
}

void Meltylock::updateHeading(float d_angle){
	h_error -= d_angle;
	while(h_error > 180){
		h_error -= 360;
	} 

	while(h_error < -180){
		h_error += 360;
	}	
}

void Meltylock::updateHeadingState(float translation_angle){
	float t_error = h_error + translation_angle;
	
	if(t_error > 0 && t_error < 180){
		heading_state = HEADING_RIGHT;
	} else {
		heading_state = HEADING_LEFT;
	}
}

void Meltylock::update(){
	float delta_t = (float)(micros() - last_update_time) / 1000000.0f;

	// Update heading
	updateHeading((ang_vel + steering * STEER_SPEED) * delta_t);
	
	// Adjust meltylock parameters
	updateParameters(radius_adjust * RADIUS_ADJUST_SPEED * delta_t, translation_offset_adjust * TRANSLATION_OFFSET_ADJUST_SPEED * delta_t);
	
	// Set last update time
	last_update_time = micros();
}


float Meltylock::getHeading(){
	return h_error;
}

HeadingState Meltylock::getHeadingState(){
	return heading_state;
}

float Meltylock::getAcceleration(){
	return last_acceleration.m;
}


void Meltylock::setSteering(float _steering){
	steering = _steering;
}


void Meltylock::adjustRadius(float _radius_adjust){
	radius_adjust = _radius_adjust;
}

void Meltylock::adjustTranslationOffset(float _translation_offset_adjust){
	translation_offset_adjust = _translation_offset_adjust;
}

void Meltylock::displayRadius(){
	Serial.print("Radius: ");
	Serial.println(radius, 10);
}

void Meltylock::displayTranslationOffset(){
	Serial.print("Translation Offset:");
	Serial.println(translation_offset, 10);
}

void Meltylock::displayAcceleration(){
	//Serial.print("Acceleration: "); 
	Serial.print(last_acceleration.x);
	Serial.print(",");
	Serial.print(last_acceleration.y);
	Serial.print(",");
	Serial.println(last_acceleration.m);
}

void Meltylock::displayAngularVelocity(){
	Serial.println(ang_vel);
}



