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
		vec3 B, C;
		if (std::fabs(N.x()) > std::fabs(N.y())) {
			float invLen = 1.0f / std::sqrt(N.x() * N.x() + N.z() * N.z());
			C = vec3(N.z() * invLen, 0.0f, -N.x() *invLen);
		}
		else {
			float invLen = 1.0f / std::sqrt(N.y() * N.y() + N.z() * N.z());
			C = vec3(0.0f, N.z() * invLen, -N.y() *invLen);
		}
		B = cross(C, N);
		return a.x() * B + a.y() * C + a.z() * N;
	}

	virtual vec3 sample(const vec3 &wi, const vec3 &N)const {
		// uniform sample on the hemisphere
		float x_1 = getRandom(), x_2 = getRandom();
		float z = std::fabs(1.0f - 2.0f * x_1);
		float r = std::sqrt(1.0f - z * z), phi = 2 * PI * x_2;
		vec3 localRay(r*std::cos(phi), r*std::sin(phi), z);
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


