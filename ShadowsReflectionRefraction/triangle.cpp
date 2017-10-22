#include "triangle.h"

Triangle::Triangle(Vec3f &a, Vec3f &b, Vec3f &c, Material *m)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->material = m;
	Vec3f::Cross3(normal, b - a, c - a);
	this->ca = a - c;
	this->cb = b - c;
}

bool Triangle::intersect(const Ray &r, Hit &h, float tmin)
{
	bool result = false;
	Vec3f l = r.getOrigin() - c;
	Vec3f k = -1.0f * r.getDirection();
	float det = k.Dot3(normal);
	if (det != 0)
	{
		float dett = l.Dot3(normal);
		Vec3f tmp1 = Vec3f();
		Vec3f tmp2 = Vec3f();
		Vec3f::Cross3(tmp1, l, cb);
		Vec3f::Cross3(tmp2, ca, l);
		float detu = k.Dot3(tmp1);
		float detv = k.Dot3(tmp2);

		float t = dett / det;
		float u = detu / det;
		float v = detv / det;

		if (t > tmin && u >= 0 && v >= 0 && 1 - u - v >= 0)
		{
			if (t < h.getT())
			{
				result = true;
				Vec3f n = normal;
				n.Normalize();
				h.set(t, material, n, r);
			}
		}
	}

	return result;
}

void Triangle::paint()
{
	material->glSetMaterial();
	glBegin(GL_TRIANGLES);
	glNormal3f(normal.x(), normal.y(), normal.z());
	glVertex3f(a.x(), a.y(), a.z());
	glVertex3f(b.x(), b.y(), b.z());
	glVertex3f(c.x(), c.y(), c.z());
	glEnd();
}