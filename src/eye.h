#ifndef EYE_H
#define EYE_H

#include <iostream>
#include <math.h>



class eye
{
	public:

		
		eye(int pos_x, int pos_y);
		~eye();
	
		int get_x();
		int get_y();
		void move_x(int new_pos);
		void move_y(int new_pos);
		void move(int new_pos_x, int new_pos_y);	

	private:
		
		int pos_x;
		int pos_y;
};

#endif //EYE_H


