#include <iostream>
#include <math.h>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "face.h"

face::face(int width_, int height_, double pixel_size_)
{
	width = width_;
	height = height_;

	pixel_size = pixel_size_;

	eye_radius = 3*(height_/16);
	eyelid_radius = height_/16;

	focal_distance = 0.05;

	cv::namedWindow("Face", cv::WINDOW_AUTOSIZE);
	for(int i = 1; i <= 5; i++)
	{
		face::expression(i);
		cv::waitKey(100);
	}
}

//_________________________________________________________________________________________________

face::face()
{

}

//_________________________________________________________________________________________________

face::~face()
{

}

//_________________________________________________________________________________________________

void face::follow(int x, int y)
{
	cv::Mat face = cv::Mat(width, height, CV_8UC1, 1);

	int x_eye = x*((2*eye_radius))/640; //That converts the x coordinate from the image to coordinates in a imaginary square with edge equivalent to the diameter of the eye
	int y_eye = y*((2*eye_radius))/480;//That converts the y coordinate from the image to coordinates in a imaginary square with edge equivalent to the diameter of the eye

	int final_x_left = ((width/4) + eye_radius - x_eye); //This makes the x coordinate of the left eye start from origin of the imaginary square 
	int final_x_right = ((3*width/4) + eye_radius - x_eye);	//This makes the x coordinate of the right eye start from origin of the imaginary square
	int final_y = ((height/3) - eye_radius + y_eye); //This stets the y coordinate, which is the same for both eyes.

	//std::cout << "final x left: " << final_x_left << "  final x right: " << final_x_right << "  final y: " << final_y << std::endl;

	if(((final_x_left > (width/4)-eye_radius) && (final_x_left < (width/4)+eye_radius)) && ((final_y > (height/3)-eye_radius) && (final_y < (height/3)+eye_radius))) //Seeing if they are inside of the imaginary squares
	{
		//It prints a happy face with the eyes looking at the ball position
		cv::circle(face, cv::Point(width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Left eye
		cv::circle(face, cv::Point(3*width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Right eye
			
		cv::circle(face, cv::Point(final_x_left, final_y), eyelid_radius, cv::Scalar(0, 0, 0), -1, 8); //Left eyelid
		cv::circle(face, cv::Point(final_x_right, final_y), eyelid_radius, cv::Scalar(0, 0, 0), -1, 8); //Right eyelid

		cv::ellipse(face, cv::Point(width/2, height/2), cv::Size(width/2, height/3), 180, 200, 340, cv::Scalar(200, 200, 200), 3, 8); //Mouth

		cv::ellipse(face, cv::Point(width/4, height/3.8), cv::Size(width/4, height/6), 0, 220, 330, cv::Scalar(200, 200, 200), 3, 8); //Left eyebrow
		cv::ellipse(face, cv::Point(3*width/4, height/3.8), cv::Size(width/4, height/6), 0, 210, 320, cv::Scalar(200, 200, 200), 3, 8); //Right eyebrow

		cv::imshow("Face", face);
		cv::waitKey(20);
	}
	else
	{
		face::expression(4); //Set the sad expression
	}

}

//_________________________________________________________________________________________________

void face::look_at(double x, double y, double z)
{
	cv::Mat face = cv::Mat(width, height, CV_8UC1, 1); //Creating a one channel matrix to store the face

	double final_screen_y_left, final_screen_y_right, final_screen_z, screen_y, screen_z; //Declaring the variables we are going to use during the conversions

	//Getting the distance in meters to the centre of the screen. Just using similar triangles to get the mesure.
	screen_y = (focal_distance*y)/x; 
	screen_z = (focal_distance*z)/x;
	//std::cout << screen_y << "  " << screen_z << std::endl;

	//Getting the distance in pixels (with the double of the given the pixel size). 
	screen_y = screen_y/(pixel_size*2);
	screen_z = screen_z/(pixel_size*2);

	//std::cout << screen_y << "  " << screen_z << std::endl;

	//Converting coordiantes in pixels to coordinates in the screen (we are using coordinates form centre, but the origin of coordinates in the screen is int the left top corner)
	screen_y = width/2 - screen_y; //We have to substract the coordinates from centre of the screen
	screen_z = height/2 + screen_z; //As the z axis from centre is inverted on the screen, we have to add the coordnates from centre of the screen

	//std::cout << screen_y << "  " << screen_z << std::endl;

	//Converting screen coordinates to coordinates from imaginary boxes at the eyes.
	screen_y = screen_y*2*eye_radius/width;
	screen_z = screen_z*2*eye_radius/height;

	//std::cout << screen_y << "  " << screen_z << std::endl;

	//Setting the eyes coordinates to start from origin, at the left top corner.
	final_screen_y_left = ((width/4) + eye_radius - screen_y);
	final_screen_y_right = ((3*width/4) + eye_radius - screen_y);
	final_screen_z = ((height/3) + eye_radius - screen_z);

	std::cout << final_screen_y_left << "  " << final_screen_z << std::endl;


	//Finally, printing the face
	cv::circle(face, cv::Point(width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Left eye
	cv::circle(face, cv::Point(3*width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Right eye
		
	cv::circle(face, cv::Point(final_screen_y_left, final_screen_z), eyelid_radius, cv::Scalar(0, 0, 0), -1, 8); //Left eyelid
	cv::circle(face, cv::Point(final_screen_y_right, final_screen_z), eyelid_radius, cv::Scalar(0, 0, 0), -1, 8); //Right eyelid

	cv::ellipse(face, cv::Point(width/2, height/2), cv::Size(width/2, height/3), 180, 200, 340, cv::Scalar(200, 200, 200), 3, 8); //Mouth

	cv::ellipse(face, cv::Point(width/4, height/3.8), cv::Size(width/4, height/6), 0, 220, 330, cv::Scalar(200, 200, 200), 3, 8); //Left eyebrow
	cv::ellipse(face, cv::Point(3*width/4, height/3.8), cv::Size(width/4, height/6), 0, 210, 320, cv::Scalar(200, 200, 200), 3, 8); //Right eyebrow

	cv::imshow("Face", face);
	cv::waitKey(2000);

}

//_________________________________________________________________________________________________

void face::look_at2(double x, double y, double z)
{
	double ue_x, ue_y, ue_z; // Left eye reference frame
	double ud_x, ud_y, ud_z; // Right eye reference frame

	// Pose of the Left Eye respect Center of the Face
	ue_x = -width/4;
	ue_y = -height/3;
	ue_z = -focal_distance/(pixel_size);
	// Pose of the Right Eye respect Center of the Face
	ud_x =  width/4;
	ud_y = -height/3;
	ud_z = -focal_distance/(pixel_size);

	double pe_x, pe_y, pe_z;
	double pd_x, pd_y, pd_z;

	// Goal point coordinate from the point of view of each of the eyes
	// Left
    pe_x = x - ue_x*pixel_size; // passing from pixels to meters
    pe_y = y - ue_y*pixel_size;
    pe_z = z - ue_z*pixel_size;
    // Right
    pd_x = x - ud_x*pixel_size;
    pd_y = y - ud_y*pixel_size;
    pd_z = z - ud_z*pixel_size;

    std::cout << "metres esquerre: " << pe_x << ", " << pe_y << ", " << pe_z << std::endl;   
    std::cout << "metres dreta: " << pd_x << ", " << pd_y << ", " << pd_z << std::endl;

    double iris_ex, iris_ey;
    double iris_dx, iris_dy;

    iris_ex = ue_x - ((focal_distance*pe_x)/pe_z)/(pixel_size); //
    iris_ey = ue_y + ((focal_distance*pe_y)/pe_z)/(pixel_size); // 

    iris_dx = ud_x -((focal_distance*pd_x)/pd_z)/(pixel_size); // 
    iris_dy = ud_y + ((focal_distance*pd_y)/pd_z)/(pixel_size); // 

    //iris_ex = iris_ex*2*eye_radius/width;
    //iris_ey = iris_ey*2*eye_radius/height;
    //iris_dx = iris_dx*2*eye_radius/width;
    //iris_dy = iris_dy*2*eye_radius/height;
  
    iris_ex = ((width/2) + iris_ex);
    iris_ey = ((height/2) + iris_ey);
    iris_dx = ((width/2) + iris_dx);
    iris_dy = ((height/2) + iris_dy);
 

    std::cout << "iris esquerre: " << iris_ex << ", " << iris_ey << std::endl;
    std::cout << "iris dreta: " << iris_dx << ", " << iris_dy << std::endl;

	cv::Mat face = cv::Mat(width, height, CV_8UC3, 1); //Creating a one channel matrix to store the face


	//Finally, printing the face
	cv::circle(face, cv::Point(width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Left eye
	cv::circle(face, cv::Point(3*width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Right eye
		
	cv::circle(face, cv::Point(iris_ex, iris_ey), eyelid_radius, cv::Scalar(250, 0, 0), -1, 8); //Left eyelid
	cv::circle(face, cv::Point(iris_dx, iris_dy), eyelid_radius, cv::Scalar(0, 250, 0), -1, 8); //Right eyelid

	cv::ellipse(face, cv::Point(width/2, height/2), cv::Size(width/2, height/3), 180, 200, 340, cv::Scalar(200, 200, 200), 3, 8); //Mouth

	cv::ellipse(face, cv::Point(width/4, height/3.8), cv::Size(width/4, height/6), 0, 220, 330, cv::Scalar(200, 200, 200), 3, 8); //Left eyebrow
	cv::ellipse(face, cv::Point(3*width/4, height/3.8), cv::Size(width/4, height/6), 0, 210, 320, cv::Scalar(200, 200, 200), 3, 8); //Right eyebrow

	cv::imshow("Face", face);
	cv::waitKey(2000);

}


//_________________________________________________________________________________________________

void face::expression(int face)
{
	switch (face)
	{
		case 1: //Happy
		{
			cv::Mat face = cv::Mat(width, height, CV_8UC1, 1);

			cv::circle(face, cv::Point(width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Left eye
			cv::circle(face, cv::Point(3*width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Right eye
			cv::circle(face, cv::Point(width/4, height/3), eyelid_radius, cv::Scalar(0, 0, 0), -1, 8); //Left eyelid
			cv::circle(face, cv::Point(3*width/4, height/3), eyelid_radius, cv::Scalar(0, 0, 0), -1, 8); //Right eyelid
			
			cv::ellipse(face, cv::Point(width/2, height/2), cv::Size(width/2, height/3), 180, 200, 340, cv::Scalar(200, 200, 200), 3, 8); //Mouth

			cv::ellipse(face, cv::Point(width/4, height/3.8), cv::Size(width/4, height/6), 0, 220, 330, cv::Scalar(200, 200, 200), 3, 8); //Left eyebrow
			cv::ellipse(face, cv::Point(3*width/4, height/3.8), cv::Size(width/4, height/6), 0, 210, 320, cv::Scalar(200, 200, 200), 3, 8); //Right eyebrow

			cv::imshow("Face", face);
			cv::waitKey(20);
			break;
		}
		case 2: //Surprised
		{
			cv::Mat face = cv::Mat(width, height, CV_8UC1, 1);
			cv::circle(face, cv::Point(width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Left eye
			cv::circle(face, cv::Point(3*width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Right eye
			cv::circle(face, cv::Point(width/4, height/3), eyelid_radius, cv::Scalar(0, 0, 0), -1, 8); //Left eyelid
			cv::circle(face, cv::Point(3*width/4, height/3), eyelid_radius, cv::Scalar(0, 0, 0), -1, 8); //Right eyelid

			cv::circle(face, cv::Point(width/2, height/1.3), 80, cv::Scalar(200, 200, 200), 1, 8); //Mouth

			cv::ellipse(face, cv::Point(width/4, height/5), cv::Size(width/4, height/5), 0, 220, 330, cv::Scalar(200, 200, 200), 3, 8); //Left eyebrow
			cv::ellipse(face, cv::Point(3*width/4, height/5), cv::Size(width/4, height/5), 0, 210, 320, cv::Scalar(200, 200, 200), 3, 8); //Right eyebrow

			cv::imshow("Face", face);
			cv::waitKey(20);
			break;
		}

		case 3: //Angry
		{
			cv::Mat face = cv::Mat(width, height, CV_8UC1, 1);

			cv::circle(face, cv::Point(width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Left eye
			cv::circle(face, cv::Point(3*width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Right eye
			cv::circle(face, cv::Point(width/4, height/3), eyelid_radius, cv::Scalar(0, 0, 0), -1, 8); //Left eyelid
			cv::circle(face, cv::Point(3*width/4, height/3), eyelid_radius, cv::Scalar(0, 0, 0), -1, 8); //Right eyelid

			cv::ellipse(face, cv::Point(width/2, height), cv::Size(width/2, height/3), 0, 200, 340, cv::Scalar(200, 200, 200), 3, 8); //Mouth

			cv::ellipse(face, cv::Point(width/4, height/5), cv::Size(width/4, height/5), 0, 260, 360, cv::Scalar(200, 200, 200), 3, 8); //Left eyebrow
			cv::ellipse(face, cv::Point(3*width/4, height/5), cv::Size(width/4, height/5), 0, 180, 270, cv::Scalar(200, 200, 200), 3, 8); //Right eyebrow

			cv::imshow("Face", face);
			cv::waitKey(20);
			break;
		}
		case 4: //Sad
		{
			cv::Mat face = cv::Mat(width, height, CV_8UC1, 1);

			cv::circle(face, cv::Point(width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Left eye
			cv::circle(face, cv::Point(3*width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Right eye
			cv::circle(face, cv::Point(width/4, height/3), eyelid_radius, cv::Scalar(0, 0, 0), -1, 8); //Left eyelid
			cv::circle(face, cv::Point(3*width/4, height/3), eyelid_radius, cv::Scalar(0, 0, 0), -1, 8); //Right eyelid

			cv::ellipse(face, cv::Point(width/2, height), cv::Size(width/2, height/3), 0, 210, 330, cv::Scalar(200, 200, 200), 3, 8); //Mouth

			cv::ellipse(face, cv::Point(width/4, height/5), cv::Size(width/4, height/7), 0, 210, 315, cv::Scalar(200, 200, 200), 3, 8); //Left eyebrow
			cv::ellipse(face, cv::Point(3*width/4, height/5), cv::Size(width/4, height/7), 0, 225, 330, cv::Scalar(200, 200, 200), 3, 8); //Right eyebrow

			cv::imshow("Face", face);
			cv::waitKey(20);
			break;
		}
		case 5: //Scared
		{
			cv::Mat face = cv::Mat(width, height, CV_8UC1, 1);

			cv::circle(face, cv::Point(width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Left eye
			cv::circle(face, cv::Point(3*width/4, height/3), eye_radius, cv::Scalar(200, 200, 200), -1, 8); //Right eye
			cv::circle(face, cv::Point(width/4, height/3), eyelid_radius+15, cv::Scalar(0, 0, 0), -1, 8); //Left eyelid
			cv::circle(face, cv::Point(3*width/4, height/3), eyelid_radius+15, cv::Scalar(0, 0, 0), -1, 8); //Right eyelid

			cv::ellipse(face, cv::Point(width/2, height/1.2), cv::Size(width/2, height/4), 0, 0, 360, cv::Scalar(200, 200, 200), 3, 8); //Mouth

			cv::ellipse(face, cv::Point(width/4, height/7), cv::Size(width/4, height/7), 0, 210, 315, cv::Scalar(200, 200, 200), 3, 8); //Left eyebrow
			cv::ellipse(face, cv::Point(3*width/4, height/7), cv::Size(width/4, height/7), 0, 225, 330, cv::Scalar(200, 200, 200), 3, 8); //Right eyebrow

			cv::imshow("Face", face);
			cv::waitKey(20);

			break;
		}
	}
}

//_________________________________________________________________________________________________