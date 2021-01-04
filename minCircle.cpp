#include "minCircle.h"

// implement
//calc the distants between 2 points
float distance(const Point &p1, const Point &p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));;
}

//making a circle out of 2 points
Circle trivalCircle2(Point p1, Point p2){
	float radius = distance (p1, p2) / 2;

	float cx = (p1.x + p2.x) / 2;
	float cy = (p1.y + p2.y) / 2;
	Point center(cx, cy);

	return Circle(center, radius);

}

//making a circle out of 3 points from Wikipdia
Circle trivalCircle3(const Point& p1, const Point&  p2, const Point&  p3){
	float bx = p2.x - p1.x;
	float by = p2.y - p1.y;
	float cx = p3.x - p1.x;
	float cy = p3.y - p1.y;

	float B = bx * bx + by * by; 
    float C = cx * cx + cy * cy; 
    float D = bx * cy - by * cx; 

	float centerX = (cy * B - by * C) / (2 * D) + p1.x;
	float centerY = (bx * C - cx * B) / (2 * D) + p1.y;

	Point center(centerX, centerY);

    float radius = distance(center, p1);

	return Circle(center, radius);
}

bool pointInCircle(Point p, Circle c) {
    return (distance(p, c.center) <= c.radius);
}

//check if point is neccesary for making a circle
bool ifPointIsInCircle(const Circle& c, const vector<Point>& pointsR) 
{ 
    for (int i = 0; i < pointsR.size(); i++)
	{
		if (!(distance(c.center, pointsR[i]) <= c.radius)) 
            return false; 
	}
	 
    return true; 
} 

//recursiv Wexler Algo
Circle minidisc(vector<Point>& p, vector<Point> r, int n){
	if (n == 0 || r.size() == 3)
	{	
		if (r.size() == 0)
		{
			return Circle(Point(0,0),0);
		}

		if (r.size() == 1)
		{
			return Circle(r[0] ,0);
		}

		if (r.size() == 2)
		{
			return trivalCircle2(r[0], r[1]);
		}
		
		//check if it will be enough to make acording only 2 points
		for (int i = 0; i < 3; i++) { 
			for (int j = i + 1; j < 3; j++) { 
				Circle c = trivalCircle2(p[i], p[j]); 
				if (ifPointIsInCircle(c, p)) 
					return c; 
			} 
		} 

		//r.size() == 3)
		return trivalCircle3(r[0], r[1], r[2]);
	}
	//else
	// Pick a random point randomly 
    int randi = rand() % n;
	Point curP = p[randi];
 	swap(p[randi], p[n-1]);

	Circle d = minidisc(p, r, n-1);

	//check if  curP is inside circle d
	if (distance(d.center, curP) <= d.radius){
		return d;
	}
	
	r.push_back(curP);
	return minidisc(p, r, n-1);
}

//our method
Circle findMinCircle(Point** points,size_t size){	
	vector<Point> vecPoint;
	for (int i = 0; i < size; i++)
	{
		vecPoint.push_back(*points[i]);
	}
	return minidisc(vecPoint, {}, vecPoint.size());	
}
