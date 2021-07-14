#include "MeshTriangle.h"
#include "ObjLoader.h"
MeshTriangle::MeshTriangle(std::string filename, std::shared_ptr<Material> _mptr)
{
	std::vector<vec3> vertexs;
	std::vector<std::vector<int>> faces;
	ObjLoad(filename, vertexs, faces);
	for (int i = 0; i < faces.size(); ++i)
	{
		triangles.emplace_back(vertexs[faces[i][0]], vertexs[faces[i][1]], vertexs[faces[i][2]], _mptr);
		bbox = Union(bbox, triangles[i].BoundingBox());
		area += triangles[i].getArea();
	}
	mptr = _mptr;
}

bool MeshTriangle::hit(const Ray & r, float tmin, float tmax, HitRecord & rec) const
{
	bool hitFlag = false;
	float closest_so_far = tmax;
	HitRecord tmp_rec;
	for (int i = 0; i < triangles.size(); ++i)
	{
		if (triangles[i].hit(r, tmin, closest_so_far, tmp_rec))
		{
			hitFlag = true;
			closest_so_far = tmp_rec.t;
			rec = tmp_rec;
		}
	}
	return hitFlag;
}

AABB MeshTriangle::BoundingBox() const
{
	return bbox;
}
