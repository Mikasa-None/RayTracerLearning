#pragma once
#include "Object.h"
#include "Material.h"
class Triangle:public Object
{
public:
	Triangle(const vec3& _v0, const vec3& _v1, const vec3& _v2, std::shared_ptr<Material> _mptr)
		:
		v0(_v0),
		v1(_v1),
		v2(_v2),
		mptr(_mptr)
	{
		e1 = v1 - v0;
		e2 = v2 - v0;
		area = cross(e1, e2).norm()*0.5f;
		normal = unit_vector(cross(e1, e2));//rhs
		vec3 pmin = vec3_min(vec3_min(v0, v1), v2);
		vec3 pmax = vec3_max(vec3_max(v0, v1), v2);
		bbox = AABB(pmin, pmax);
		
	}
	
	vec3 normal;
	//vec2 tex_uv[3];
	std::shared_ptr<Material> mptr;

	virtual void Sample(HitRecord &pos, float &pdf) const{
		float x = std::sqrt(getRandom()), y = getRandom();
		pos.p = v0 * (1.0f - x) + v1 * (x * (1.0f - y)) + v2 * (x * y);
		pos.normal = this->normal;
		pos.mptr = mptr;
		pdf = 1.0f / area;
	}
	virtual float getArea() const {
		return area;
	}
	virtual bool hasEmit()const
	{
		return mptr->hasEmission();
	}

public:
	virtual bool hit(const Ray& r, float tmin, float tmax, HitRecord& rec)const override;
	virtual AABB BoundingBox()const override;
private:
	vec3 v0,v1,v2;//counter-clockwise order
	vec3 e1, e2;
	float area;
	AABB bbox;
};


