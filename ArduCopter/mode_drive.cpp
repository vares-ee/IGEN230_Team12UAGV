#include "Copter.h"

bool ModeDrive::init(bool ignore_checks)
{	
	if (coptor.ap.land_complete)//check if landed
	{
		AP_MotorsMatrix::disable_enable(false);//turn off propellor motors, turn on drive motors
		return true;
	} 
	else
	{
		gcs().send_text(MAV_SEVERITY_CRITICAL, "Must be landed to switch to Rover");
		return false;//refuse to switch to rover if not landed
	}
}

void ModeDrive::run()
{
    if (!motors->armed())
    {
        // Motors should be Stopped
        motors->set_desired_spool_state(AP_Motors::DesiredSpoolState::SHUT_DOWN);
    }

    ModeDrive::get_pilot_input()
}

//add this prototype to class def
void ModeDrive::get_pilot_input()
{
    //Some PWM signal between 900 and 2100
    //set_output_norm() found in SRV_CHANNEL
    //force it to between 0 and 1
    driveModeOutputs[SteeringOut] = (channel_roll->get_control_in() - 900) / (2100 - 900);

    // some value between 0 and 1
    //pwm_from_range found in SRV_CHANNEL
    //becomes throttle actuator value
    //function(actuator, value)
    driveModeOutputs[ThrottleOut] = Mode::get_pilot_desired_throttle();
}

void exit()
{
    AP_MotorsMatrix::disable_enable(true);
}