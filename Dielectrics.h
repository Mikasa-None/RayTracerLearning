#pragma once
#include "Material.h"

float schlick(float cosine, float ni_over_nt)
{
	float r0 = (1 - ni_over_nt) / (1 + ni_over_nt);
	r0 = r0*r0;
	return r0 + (1 - r0)*pow((1 - cosine), 5);

}


class Dielectrics :public Material
{
public:
	Dielectrics(float ir)
		:
		index_of_refraction(ir)
	{}
	bool scatter(const Ray& ray_in, const HitRecord& rec, vec3& attenuation, Ray& scattered)const override
	{
		attenuation = vec3(1.0, 1.0, 1.0);
		float ni_over_nt;
		vec3 outward_normal;
		if (dot(ray_in.dir, rec.normal) < 0)
		{
			outward_normal = rec.normal;
			ni_over_nt = 1.0f / index_of_refraction;
		}
		else
		{
			outward_normal = -rec.normal;
			ni_over_nt = index_of_refraction;
		}

		float cosine = dot(-ray_in.dir, outward_normal);
		vec3 direction;
		vec3 refracted;
		if (schlick(cosine, ni_over_nt) > getRandom()|| !refraction(ray_in.dir, outward_normal,ni_over_nt, refracted))
		{
			direction = reflection(ray_in.dir, outward_normal);
		}
		else
		{
			direction= refracted;
		}	
		scattered = Ray(rec.p, direction);
		return true;
	}
	
	float index_of_refraction;
};


