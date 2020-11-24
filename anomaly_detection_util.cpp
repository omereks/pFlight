#include "anomaly_detection_util.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>
using namespace std;

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
    //crate xPow by 2
    float sumXPow = 0;
    for(int i=0 ; i<size ; i++) {
        sumXPow += pow(x[i], 2);
    }  
    float ret = sumXPow/size - pow(getAvg(x, size), 2);
    return ret;
}

float cov(float* x, float* y, int size) {
    //crate xyArray
    float xyArray[size];
    for(int i=0 ; i<size ; i++) {
        xyArray[i] = x[i]*y[i];
    }

    return getAvg(xyArray,size) - (getAvg(x,size) * getAvg(y,size));
}

float pearson(float* x, float* y, int size) {
    return (cov(x, y, size)) / (sqrt( var(x , size) ) * (sqrt( var(y , size) )));
}

Line linear_reg(Point** points, int size){
    float a, b;
    float xP[size], yP[size];
    //extract x and y from points into array
    for(int i=0 ; i<size ; i++) {
        xP[i] = points[i]->x;
        yP[i] = points[i]->y;
    } 
    a = cov(xP, yP, size) / var(xP , size);
    b = getAvg(yP, size) - a*getAvg(xP, size);
    return Line(a, b);
}

float dev(Point p,Point** points, int size){
    Line curLine = linear_reg(points , size);
return dev(p, curLine);

}

float dev(Point p,Line l) {
    return abs(l.f(p.x) - p.y);
}




//import from the Submit 


bool wrong(float val, float expected){
	return val<expected-0.001 || val>expected+0.001;
}

