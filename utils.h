#pragma once
#include <cmath>
#include <iostream>
#include <math.h>

constexpr float EPSILON = 1e-5f;
//*****************************************//
//*Chili DirectX Framework Version 16.10.01											  *
//*	ChiliMath.h
constexpr float PI = 3.14159265f;
constexpr double PI_D = 3.1415926535897932;

//template <typename T>
//constexpr auto sq(const T& x)
//{
//	return x * x;
//}
//
//template<typename T>
//T wrap_angle(T theta)
//{
//	const T modded = fmod(theta, (T)2.0 * (T)PI_D);
//	return (modded > (T)PI_D) ?
//		(modded - (T)2.0 * (T)PI_D) :
//		modded;
//}
//
//template<typename T>
//constexpr T interpolate(const T& src, const T& dst, float alpha)
//{
//	return src + (dst - src) * alpha;
//}
//
//template<typename T>
//constexpr T to_rad(T deg)
//{
//	return deg * PI / (T)180.0;
//}
//*****************************************//
constexpr float to_rad(float deg)
{
	return deg * PI / 180.0;
}

class vec2 {
public:
	vec2();
	vec2(float e0, float e1);

	float x() const;
	float y() const;
	float& operator[](int i);
	float operator[](int i) const;

	vec2 operator-() const;
	vec2& operator+=(const vec2 &v);
	vec2& operator*=(const float t);
	vec2& operator/=(const float t);

	float norm() const;
	float norm_squared() const;

public:
	float e[2];
};

class vec3 {
public:
	vec3();
	vec3(float e0, float e1, float e2);

	float x() const;
	float y() const;
	float z() const;
	float& operator[](int i);
	float operator[](int i) const;
	
	vec3 operator-() const;
	vec3& operator+=(const vec3 &v);
	vec3& operator*=(const float t);
	vec3& operator/=(const float t);

	float norm() const;
	float norm_squared() const;

	vec3 normalized(){
		return vec3(e[0]/norm(),e[1]/norm(),e[2]/norm());
	}

	float sum() const;

public:
	float e[3];
};

class vec4 {
public:
	vec4();
	vec4(float e0, float e1, float e2, float e3);

	float x() const;
	float y() const;
	float z() const;
	float w() const;
	float& operator[](int i);
	float operator[](int i) const;

	vec4& operator*=(const float t);
	vec4& operator/=(const float t);


public:
	float e[4];
};

class mat3 {
public:
	mat3();

	vec3& operator[](int i);
	vec3 operator[](int i) const;

	mat3 transpose() const;
	mat3 inverse() const;
	mat3 inverse_transpose() const;
	static mat3 identity();

public:
	vec3 rows[3];
};

class mat4 {
public:
	mat4();

	vec4& operator[](int i);
	vec4 operator[](int i) const;

	mat4 transpose() const;
	mat4 inverse() const;
	mat4 inverse_transpose() const;
	static mat4 identity();

public:
	vec4 rows[4];
};

/* vec2 related functions */
std::ostream& operator<<(std::ostream &out, const vec2 &v);
vec2 operator+(const vec2 &u, const vec2 &v);
vec2 operator-(const vec2 &u, const vec2 &v);
vec2 operator*(const vec2 &u, const vec2 &v);
vec2 operator*(double t, const vec2 &v);
vec2 operator*(const vec2 &v, double t);
vec2 operator/(vec2 v, double t);

/* vec3 related functions */
std::ostream& operator<<(std::ostream &out, const vec3 &v);
vec3 operator+(const vec3 &u, const vec3 &v);
vec3 operator-(const vec3 &u, const vec3 &v);
vec3 operator*(const vec3 &u, const vec3 &v);
vec3 operator*(double t, const vec3 &v);
vec3 operator*(const vec3 &v, double t);
vec3 operator/(vec3 v, double t);
double dot(const vec3 &u, const vec3 &v);
vec3 cross(const vec3 &u, const vec3 &v);
vec3 unit_vector(const vec3 &v);
vec3 cwise_product(const vec3& a, const vec3& b);

//vec3 dot_division(const vec3 &u, const vec3 &v);

/* vec4 related functions */
std::ostream& operator<<(std::ostream &out, const vec4 &v);
vec4 to_vec4(const vec3 &u, float w);
vec4 operator-(const vec4 &u, const vec4 &v);
vec4 operator+(const vec4 &u, const vec4 &v);
vec4 operator*(double t, const vec4 &v);
vec4 operator*(const vec4 &v, double t);

/* mat related functions */
std::ostream& operator<<(std::ostream &out, const mat3 &m);
std::ostream& operator<<(std::ostream &out, const mat4 &m);
vec4 operator*(const mat4 &m, const vec4 v);
mat4 operator*(const mat4 &m1, const mat4 &m2);

/* untility functions */
float float_max(float a, float b);
float float_min(float a, float b);
float float_clamp(float f, float min, float max);
float float_lerp(float start, float end, float alpha);
vec2 vec2_lerp(vec2& start, vec2& end, float alpha);
vec3 vec3_lerp(vec3& start, vec3& end, float alpha);
vec4 vec4_lerp(vec4& start, vec4& end, float alpha);

vec3 vec3_min(const vec3& v1, const vec3& v2);
vec3 vec3_max(const vec3& v1, const vec3& v2);


float getRandom(float rangeMin = 0.0, float rangeMax = 1.0);
int getRandomInt(int rangeMin = 0, int rangeMax = 100);
vec3 random_in_unit_sphere();
