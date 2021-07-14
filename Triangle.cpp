#include "Triangle.h"

bool Triangle::hit(const Ray & r,float tmin, float tmax, HitRecord & rec) const
{
	//fundamentals... book
	vec3 cramer0 = e1;
	vec3 cramer1 = e2;
	vec3 D = r.dir;
	vec3 T =  r.origin-v0;
	vec3 P = cross(D, e2);
	vec3 Q = cross(T, e1);

	float det = dot(P, e1);
	float inv_det = 1.0f / det;

	float t = dot(Q,e2)*inv_det;
	if (t<tmin || t>tmax)return false;
	float u = dot(P, T)*inv_det;
	if (u < 0)return false;
	float v = dot(Q, D)*inv_det;
	if (v < 0)return false;
	if (u+v >1)return false;

	rec.hitFlag = true;
	rec.t = t;
	rec.p = r.GetPoint(rec.t);
	rec.normal = normal;
	rec.mptr = mptr;
	return true;
}

AABB Triangle::BoundingBox() const
{
	return bbox;
}
