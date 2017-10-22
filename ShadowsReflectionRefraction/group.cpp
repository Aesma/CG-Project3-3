#include "group.h"

Group::Group(int num_objects)
{
	this->num_objects = num_objects;
	this->object3ds = new Object3D*[num_objects];
}

bool Group::intersect(const Ray &r, Hit &h, float tmin)
{
	bool result = false;
	
	for (int i = 0; i < num_objects; i++)
	{
		if (object3ds[i]->intersect(r, h, tmin)){
			result = true;
		}
	}

	return result;
}

void Group::addObject(int index, Object3D *obj)
{
	object3ds[index] = obj;
}

void Group::paint()
{
	for (int i = 0; i < num_objects; i++)
	{
		object3ds[i]->paint();
	}
}

Group::~Group()
{
	delete[]object3ds;
}