#include "Sphere.h"
#include <algorithm>
bool Sphere::hit(const Ray& r, float tmin, float tmax, HitRecord& rec) const
{
	float a = dot(r.dir, r.dir);
	float b = 2 * dot((r.origin - center), r.dir);
	float c = dot((r.origin - center), (r.origin - center)) - radius*radius;
	float discriminant = b*b - 4 * a*c;
	if (discriminant >= 0)
	{
		float factor = 1.0 / (2 * a);
		//float t1 = (-b - sqrt(discriminant))*factor;
		//float t2= (-b + sqrt(discriminant))*factor;
		//float t = t1;
		//if (t <0)t = t2;
		//if (t < 0)return false;
		float t = (-b - sqrt(discriminant))*factor;

		//float tmin = 0.001;

		if (t < tmin || t>tmax)
		{
			t = (-b + sqrt(discriminant))*factor;
			if (t < tmin || t>tmax)
				return false;
		}


		rec.t = t;
		rec.p = r.GetPoint(rec.t);
		rec.normal = (rec.p - center).normalized();
		rec.mptr = mptr;
		rec.hitFlag = true;

		return true;

	}

	return false;
}

AABB Sphere::BoundingBox() const
{
	return AABB(center-vec3(radius, radius, radius),center+ vec3(radius, radius, radius));
}
