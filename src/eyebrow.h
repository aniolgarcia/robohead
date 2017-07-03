#ifndef EYEBROW_H
#define EYEBROW_H

#include <iostream>

using namespace std;

class eyebrow
{
	public:

		eyebrow(int pos_x, int pos_y);
		~eyebrow();

		int get_x();
		int get_y();
		int get_deg();
		void move_x(int new_pos);
		void move_y(int new_pos);
		void rotate(int deg);	

	private:

		int pos_x;
		int pos_y;
		int deg;		
		

};

#endif //EYEBROW_H
