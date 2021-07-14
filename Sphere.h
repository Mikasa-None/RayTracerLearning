#pragma once
#include "Ray.h"
#include "Object.h"

class Sphere:public Object
{
public:
	Sphere(const vec3& _center, float r, std::shared_ptr<Material> _mptr)
		:
		center(_center),
		radius(r),
		mptr(_mptr)
	{}
	bool hit(const Ray& r, float tmin, float tmax, HitRecord& rec)const override;
	AABB BoundingBox()const override;
private:
	vec3 center;
	float radius;
	std::shared_ptr<Material> mptr;
};