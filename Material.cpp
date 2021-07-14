#include "Material.h"

vec3 reflection(const vec3 & in, const vec3 & normal)
{
	return in - 2 * dot(in, normal)*normal;
}

bool refraction(const vec3& in, const vec3& normal, float ni_over_nt, vec3& refracted)
{
	vec3 in_unit = unit_vector(in);
	vec3 normal_unit= unit_vector(normal);
	float cos_theta_in = dot(in_unit, normal_unit);
	float sin2_theta_in = 1 - cos_theta_in*cos_theta_in;
	float sin2_theta_out = ni_over_nt*ni_over_nt*sin2_theta_in;
	float cos2_theta_out = 1 - sin2_theta_out;
	if (cos2_theta_out > 0)
	{
		float cos_theta_out = sqrt(cos2_theta_out);
		refracted = -normal_unit*cos_theta_out + ni_over_nt*(in_unit - normal_unit*cos_theta_in);
		return true;
	}
	return false;

}