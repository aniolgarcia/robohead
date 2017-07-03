#ifndef MECHANICAL_H
#define MECHANICAL_H

#include <iostream>
#include <math.h>
#include <dynamixel_pan_tilt.h>
#include <dynamixelserver_ftdi.h>

/**
 *\ingroup robohead
 *\class mechanical
 *\brief Class for controlling a pan & tilt structure
 * This class is specially made for unsing a pan and tilt structure. It includes the methods used to move the motors (together or one by one) ang get information
 * about them, such as their position or maximum and minimum degrees.
 * IMPORTANT: you have to configure the SerialNumber of the usb controller at the class constructor! You can get it from dmesg command.
 *
 */



class mechanical
{
	public:


		//--------------- CONSTRUCTORS & DESTRUCTORS ---------------//

		/**
		 *\brief Main constructor of the class
		 *
		 *\param name A string with the desired name, only used by the pan_tilt object constructor
		 *\param pan_id The id of the pan motor
		 *\param tilt_id The id of the tilt motor
		 *\param config_file A string that contains the path of the .xml config_file
		 *
		 */		
		mechanical(std::string& name, int pan_id, int tilt_id, std::string& config_file);

		/**
		 *\brief A void constructor, useful for declaring it in classes as private.
		 *
		 */
		mechanical();

		/**
		 *\brief The destructor of the class
		 *
		 */
		~mechanical();

		//-------------- METHODS --------------//

		/**
		 *\brief Move the pan motor to a specific degree with the default speed
		 *
		 *\param deg A double containing the desired degrees to move
		 *
		 */
		void move_x(double deg);

		/**
		 *\brief Move the tilt motor to a specific degree with the default speed
		 *
		 *\param deg A double containing the desired degrees to move
		 *
		 */
		void move_y(double deg);

		/**
		 *\brief Add to the pan motor a specific number of degrees from current position
		 *
		 *\param deg A double containing the desired degrees to move
		 *
		 */
		void add_x(double deg);

		/**
		 *\brief Add to the tilt motor a specific number of degrees from current position
		 *
		 *\param deg A double containing the desired degrees to move
		 *
		 */
		void add_y(double deg);

		/**
		 *\brief Move the head to the given coordinates
		 * It gets a position from the image matrix (not from space!) and moves to that position. If you want to move the head a specific position, use mechanical::move.
		 * It's useful when you use it with coordinates from methods of the visual_analysis class, such as get_ball, get_color, get_ball or get_circle.
		 *
		 *\param deg A double containing the desired degrees to move
		 *
		 */
		void follow(double x, double y);

		/**
		 *\brief Move the head to a specific position given in degrees
		 *
		 *\param deg_x A double containing the degree for the pan motor
		 *\param deg_y A double containing the degree for the tilt motor
		 *
		 */
		void move(double& deg_x, double& deg_y);

		/**
		 *\brief Add a specific number of degrees to the current position
		 *
		 *\param deg_x A double containing the desired degrees to move the pan motor
		 *\param deg_y A double containing the desired degrees to move the tilt motor
		 */
		void add(double& deg_x, double& deg_y);

		/**
		 *\brief The whole head returns to the starting position
		 *
		 */
		void start_position();

		/**
		 *\brief Stop both motors
		 *
		 */
		void stop();

		//-------------- GETTERS & SETTERS --------------//

		/**
		 *\brief It sets the speed that will be used in all the movements
		 *
		 *\param speed An integrer between 0 and 355. Constructor of the class will set it to 100.0
		 *
		 */
		void set_default_speed(int speed);

		double get_deg_x(); ///<Returns the position of the pan motor
		double get_deg_y(); ///<Returns the position of the tilt motor


		double max_angle_x(); ///< Getter of the max angle of pan
		double min_angle_x(); ///< Getter of the min angle of pan
		double max_angle_y(); ///< Getter of the max angle of tilt
		double min_angle_y(); ///< Getter of the min angle of tilt

 	
	private: 
		
		double deg_x; 
		double deg_y;		
		double deg;
		double default_speed;

		std::string serial;
		int baudrate;
		Dynamixel_pan_tilt_info info;
  		Dynamixel_pan_tilt_data pos, default_pos, desired_pos, desired_speed, desired_effort;
  		Dynamixel_pan_tilt_config config;
  		Dynamixel_pan_tilt_compliance compliance;
  		Dynamixel_pan_tilt_pid pid;

  		CDynamixelServerFTDI *dyn_server;
  		CDynamixel_Pan_Tilt *pan_tilt;

  		double max_angle_error;
  		double time_interval;
  		double max_time_sec;
  		double t;
  		double uperiod;
  		double step;

  		double timeout;
  		double torque_timeout;
		

}; 


#endif //mechanical_H
