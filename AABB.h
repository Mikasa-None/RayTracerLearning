#pragma once
#include "utils.h"
class AABB
{
public:
	AABB()
	{
		double minNum = std::numeric_limits<float>::min();
		double maxNum = std::numeric_limits<float>::max();
		pmax = vec3(minNum, minNum, minNum);
		pmin = vec3(maxNum, maxNum, maxNum);
	}
	AABB(const vec3& _pmin, const vec3& _pmax)
		:
		pmin(_pmin),
		pmax(_pmax)
	{}

	bool hit(const Ray& r)const
	{

		float tmin= std::numeric_limits<float>::min();
		float tmax = std::numeric_limits<float>::max();

		for (int i = 0; i < 3; ++i)
		{
			float invDir = 1.0 / r.dir[i];
			float tenter= (pmin[i] - r.origin[i])*invDir;
			float texit = (pmax[i] - r.origin[i])*invDir;
			if (invDir < 0)
			{
				std::swap(tenter, texit);
			}
			tmin = float_max(tmin, tenter);
			tmax = float_min(tmax, texit);
			if (tenter > texit)return false;
		}
		return tmin < tmax && tmax>0;

	}
	
	int maxRangeAxis()
	{
		vec3 diff = pmax - pmin;
		float tmpmax = 0;
		int maxindex = -1;
		for (int i = 0; i < 3; ++i)
		{
			if (diff[i] > tmpmax)
			{
				tmpmax = diff[i];
				maxindex = i;
			}
		}
		return maxindex;
	}

	vec3 Centroid()
	{
		return 0.5f*pmin + 0.5f*pmax;
	}

public:
	vec3 pmin;
	vec3 pmax;
};

inline AABB Union(const AABB& a, const AABB& b)
{
	AABB res;
	res.pmin = vec3_min(a.pmin, b.pmin);
	res.pmax = vec3_max(a.pmax, b.pmax);
	return res;
}