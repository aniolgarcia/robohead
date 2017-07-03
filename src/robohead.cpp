#include "robohead.h"

//_________________________________________________________________________________________________

CRobohead::CRobohead()
{
	std::cout << "Building the head" << std::endl;
	visual_analysis camera;
	digital_face = face(400, 400, 0.00028); 

	std::string name="PAN_TILT_AX_12plus";
	std::string config_file="/home/agarcia/Desktop/Codi/IRI/xml/dyn_pan_tilt_config_AX12plus.xml";
	neck = mechanical(name, 1, 2, config_file);
	neck.set_default_speed(100.0);
}

//_________________________________________________________________________________________________
 
CRobohead::~CRobohead()
{
	std::cout << "Ara em destruiexo" <<std::endl;
}

//_________________________________________________________________________________________________

void CRobohead::follow_face()
{
	try
	{
		cv::Mat img;
		while(1)
		{ 
			double x, y;
			int state;
			camera.get_img(img);
			state = camera.get_face(x, y, img);
			digital_face.follow(x, y);
			//neck.follow(x, y);
			cv::waitKey(30);
		}
	}
	catch(CException &e)
	{
		std::cout << "[Genereal exception]: " << e.what() << std::endl;
	}
}

//_________________________________________________________________________________________________

void CRobohead::follow_ball()
{
	try
	{
		cv::Mat img;
		while(1)
		{ 
			double x, y;
			int state;
			camera.get_img(img);
			state = camera.get_ball(x, y, img);
			digital_face.follow(x, y);
			//neck.follow(x, y);
			cv::waitKey(30);
		}
	}
	catch(CException &e)
	{
		std::cout << "[Genereal exception]: " << e.what() << std::endl;
	}
}

//_________________________________________________________________________________________________

void CRobohead::follow_color(int min_H_, int max_H_, int min_S_, int max_S_, int min_V_, int max_V_)
{
	try
	{
		cv::Mat img;
		while(1)
		{ 
			double x, y;
			int state;
			camera.get_img(img);
			state = camera.get_color(x, y, img, min_H_, max_H_, min_S_, max_S_, min_V_, max_V_);
			digital_face.follow(x, y);
			//neck.follow(x, y);
			cv::waitKey(30);			
		}
	}
	catch(CException &e)
	{
		std::cout << "[Genereal exception]: " << e.what() << std::endl;
	}
}

//_________________________________________________________________________________________________

void CRobohead::look_at(double x, double y, double z)
{
	digital_face.look_at(x, y, z);
}

void CRobohead::look_at2(double x, double y, double z)
{
	digital_face.look_at2(x,y,z);
}

//_________________________________________________________________________________________________

void CRobohead::expression(int face)
{
	digital_face.expression(face);
}

//_________________________________________________________________________________________________