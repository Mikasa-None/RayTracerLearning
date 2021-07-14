#pragma once
#include "Ray.h"
#include "HitRecord.h"

class Material
{
public:
	virtual bool scatter(const Ray& ray_in, const HitRecord& rec, vec3& attenuation, Ray& scattered)const = 0;
	//virtual vec3 emit(float u, float v, const vec3& p)const
	//{
	//	return vec3(0.0, 0.0, 0.0);
	//}
	virtual vec3 getEmission()const
	{
		return{};
	}

	virtual bool hasEmission()const
	{
		return false;
	}

	virtual vec3 getAlbedo()const
	{
		return{};
	}
	virtual vec3 sample(const vec3 &wi, const vec3 &N)const
	{
		return{};
	}


	virtual float pdf(const vec3 &wi, const vec3 &wo, const vec3 &N)const
	{
		return -1.0;
	}


	virtual vec3 brdf(const vec3 &wi, const vec3 &wo, const vec3 &N)const
	{
		return{};
	}
};



vec3 reflection(const vec3& in, const vec3& normal);
bool refraction(const vec3& in, const vec3& normal, float ni_over_nt, vec3& refracted);