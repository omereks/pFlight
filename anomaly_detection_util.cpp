#include "anomaly_detection_util.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

float avg(float* x, int size){
	float sum=0;
	for(int i=0;i<size;sum+=x[i],i++);
	return sum/size;
}


//getting avg of array
static float getAvg(float* x, int size) {
    float sum=0;    
    //caclute sum
    for(int i=0; i < size; i++) {
        sum += x[i]; 
    }
    //check if vals are ok
    if (size ==0  || sum == 0) {
        return 0;
    }
    return sum / size ;
}


float var(float* x, int size) {
    float av=avg(x,size);
	float sum=0;
	for(int i=0;i<size;i++){
		sum+=x[i]*x[i];
	}
	return sum/size - av*av;
}

float cov(float* x, float* y, int size) {
    float sum=0;
	for(int i=0;i<size;i++){
		sum+=x[i]*y[i];
	}
	sum/=size;
    return sum - avg(x,size)*avg(y,size);
}

float pearson(float* x, float* y, int size) {
    return cov(x,y,size)/(sqrt(var(x,size))*sqrt(var(y,size)));
}

Line linear_reg(vector<Point> points) {
    int size = points.size();
	float x[size],y[size];
	for(int i=0;i<size;i++)
	{
		x[i] = points[i].x;
		y[i] = points[i].y;
	}
	float a=cov(x,y,size)/var(x,size);
	float b=avg(y,size) - a*(avg(x,size));

	return Line(a,b);
}


Line linear_reg(Point** points, int size){
    float x[size],y[size];
	for(int i=0;i<size;i++){
		x[i]=points[i]->x;
		y[i]=points[i]->y;
	}
	float a=cov(x,y,size)/var(x,size);
	float b=avg(y,size) - a*(avg(x,size));

	return Line(a,b);
}

float dev(Point p,Point** points, int size){
    Line l=linear_reg(points,size);
	return dev(p,l);

}

float dev(Point p,Line l) {
    float x=p.y-l.f(p.x);
	if(x<0)
		x*=-1;
	return x;
}




//import from the Submit 


bool wrong(float val, float expected){
	return val<expected-0.001 || val>expected+0.001;
}

