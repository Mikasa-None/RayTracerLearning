#pragma once

#include "Ray.h"
#include "AABB.h"
#include "HitRecord.h"

class Object
{
public:
	virtual bool hit(const Ray& r, float tmin, float tmax, HitRecord& rec)const=0;
	virtual AABB BoundingBox()const = 0;
	virtual bool hasEmit()const = 0;
	virtual float getArea() const = 0;
	virtual void Sample(HitRecord &pos, float &pdf)const = 0;
};