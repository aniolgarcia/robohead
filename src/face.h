#ifndef FACE_H
#define FACE_H

#include "eye.h"
#include "eyebrow.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

/**
 *\ingroup robohead
 *\brief A class for drawing a face in the screen
 * This class contain various methods that you can use with a digital face. It can show different faces with different expressions, it can move the eyelids
 * to a specific position or follow something with them (useful with the visual_analysis class) and it can move the eyes to a specific position in the space.
 *
 */

class face
{
	public:

		/**
		 *\brief Main constructor of the face class. 
		 *It sets some variables from the class, and while loading, it shows a scared face. Note: at the moment it works better with squares, height and width should be the same value.
		 *Recomended settings: width and heigth to 400 and pixel size to 0.00028 meters.
		 *\param width The width of the face to be shown
		 *\param height The height of the face to be shown
		 *\param pixel_size The lenght of a pixel edge in meters
		 *
		 */
		face(int width, int height, double pixel_size);

		/**
		 *\brief A void constructor, useful for declaring it in classes as private.
		 *
		 */
		face();

		/**
  		 *\brief Destructor of the class.
  		 *
  		 */
		~face();

		/**
		 *\brief It moves the eyes according to coordinates given from the screen.  
		 *\param x The x coordinate
		 *\param y The y coordinate
		 *
		 */
		void follow(int x, int y);

		/**
		 *\brief It moves the eyes on time according to given coordinates from the space.
		 *\param x The x coordinate from the space in m
		 *\param y The y coordinate from the space in m
		 *\param z The z coordinate from the space in m
		 *
		 */
		void look_at(double x, double y, double z);

		void look_at2(double x, double y, double z);

		/**
		 *\brief The face shows an expression.
		 *\param face An int that refers to an expression according to the following table:
		 * 1.- Happiness 
		 * 2.- Surprise
		 * 3.- Anger
		 * 4.- Sadness
		 * 5.- Fear
		 *
		 */
		void expression(int face);

	private:

		int eye_radius;
		int eyelid_radius;
		int step;

		int width;
		int height;

		double pixel_size;
		double focal_distance;

		int happy;
		int surprised;
		int angry;
		int sad;
		int scared;



};

#endif //FACE_H

