/* Kashyap Babubhai Patel								*/
/* Computer Programmer (CPD)							*/
/* Semester - 4											*/
/* Seneca College of Applied Arts and Technology		*/
/* School of Information & Communication Technology		*/
/* E-mail: kbpatel13@myseneca.ca						*/

//Polygon.h
#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <iostream>
using namespace std;
#include <string.h>


class Showable {									//interface class showable
	public:
		virtual ostream& display(ostream& os) const = 0;
};
	ostream& operator<<(ostream& os, const Showable& s) {  //Insertion operator for Showable
		s.display(os);
		return os;
}

class Point : public Showable {						//class point
		double x, y;
	public:
		Point() {									// no arg constructor
			x = 0; y = 0; 
		}										
	Point(double x, double y) : x(x), y(y) { }		// two arg constructor
	ostream& display(ostream& os) const {
		os << "(" << x << ", " << y << ")" << endl;
		return os;
	}
	double getX() const {							// get function for X
		return x; 
	}		
	double getY() const {							// get function for Y
		return y; 
	}		
};

Point operator+(const Point& pa, const Point& pb) {	//Return Point that contains sum of coordinates of Points a and b	
	return Point(pa.getX() + pb.getX(), pa.getY() + pb.getY());
}

Point operator/(const Point& a, int b) {		//Return Point whose coordinates are those of Point a, divided by b 
	return Point(a.getX() / b, a.getY() / b);
}

class Shape : public Showable {					//class shape
		char name[30];
public:
	ostream& display(ostream &os) const {
		os << name << endl;
		return os;
	}
	virtual Point centroid() const = 0;

};

												//Concrete class Polygon that is a named Shape which contains vertices
class Polygon : public Shape {
	char* name;
	int n_vertices;
	Point* vertices;
public:
	Polygon(char* n, int v) {			  		//Two argument Constructor
		if (n != NULL && v > 0) {
			name = new char[strlen(n) + 1];
			strcpy(name, n);
			vertices = new Point[v];
			n_vertices = v;
		} else {
			name = NULL;
			vertices = new Point();
			n_vertices = 1;
		}
		
	}
	Point& operator()(int i) {					//Return reference to Point object 
		if (i >= 0 || i < n_vertices) {
			return vertices[i];
		}
		else {
			return vertices[0];
		}
	}
	ostream& display(ostream& os) const {		//Display name of Polygon 
		if (name != NULL) os << name << " Centroid " << centroid() << endl;
		return os;
	}


	Point centroid() const {					//query that returns point objects
		double x = 0;
		double y = 0;
		int z;
		for (z = 0; z < n_vertices; z++) {
			x += vertices[z].getX();
			y += vertices[z].getY();
		}
		return Point(x / n_vertices, y / n_vertices);
	}
	~Polygon() {								//destructor
		name = NULL;
		delete[] name;
		if(vertices) {
			delete[] vertices;
			vertices = NULL;
		}
	}
};
#endif
