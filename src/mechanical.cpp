#include <iostream>
#include <math.h>

#include "mechanical.h"

mechanical::mechanical(std::string& name, int pan_id, int tilt_id, std::string& config_file) //The main constructor of class. It take the name, th id of the servos and the config file.
{
	std::cout << "Starting mechanical constructor..." << std::endl;
	serial="A600cVhY"; //Get it form dmesg command "SerialNumber: A600cVhY"
	baudrate = 1000000;        

	dyn_server=CDynamixelServerFTDI::instance();
	pan_tilt = NULL;
	
	try
	{
		if(dyn_server->get_num_buses()>0)
		{

			std::cout << "Defining variables values..." << std::endl;
			dyn_server->config_bus(serial,baudrate);
			std::cout << "Bus working correctly!" << std::endl;
			pan_tilt = new CDynamixel_Pan_Tilt(name, dyn_server, pan_id, tilt_id);
			std::cout << "Getting config_file..." << std::endl; 

			pan_tilt->load_config(config_file);
			std::cout << "Loading config_file..." << std::endl; 
			pan_tilt->get_pan_tilt_config(config);
			pan_tilt->get_pan_tilt_info(info);

			pan_tilt->get_compliance_control(compliance);
			max_angle_error =  1.8; //fabs(0.7*compliance.pan.cw_compliance_margin); //max angle error permitted
			time_interval   =   0.1; //time in secs between checks
			max_time_sec    =   5.0; //max time to wait until timeout
			uperiod = time_interval*1000000.0;
			timeout = max_time_sec/time_interval;
			torque_timeout = 45.0;
			desired_speed.pan = default_speed; //Set the pan motor speed to default speed
			desired_speed.tilt = default_speed; //Set the tilt motor to default speed

			default_pos = pan_tilt->get_position(); //Save the starting position

			std::cout << "End of inicialitzacion!" << std::endl << std::endl;
		}

		else
		{
			std::cout << "No buses!!! tip: sudo rmmod ftdi_sio" << std::endl;
		}
	}
	catch(CException &e)
	{
		std::cout << "[Genereal exception]: " << e.what() << std::endl;
		if (pan_tilt != NULL)
		{
			pan_tilt->stop();
		}
	}
}

//-________________________________________________________________________________________________

mechanical::mechanical()
{

}

//_________________________________________________________________________________________________

mechanical::~mechanical()
{
	//pan_tilt->stop();
	//delete pan_tilt;
}


//_________________________________________________________________________________________________

double mechanical::get_deg_x() //Get the current Pan position
{
	return pan_tilt->get_pan_position();
}

//_________________________________________________________________________________________________

double mechanical::get_deg_y() //Get the current tilt position
{
	return pan_tilt->get_tilt_position();
}

//_________________________________________________________________________________________________

void mechanical::move_x(double deg) //Move Pan a specific number of degrees with the default speed
{
	pan_tilt->move_absolute_angle_pan(deg, default_speed);
	
	t=0.0;
	pos = pan_tilt->get_position();
	while((fabs(pos.pan - deg) > max_angle_error) && t<timeout)
	{
		pos = pan_tilt->get_position();
		usleep(uperiod);
		t++;
	}
}

//_________________________________________________________________________________________________

void mechanical::move_y(double deg) //Move Tilt a specific number of degrees with the default speed
{
	pan_tilt->move_absolute_angle_tilt(deg, default_speed);
	
	t=0.0;
	pos = pan_tilt->get_position();
	while((fabs(pos.tilt - deg) > max_angle_error) && t<timeout)
	{
		pos = pan_tilt->get_position();
		usleep(uperiod);
		t++;
	}
}

//_________________________________________________________________________________________________

void mechanical::add_x(double deg) //Add Pan a specific number of degrees from current position
{
	pan_tilt->move_relative_angle_pan(deg, default_speed);

	t=0.0;
	pos = pan_tilt->get_position();
	while((fabs(pos.pan - deg) > max_angle_error) && t<timeout)
	{
		pos = pan_tilt->get_position();
		usleep(uperiod);
		t++;
	}
}

//_________________________________________________________________________________________________

void mechanical::add_y(double deg) //Add Tilt a specific number of degrees from current position
{
	pan_tilt->move_relative_angle_tilt(deg, default_speed);

	t=0.0;
	pos = pan_tilt->get_position();
	while((fabs(pos.tilt - deg) > max_angle_error) && t<timeout)
	{
		pos = pan_tilt->get_position();
		usleep(uperiod);
		t++;
	}
}

//_________________________________________________________________________________________________

void mechanical::follow(double x, double y)
{
	std::cout << "follow";
	try
	{
		step = -2.0;
		double back_step = -step;

		//If there are problems with the limits, uncomment the "if" before the movements

		if(x > 0 && x <= 630) //Should be 640, but it only arrives to 630
		{
			if(x < 280) //(640/2) --> Half of the resolution ot the camera
			{
			//if((mechanical::get_deg_x() + step) < mechanical::max_angle_x())
			//{
				std::cout << "Moving right";
				pan_tilt->move_relative_angle_pan(step, default_speed);
				std::cout << "Right";
			//}
			}
			else if(x > 360)
			{
			//if((mechanical::get_deg_x() + back_step) < mechanical::min_angle_x())
			//{
				std::cout << "Moving left"; 
				pan_tilt->move_relative_angle_pan(back_step, default_speed);
				std::cout << "Left "; 
			//}      
			}
			else
			{
			std::cout << "Centre ";
			
			}
			std::cout << x << "  ";
		}
				
		if(y > 0 && y <= 470) //Same of x, should be 480 but it gets 470 as maximum
		{
			if(y  < 210)
			{
			//if((mechanical::get_deg_y() + back_step) > mechanical::min_angle_y())
			//{
				std::cout << "Moving up";
				pan_tilt->move_relative_angle_tilt(back_step, default_speed);
				std::cout << "Up ";
			//}
			}
			else if(y > 260)
			{
			//if((mechanical::get_deg_y() + step) > mechanical::max_angle_y())
			//{
				std::cout << "Moving down";
				pan_tilt->move_relative_angle_tilt(step, default_speed);
				std::cout << "Down ";
			//}
			}
			else
			{
				std::cout << "Centre ";
			}
			std::cout << y << std::endl;
		}
	}
	catch(CException &e)
	{
		std::cout << "[Genereal exception]: " << e.what() << std::endl;
	}
	
}


//_________________________________________________________________________________________________

void mechanical::move(double& deg_x, double& deg_y) //Same as "move" but the two axis at the same time
{
	desired_pos.pan = deg_x;
	desired_pos.tilt = deg_y;
	pan_tilt->move_absolute_angle(desired_pos, desired_speed);

	t=0.0;
	pos = pan_tilt->get_position();
	while((fabs(pos.pan - desired_pos.pan) > max_angle_error || fabs(pos.tilt - desired_pos.tilt) > max_angle_error) && t<timeout)
	{
		pos = pan_tilt->get_position();
		std::cout << "Posicio: ";
		pan_tilt->print_current_position();
		usleep(uperiod);
		t++;
	}
	
}

//_________________________________________________________________________________________________

void mechanical::add(double& deg_x, double& deg_y) //Same as "add" but the two axis at the same time
{
	desired_pos.pan = deg_x;
	desired_pos.tilt = deg_y;
	pan_tilt->move_relative_angle(desired_pos, desired_speed);

	t=0.0;
	pos = pan_tilt->get_position();
	while((fabs(pos.pan - desired_pos.pan) > max_angle_error || fabs(pos.tilt - desired_pos.tilt) > max_angle_error) && t<timeout)
	{
		pos = pan_tilt->get_position();
		std::cout << "Posicio: ";
		pan_tilt->print_current_position();
		usleep(uperiod);
		t++;
	}
}

//_________________________________________________________________________________________________

void mechanical::start_position() //The whole mechanical returns to the starting position
{
	desired_speed.pan = default_speed;
	desired_speed.tilt = default_speed;
	pan_tilt->move_absolute_angle(pos, desired_speed);

	t=0.0;
	pos = pan_tilt->get_position();
	while((fabs(pos.pan - default_pos.pan) > max_angle_error || fabs(pos.tilt - default_pos.tilt) > max_angle_error) && t<timeout)
	{
		pos = pan_tilt->get_position();
		std::cout << "Posicio: ";
		pan_tilt->print_current_position();
		usleep(uperiod);
		t++;
	}
}

//_________________________________________________________________________________________________

void mechanical::set_default_speed(int speed) //Sets the speed of the motors
{
	this->default_speed = speed;
	std::cout << "Default speed: " << speed << std::endl;
}

//_________________________________________________________________________________________________

void mechanical::stop() //Stops the motors
{
	pan_tilt->stop();
}

//_________________________________________________________________________________________________

double mechanical::max_angle_x()
{
	return config.pan.max_angle;
}

//_________________________________________________________________________________________________

double mechanical::min_angle_x()
{
	return config.pan.min_angle;
}

//_________________________________________________________________________________________________

double mechanical::max_angle_y()
{
	return config.tilt.max_angle;
}

//_________________________________________________________________________________________________

double mechanical::min_angle_y()
{
	return config.tilt.min_angle;
}

//_________________________________________________________________________________________________
