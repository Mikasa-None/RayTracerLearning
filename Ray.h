#pragma once
#include "utils.h"


class Ray
{
public:
	Ray() = default;
	Ray(const vec3& _origin,const vec3& _dir)
		:
		origin(_origin),
		dir(_dir)
	{}
	vec3 GetPoint(float t)const;
	vec3 origin;
	vec3 dir;

};