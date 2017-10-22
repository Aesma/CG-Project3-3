#ifndef SPHERE_H
#define SPHERE_H

#include "object3d.h"

class Sphere:public Object3D
{
public:
	Sphere(Vec3f center, float radius, Material* material);
	virtual bool intersect(const Ray &r, Hit &h, float tmin);
	virtual void paint();
	~Sphere();
protected:
	Vec3f center;
	float radius;
};

#endif