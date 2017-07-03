#ifndef _ROBOHEAD_H
#define _ROBOHEAD_H

#include "mechanical.h"
#include "visual_analysis.h"
#include "face.h"

/** \defgroup robohead robohead_drivers
 *\class robohead
 *\ingroup robohead
 *\brief Class robohead.
 *
 * A class with the most basic methods for controlling and using a robotic head.
 * The goal of this project is to make the human-robot interaction more fluid and pleasant for the user. Adding a head to the robot, it will be able to show different expressions,
 * look at the user and moving the head according to his body, getting in this way a more natural behaviour.   
 * This driver includes the necessary movment, image analysis and interface libraries to control the head. 
 *
 *\author Aniol Garcia i Serrano
 *Contact: aniolgarcia@gmail.com
 *\version 0.1
 */



class CRobohead
{

  public:

	//--------------- CONSTRUCTOR & DESTRUCTOR -------------//

	/**
	 *\brief Main constructor of the robohead class 
	 *It configures other objects such as mechanical, visual_analysis and face ones.
	 *
	 */
	CRobohead();

	/**
	 *\brief Destructor of the robohead class
	 *
	 */
	~CRobohead();

	//------------- METHODS ---------------//

	/**
	 *\brief The head will follow the biggest face that visual_analysis is able to find.
	 *
	 */
	void follow_face();

	/**
	 *\brief The head will follow an orange ball, used in testing.
	 *
	 */
	void follow_ball();

	/**
	 *\brief The head will follow a specific colour
	 * It follows a color given range of it in HSV system.
	 *
	 *\param min_H_ Minimum hue to search
	 *\param max_H_ Maximum hue to search
	 *\param min_S_ Minimum saturatuion to search
	 *\param max_S_ Maximum saturatuion to search
	 *\param min_V_ Minimun color valur to search
	 *\param max_V_ Maximum color value to search
	 */
	void follow_color(int min_H_, int max_H_, int min_S_, int max_S_, int min_V_, int max_V_);

	/**
	 *\todo Write the code for robohead::orient_to
	 *\brief It moves the head to given coordinates from the space.
	 *\param x The x coordinate from the space
	 *\param y The y coordinate from the space
	 *\param z The z coordinate from the space
	 *
	 */
	void orient_to(int x, int y, int z); //TO DO!

	/**
	 *\brief It moves the eyes to look at given coordinates from the space.
	 *\param x The x coordinate from the space in meters
	 *\param y The y coordinate from the space in meters
	 *\param z The z coordinate from the space in meters
	 *
	 */
	void look_at(double x,  double y,  double z);

	void look_at2(double x, double y, double z);

	/**
	 *\brief The face shows an expression.
	 *\param face An int that refers to an expression according to the following table.
	 * 1.- Happiness 
	 * 2.- Surprise
	 * 3.- Anger
	 * 4.- Sadness
	 * 5.- Fear
	 *
	 */
	void expression(int face);

  private:

	mechanical neck;
	face digital_face;
	visual_analysis camera;

};

#endif
