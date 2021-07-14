#pragma once
#include "Object.h"
#include "Triangle.h"
#include <vector>
class MeshTriangle :public Object
{
public:
	MeshTriangle(std::string filename, std::shared_ptr<Material> _mptr);
	virtual void Sample(HitRecord &pos, float &pdf) const{
		int r= getRandomInt(0,triangles.size()-1);
		triangles[r].Sample(pos, pdf);
		pdf = 1.0/area;
	}
	virtual float getArea() const {
		return area;
	}
	virtual bool hasEmit()const
	{
		return mptr->hasEmission();
	}

private:
	std::vector<Triangle> triangles;
	AABB bbox;
	float area=0;
	std::shared_ptr<Material> mptr;
public:
	virtual bool hit(const Ray& r, float tmin, float tmax, HitRecord& rec)const override;
	virtual AABB BoundingBox()const override;
};