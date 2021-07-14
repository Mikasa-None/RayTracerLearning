#pragma once
#include "Material.h"
class Metal :public Material
{
public:
	Metal(const vec3& a) 
		:
		albedo(a)
	{}
	bool scatter(const Ray& ray_in, const HitRecord& rec, vec3& attenuation, Ray& scattered)const override 
	{
		vec3 reflected = reflection(ray_in.dir, rec.normal);
		scattered = Ray(rec.p, reflected.normalized());
		attenuation = albedo;
		return dot(scattered.dir, rec.normal) > 0;
	}
	virtual vec3 getAlbedo()const
	{
		return albedo;
	}
	vec3 albedo;
};