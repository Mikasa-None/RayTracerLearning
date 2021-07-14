#pragma once
#include "Object.h"
#include "BVH.h"
#include <vector>
#include <memory>
class Scene
{
public:
	Scene()
	{
		CreateObjects();
		//bvh = std::make_unique<BVH>(objects);
	}
	void CreateObjects();

	bool isHit(const Ray & r, HitRecord& rec)const;

	vec3 castRay(const Ray& r, int depth)const;

	vec3 PathTracing(const Ray& r) const;
	void sampleLight(HitRecord &pos, float &pdf) const;
	vec3 shade(HitRecord& rec, const vec3& wo)const;
private:
	std::vector<std::shared_ptr<Object>> objects;
	std::unique_ptr<BVH> bvh;
	float RussianRoulette = 0.8;
};