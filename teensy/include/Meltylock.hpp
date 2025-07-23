#ifndef _MELTYLOCK
#define _MELTYLOCK

#include <SparkFun_LIS331.h>
#include <Wire.h>

enum HeadingState{
	HEADING_LEFT,
	HEADING_RIGHT
};

struct Vector{
	float x;
	float y;
	float m;
};

class Meltylock{
	private:
		LIS331 accel;
		float radius; // Radius of accelerometer from centre of rotation
		float translation_offset; // Switching point of motors relative to heading
		
		// Control Parameters
		float steering; // Adds steering offset to robots heading
		float radius_adjust;
		float translation_offset_adjust;

		Vector last_acceleration;

		volatile float ang_vel; // Angular velocity
		volatile float h_error; // Heading error
		volatile HeadingState heading_state; // Heading state: Left or Right of robot front
		volatile unsigned long last_update_time; // Time since last update
	public:
		Meltylock(float _radius, float _translation_offset);

		void readAccelerometer();
		void setAngularVelocity();
		
		// setLastUpdateTime must be run right after update methods
		void updateHeadingError();
		void updateParameters();
		void setLastUpdateTime();

		float getHeading();
		HeadingState getHeadingState();
		float getAcceleration();


		void shiftHeading(float angle);
		void setHeadingState();

		void setSteering(float _steering);
		void adjustRadius(float _radius_adjust);
		
		void displayRadius();
		void displayAcceleration();
		void displayAngularVelocity();
};

#endif
