#include "Scene.h"
#include "Sphere.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectrics.h"
#include "DiffuseLight.h"
#include <limits>
#include "MeshTriangle.h"
void Scene::CreateObjects()
{
	//objects.push_back(std::make_shared<Sphere>(vec3(0, 0, -1), 0.5,std::make_shared<Lambertian>(vec3(0.8,0.3,0.3))));
	//objects.push_back(std::make_shared<Sphere>(vec3(0, -100.5, -1), 100, std::make_shared<Lambertian>(vec3(0.8, 0.8, 0.0))));
	//objects.push_back(std::make_shared<Sphere>(vec3(1, 0, -1), 0.5, std::make_shared<Metal>(vec3(0.8, 0.6, 0.2))));
	//objects.push_back(std::make_shared<Sphere>(vec3(-1, 0, -1), 0.5, std::make_shared<Dielectrics>(1.5)));


	auto red =   std::make_shared<Lambertian>(vec3(.65, .05, .05));
	auto white = std::make_shared<Lambertian>(vec3(.73, .73, .73));
	auto green = std::make_shared<Lambertian>(vec3(.12, .45, .15));
	auto light = std::make_shared<DiffuseLight>(vec3(15, 15, 15));
	//auto light = std::make_shared<DiffuseLight>((8.0f * vec3(0.747f + 0.058f, 0.747f + 0.258f, 0.747f) + 15.6f * vec3(0.740f + 0.287f, 0.740f + 0.160f, 0.740f) + 18.4f *vec3(0.737f + 0.642f, 0.737f + 0.159f, 0.737f)));
	
	objects.emplace_back(std::make_shared<MeshTriangle>("cornellbox\\floor.obj", white));
	objects.emplace_back(std::make_shared<MeshTriangle>("cornellbox\\shortbox.obj", white));
	objects.emplace_back(std::make_shared<MeshTriangle>("cornellbox\\tallbox.obj", white));
	objects.emplace_back(std::make_shared<MeshTriangle>("cornellbox\\left.obj", red));
	objects.emplace_back(std::make_shared<MeshTriangle>("cornellbox\\right.obj", green));
	objects.emplace_back(std::make_shared<MeshTriangle>("cornellbox\\light.obj", light));


}

bool Scene::isHit(const Ray & r, HitRecord& rec) const
{
	bool hitflag = false;
	float tnear = std::numeric_limits<float>::max();
	HitRecord recTmp;
	for (int i = 0; i < objects.size(); ++i)
	{
		if (objects[i]->hit(r,0.001, tnear, recTmp))
		{
			tnear = recTmp.t;
			rec = recTmp;
			hitflag = true;
		}
	}
	//hitflag = bvh->hit(r, rec);
	return hitflag;
}


//vec3 Scene::castRay(const Ray& r, int depth) const {
//	HitRecord rec;
//	if (isHit(r, rec)) {
//		Ray scattered;
//		vec3 attenuation;
//		if (depth < 4 && rec.mptr->scatter(r, rec, attenuation, scattered)) {
//
//			return attenuation*castRay(scattered,depth + 1);
//		}
//		else {
//			return vec3(0, 0, 0);
//		}
//
//	}
//	else {
//		vec3 unit_dir = unit_vector(r.dir);
//		float t = 0.5*(unit_dir.y() + 1.0);
//		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
//	}
//}

vec3 Scene::castRay(const Ray& r, int depth) const {
	if (depth > 10)return{};
	HitRecord rec;
	if (isHit(r, rec)) {
		Ray scattered;
		vec3 attenuation;
		vec3 emitted= rec.mptr->getEmission();
		if (rec.mptr->hasEmission())return emitted;
		rec.mptr->scatter(r, rec, attenuation, scattered);
		return emitted + attenuation*castRay(scattered, depth + 1);

	}
	else {
		return vec3(0.235294, 0.67451, 0.843137);
	}
}


void Scene::sampleLight(HitRecord &pos, float &pdf) const
{
	float emit_area_sum = 0;
	for (uint32_t k = 0; k < objects.size(); ++k) {
		if (objects[k]->hasEmit()) {
			emit_area_sum += objects[k]->getArea();
		}
	}
	float p = getRandom() * emit_area_sum;
	emit_area_sum = 0;
	for (uint32_t k = 0; k < objects.size(); ++k) {
		if (objects[k]->hasEmit()) {
			emit_area_sum += objects[k]->getArea();
			if (p <= emit_area_sum) {
				objects[k]->Sample(pos, pdf);
				break;
			}
		}
	}
}

vec3 Scene::shade(HitRecord& rec, const vec3& wo)const
{
	vec3 emitted = rec.mptr->getEmission();
	if (rec.mptr->hasEmission())return emitted;

	//vec3 albedo= rec.mptr->getAlbedo();
	vec3 L_dir;
	//sample light
	//light_pdf
	float light_pdf;
	HitRecord light_inter;
	sampleLight(light_inter, light_pdf);
	vec3 obj2light = light_inter.p - rec.p;
	vec3 obj2lightDir = unit_vector(obj2light);
	//test shelter
	Ray shadowRay = Ray(rec.p, obj2lightDir);
	HitRecord shelter_test;
	isHit(shadowRay, shelter_test);

	float threshold = 0.0005f;
	//light_emit*brdf*cos*(dA*cos'/r^2)/light_pdf
	if (shelter_test.t - obj2light.norm() > -threshold)
	{
		L_dir =
			light_inter.mptr->getEmission()*
			rec.mptr->brdf(obj2light, wo, rec.normal)*
			std::max(0.0, dot(obj2lightDir, rec.normal))*
			std::max(0.0, dot(-obj2lightDir, light_inter.normal)) /
			dot(obj2light, obj2light) / light_pdf;
	}
	//r<RR indir
	if (getRandom() > RussianRoulette)return L_dir;
	vec3 L_indir;
	//sample obj hemisphere--nextObjDir
	//hemi_pdf
	vec3 nextObjDir = rec.mptr->sample(wo, rec.normal).normalized();
	float hemi_pdf = rec.mptr->pdf(wo, nextObjDir, rec.normal);
	if (hemi_pdf < threshold)return L_dir;
	//shade(nextObj,-nextObjDir)*brdf*cos/hemi_pdf/RR
	HitRecord nextObj;
	Ray NextHitRay(rec.p, nextObjDir);
	isHit(NextHitRay, nextObj);
	if (nextObj.hitFlag && !nextObj.mptr->hasEmission())
	{
		L_indir = shade(nextObj, -nextObjDir)*
			rec.mptr->brdf(nextObjDir, wo, rec.normal)*
			std::max(0.0, dot(nextObjDir, rec.normal)) /
			hemi_pdf / RussianRoulette;
	}

	return L_dir + L_indir;


}


vec3 Scene::PathTracing(const Ray& r) const {
	HitRecord rec;
	if (!isHit(r, rec))return{};
	return shade(rec, -r.dir);
	
}