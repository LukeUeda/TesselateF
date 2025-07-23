#include "../include/Meltylock.hpp"

#include "../include/Constants.hpp"

Meltylock::Meltylock(float _radius, float _translation_offset){
	Wire.begin();
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

	last_acceleration = {
		.x = 0,
		.y = 0,
		.m = 0
	};
}


void Meltylock::readAccelerometer(){
	if(accel.newXData() || accel.newYData()){
		int16_t x, y, z;

		accel.readAxes(x, y, z);

		last_acceleration.x = accel.convertToG(400, x) * 9.81;
		last_acceleration.y = accel.convertToG(400, y) * 9.81;
	}
}

void Meltylock::setAngularVelocity(){
	last_acceleration.m = sqrt(last_acceleration.x*last_acceleration.x + last_acceleration.y*last_acceleration.y);
	ang_vel = sqrt(last_acceleration.m * 1000/abs(radius)) * RAD_TO_DEG;
}

void Meltylock::updateHeadingError(){
	shiftHeading((ang_vel + steering * STEER_SPEED)* (micros() - last_update_time) / 1000000);
}

void Meltylock::updateParameters(){
	radius += radius_adjust * RADIUS_ADJUST_SPEED * (micros() - last_update_time)/ 1000000;
	translation_offset += translation_offset_adjust * TRANSLATION_OFFSET_ADJUST_SPEED * 
		(micros() - last_update_time);
}

void Meltylock::setLastUpdateTime(){
	last_update_time = micros();
}

float Meltylock::getHeading(){
	return h_error;
}

HeadingState Meltylock::getHeadingState(){
	return heading_state;
}

void Meltylock::shiftHeading(float angle){
	h_error -= angle;
	while(h_error > 180){
		h_error -= 360;
	} 

	while(h_error < -180){
		h_error += 360;
	}

	float t_error = h_error + translation_offset;
	
	if(t_error > 0 && t_error < 180){
		heading_state = HEADING_RIGHT;
	} else {
		heading_state = HEADING_LEFT;
	}
}

void Meltylock::setSteering(float _steering){
	steering = _steering;
}

void Meltylock::adjustRadius(float _radius_adjust){
	radius_adjust = _radius_adjust;
}

void Meltylock::displayRadius(){
	Serial.print("Radius: ");
	Serial.println(radius, 10);
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

float Meltylock::getAcceleration(){
	return last_acceleration.m;
}
