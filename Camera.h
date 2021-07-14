#pragma once
#include "Ray.h"
class Camera
{
public:
	Camera(vec3 lookFrom, vec3 lookAt, vec3 up, float fov, float aspect)
		:
		pos(lookFrom)
	{
		float theta = to_rad(fov);
		half_height = tan(theta / 2.0);
		half_width = aspect*half_height;
		w = (lookFrom - lookAt).normalized();//right hand
		u = cross(up, w).normalized();
		v = cross(w, u).normalized();
	}

	Ray GetRay(float x, float y) const
	{
		x = (x * 2 - 1)*half_width;
		y = (-y * 2 + 1 )*half_height;

		//vec3 dir1 = (x*u + y*v - w - pos).normalized();
		vec3 dir = (x*u + y*v - w).normalized();
		return Ray(pos,dir );
	}

private:
	vec3 pos;
	vec3 u;
	vec3 v;
	vec3 w;
	float half_width;
	float half_height;

};

