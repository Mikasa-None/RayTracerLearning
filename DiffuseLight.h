#pragma once

#include "Material.h"

class DiffuseLight:public Material
{
public:
	DiffuseLight(const vec3& e)
		:
		emitted(e)
	{}
	virtual bool scatter(const Ray& ray_in, const HitRecord& rec, vec3& attenuation, Ray& scattered)const override
	{
		return false;
	}
	//virtual vec3 emit(float u, float v, const vec3& p)const
	//{
	//	return emitted;
	//}

	virtual vec3 getEmission()const
	{
		return emitted;
	}

	virtual bool hasEmission()const
	{
		return true;
	}
	vec3 emitted;
};