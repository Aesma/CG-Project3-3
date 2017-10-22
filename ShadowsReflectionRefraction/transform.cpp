#include "transform.h"

Transform::Transform(Matrix &m, Object3D *o)
{
	this->transform_matrix = m;
	this->object3d = o;
}

bool Transform::intersect(const Ray &r, Hit &h, float tmin)
{
	bool result = false;
	Matrix tmp1_matrix = transform_matrix;
	if (tmp1_matrix.Inverse()){
		Vec3f direction = r.getDirection();
		Vec3f origin = r.getOrigin();
		tmp1_matrix.Transform(origin);
		tmp1_matrix.TransformDirection(direction);
		Ray ray = Ray(origin, direction);
		result = object3d->intersect(ray, h, tmin);
		if (result)
		{
			Vec3f n = h.getNormal();
			Matrix tmp2_matrix = tmp1_matrix;
			tmp2_matrix.Transpose();
			tmp2_matrix.TransformDirection(n);
			n.Normalize();
			h.set(h.getT(), h.getMaterial(), n, r);
		}
	}

	return result;
}

void Transform::paint()
{
	glPushMatrix();
	Matrix tmp = Matrix(transform_matrix);
	GLfloat *glMatrix = tmp.glGet();
	glMultMatrixf(glMatrix);
	delete[] glMatrix;
	object3d->paint();
	glPopMatrix();
}