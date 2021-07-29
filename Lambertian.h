#pragma once
#include "Material.h"

class Lambertian :public Material
{
public:
	Lambertian(const vec3& a)
		:
		albedo(a)
	{}
	bool scatter(const Ray& ray_in, const HitRecord& rec, vec3& attenuation, Ray& scattered)const override
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = Ray(rec.p, (target - rec.p).normalized());
		attenuation = albedo;
		return true;
	}
	virtual vec3 getAlbedo()const
	{
		return albedo;
	}
	vec3 toWorld(const vec3 &a, const vec3 &N)const {
		vec3 w = unit_vector(N);
		vec3 help = (fabs(w.x()) > 0.9) ? vec3(0, 1, 0) : vec3(1, 0, 0);
		vec3 v = unit_vector(cross(w, help));
		vec3 u = cross(w, v);
		return a.x() * u + a.y() * v + a.z() * w;
	}

	virtual vec3 sample(const vec3 &wi, const vec3 &N)const {
		float x_1 = getRandom(), x_2 = getRandom();
		float Phi = 2 * PI * x_1;
		float CosTheta = x_2;
		float SinTheta = sqrt(1 - CosTheta * CosTheta);

		float x = SinTheta * cos(Phi);
		float y = SinTheta * sin(Phi);
		float z = CosTheta;
		vec3 localRay(x, y, z);
		return toWorld(localRay, N);

	}

	virtual float pdf(const vec3 &wi, const vec3 &wo, const vec3 &N)const {
		// uniform sample probability 1 / (2 * PI)
		if (dot(wo, N) > 0.0f)
			return 0.5f / PI;
		else
			return 0.0f;

	}

	virtual vec3 brdf(const vec3 &wi, const vec3 &wo, const vec3 &N)const {
		// calculate the contribution of diffuse   model
		float cosalpha = dot(N, wo);
		if (cosalpha > 0.0f) {
			vec3 diffuse = albedo / PI;
			return diffuse;
		}
		else
			return{};

	}

private:
	vec3 albedo;
};


