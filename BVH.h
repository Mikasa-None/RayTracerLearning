#pragma once
#include "Object.h"
#include "AABB.h"
#include "HitRecord.h"
#include <vector>
#include <algorithm>

struct bvhNode
{
	std::shared_ptr<Object> obj;
	std::shared_ptr<bvhNode> left;
	std::shared_ptr<bvhNode> right;
	AABB bbox;
};

class BVH
{
public:
	BVH(std::vector<std::shared_ptr<Object>> objects)
	{
		root = BVHbuild(objects);
	}
	std::shared_ptr<bvhNode> root;
	std::shared_ptr<bvhNode> BVHbuild(std::vector<std::shared_ptr<Object>> objects);
	bool hit(const Ray& r, HitRecord& rec)const;
	
};

