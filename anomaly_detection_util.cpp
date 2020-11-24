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

// this is a simple test to put you on the right track
int main(){
	
    
    const int N=10;
	float x[]={1,2,3,4,5,6,7,8,9,10};
	float y[]={2.1,4.2,6.1,8.1,10.3,12.2,14.4,16.1,18.2,20.3};

	Point* ps[N];
	for(int i=0;i<N;i++)
		ps[i]=new Point(x[i],y[i]);

	Line l=linear_reg(ps,N);
	Point p(4,8);

	float v[]={var(x,N),cov(x,y,N),pearson(x,y,N),l.a,l.b,l.f(4),dev(p,l)};
	float e[]={8.25,16.63,0.999,2.015,0.113,8.176,0.176};


	for(int i=0;i<7;i++)
		if(wrong(v[i],e[i]))
			cout<<"error for check "<<i<<" (-14)"<<endl;


	for(int i=0;i<N;i++)
		delete ps[i];

	cout<<"done"<<endl;
    
	return 0;
}
