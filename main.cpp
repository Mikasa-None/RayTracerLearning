
#include <string>
#include <time.h>
#include "RayTracer.h"
#include "Scene.h"
#include "Canvas.h"

//#include<memory>
//#include"Lambertian.h"
//#include "Triangle.h"

int main()
{
	//auto red = std::make_shared<Lambertian>(vec3(.65, .05, .05));
	//Triangle t(vec3(-1,-1,-1), vec3(1,-1,-1), vec3(0,1,-2), red);
	//Ray r(vec3(0,0,0),vec3(0,0,-1));
	//HitRecord rec;
	//t.hit(r, 0.001, 1e09f, rec);

	clock_t start, end;
	start = clock();

	RayTracer rt;
	Scene scn;
	Canvas cvs;

	rt.Draw(scn, cvs);

	end = clock();
	std::cout << "time=" << double(end - start) / CLOCKS_PER_SEC << "s\n" ;
	std::string time = std::to_string(double(end - start) / CLOCKS_PER_SEC);
	std::string savename = "result_"+ time+".png";
	cvs.output(savename);
	getchar();
	return 0;
}