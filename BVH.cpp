#include "BVH.h"

std::shared_ptr<bvhNode> BVH::BVHbuild(std::vector<std::shared_ptr<Object>> objects)
{

	std::shared_ptr<bvhNode> node = std::make_unique<bvhNode>();

	if (objects.size() == 1)
	{
		node->left = nullptr;
		node->right = nullptr;
		node->obj = objects[0];
		node->bbox = objects[0]->BoundingBox();
		return node;
	}

	if (objects.size() == 2)
	{
		node->left = BVHbuild(std::vector<std::shared_ptr<Object>>{ objects[0] });
		node->right = BVHbuild(std::vector<std::shared_ptr<Object>>{ objects[1] });
		node->bbox = Union(node->left->bbox, node->right->bbox);
		return node;
	}


	AABB bboxAllObjectForThisNode;
	for (int i = 0; i < objects.size(); ++i)
	{
		bboxAllObjectForThisNode = Union(bboxAllObjectForThisNode, objects[i]->BoundingBox());
	}
	int axis = bboxAllObjectForThisNode.maxRangeAxis();

	auto compare = [axis](std::shared_ptr<Object> a, std::shared_ptr<Object> b)
	{
		return a->BoundingBox().Centroid().e[axis] < b->BoundingBox().Centroid().e[axis];
	};
	std::sort(objects.begin(), objects.end(), compare);

	auto mid = objects.begin() + objects.size() / 2;

	node->left = BVHbuild(std::vector<std::shared_ptr<Object>>(objects.begin(), mid));
	node->right = BVHbuild(std::vector<std::shared_ptr<Object>>(mid, objects.end()));

	node->bbox = Union(node->left->bbox, node->right->bbox);

	return node;

}

void Intersection(const Ray& r, std::shared_ptr<bvhNode> node, HitRecord& rec)
{
	if (!node->bbox.hit(r))return;
	if (node->left == nullptr && node->right == nullptr)
	{
		node->obj->hit(r, 0.001,std::numeric_limits<float>::max(),rec);
		return;
	}

	HitRecord rec_left, rec_right;

	Intersection(r, node->left, rec_left);
	Intersection(r, node->right, rec_right);
	rec = rec_left.t < rec_right.t ? rec_left : rec_right;
}

bool BVH::hit(const Ray& r, HitRecord& rec)const
{
	if (!root->bbox.hit(r))return false;
	Intersection(r, root, rec);
	if (!rec.hitFlag)return false;
	return true;
}

