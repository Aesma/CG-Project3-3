#ifndef TRIANGLE
#define TRIANGLE

#include "object3d.h"

class Triangle :public Object3D
{
public:
	Triangle(Vec3f &a, Vec3f &b, Vec3f &c, Material *m);
	virtual bool intersect(const Ray &r, Hit &h, float tmin);
	virtual void paint();
private:
	Vec3f a;
	Vec3f b;
	Vec3f c;
	Vec3f normal;
	Vec3f ca;
	Vec3f cb;
};

#endif