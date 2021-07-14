#pragma once
#include "utils.h"
#include <memory>
class Material;

struct HitRecord
{
	float t= std::numeric_limits<double>::max();
	vec3 p;
	vec3 normal;
	std::shared_ptr<Material> mptr;
	bool hitFlag = false;
};
