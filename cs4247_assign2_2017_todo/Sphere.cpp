//============================================================
// STUDENT NAME: Miao Qi
// MATRIC NO.  : A0159327X
// NUS EMAIL   : e0046706@u.nus.edu
// COMMENTS TO GRADER:
// <comments to grader, if any>
//
// ============================================================
//
// FILE: Sphere.cpp



#include <cmath>
#include "Sphere.h"
#include <algorithm>

using namespace std;



bool Sphere::hit( const Ray &r, double tmin, double tmax, SurfaceHitRecord &rec ) const 
{
	//***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************

	// Transfer the origin 
    Vector3d origin = r.origin() - center;

    double a = 1;
    double b = 2 * dot(r.direction(), origin);
    double c = dot(origin, origin) - pow(radius, 2); 
    double d = pow(b, 2) - 4 * a * c;
    if ( d < 0 )
        return false;

    double t0 = (-b + sqrt(d)) / (2 * a);
    double t1 = (-b - sqrt(d)) / (2 * a);
    double t;
	if ((t0 > tmax && t1 > tmax) || (t0 < tmin && t1 < tmin) || (t0 > tmax && t1 < tmin) || (t0 < tmin && t1 > tmax))
		return false;
	else if (t0 < tmin || t0 > tmax)
		t = t1;
	else if (t1 < tmin || t1 > tmax)
		t = t0;
	else
		t = min(t0, t1);

    rec.t = t;
    rec.p = r.pointAtParam(t);

    Vector3d normal = rec.p - center;
	rec.normal = normal / normal .length();
    
	rec.mat_ptr = matp;

	return true;
}




bool Sphere::shadowHit( const Ray &r, double tmin, double tmax ) const 
{
	//***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************

	Vector3d origin = r.origin() - center;

	double a = 1;
	double b = 2 * dot(r.direction(), origin);
	double c = dot(origin, origin) - pow(radius, 2);
	double d = pow(b, 2) - 4 * a * c;
	if (d < 0)
		return false;

	double t0 = (-b + sqrt(d)) / (2 * a);
	double t1 = (-b - sqrt(d)) / (2 * a);
	double t;
	if ((t0 > tmax && t1 > tmax) || (t0 < tmin && t1 < tmin) || (t0 > tmax && t1 < tmin) || (t0 < tmin && t1 > tmax))
		return false;
	else
		return true;
		

	return false; 
}

