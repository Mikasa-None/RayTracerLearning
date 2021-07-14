#pragma once
#include "Canvas.h"
#include "Scene.h"
#include "Camera.h"

class RayTracer
{
public:
	RayTracer()
		:
		camera(vec3(278, 278, -800), vec3(278, 278, 0), vec3(0, 1, 0), 40, float(Canvas::ScreenWidth) / float(Canvas::ScreenHeight))
	{}
	void Draw(const Scene& scn, Canvas& cvs)const;
	Camera camera;

};

//camera(vec3(278, 278, -800), vec3(278, 278, 0), vec3(0, 1, 0), 40, float(Canvas::ScreenWidth) / float(Canvas::ScreenHeight))
//camera(vec3(0, 0, 0),vec3(0, 0, -1),vec3(0,1,0),90, float(Canvas::ScreenWidth)/ float(Canvas::ScreenHeight))