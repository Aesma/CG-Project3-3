#ifndef GROUP_H
#define GROUP_H

#include "object3d.h"

class Group :public Object3D
{
public:
	Group(int num_objects);
	virtual bool intersect(const Ray &r, Hit &h, float tmin);
	void addObject(int index, Object3D *obj);
	virtual void paint();
	~Group();
protected:
	Object3D** object3ds;
	int num_objects;
};

#endif