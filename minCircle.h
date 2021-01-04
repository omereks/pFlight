// 31235019	30843376

#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include "math.h"
#include "vector"
#include "random"
#include "algorithm"
#include "anomaly_detection_util.h"
using namespace std;

// ------------ DO NOT CHANGE -----------
//class Point{
//public:
//	float x,y;
//	Point(float x,float y):x(x),y(y){}
//};

class Circle{
public:
	Point center;
	float radius;
	Circle():center(Point(0,0)),radius(0){}
	Circle(Point c,float r):center(c),radius(r){}
	float getRadius(){
		return radius;
	}
	void setRadius(float r){
		radius = r;
	}
};
// --------------------------------------
// implement
//calc the distants between 2 points


//making a circle out of 2 points
Circle trivalCircle2(Point p1, Point p2);

//making a circle out of 3 points from Wikipdia
Circle trivalCircle3(const Point& p1, const Point&  p2, const Point&  p3);

//check if point is neccesary for making a circle
bool ifPointIsInCircle(const Circle& c, const vector<Point>& pointsR);

//recursiv Wexler Algo
Circle minidisc(vector<Point>& p, vector<Point> r, int n);

//our method
Circle findMinCircle(Point** points,size_t size);


#endif

