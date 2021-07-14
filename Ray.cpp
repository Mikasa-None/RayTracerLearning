#include "Ray.h"

vec3 Ray::GetPoint(float t)const
{
	return origin + t*dir;
}
