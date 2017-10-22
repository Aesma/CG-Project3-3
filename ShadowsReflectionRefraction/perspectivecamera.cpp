#include "perspectivecamera.h"

PerspectiveCamera::PerspectiveCamera(Vec3f &center, Vec3f &direction, Vec3f &up, float angle)
{
	this->center = center;
	this->direction = direction;
	this->up = up;
	this->angle = angle;
	Vec3f::Cross3(this->horizontal, this->direction, this->up);
	Vec3f::Cross3(this->up, this->horizontal, this->direction);
	this->direction.Normalize();
	this->up.Normalize();
	this->horizontal.Normalize();
	this->distance = 1.0f / tanf(angle / 2);
}

Ray PerspectiveCamera::generateRay(Vec2f point)
{
	Vec3f dir = horizontal * point.x() + up * point.y() + (direction) * distance;
	dir.Normalize();

	return Ray(center, dir);
}

float PerspectiveCamera::getTMin() const
{
	return -1.0f * INT_MAX;
}

void PerspectiveCamera::glPlaceCamera()
{
	gluLookAt(center.x(), center.y(), center.z(), center.x() + direction.x(), center.y() + direction.y(), center.z() + direction.z(), up.x(), up.y(), up.z());
}

void PerspectiveCamera::dollyCamera(float dist)
{
	center = center + direction * dist;
}

void PerspectiveCamera::rotateCamera(float x_theta, float y_theta)
{
	float tiltAngle = acos(up.Dot3(direction));
	if (tiltAngle - y_theta > 3.13)
		y_theta = tiltAngle - 3.13;
	else if (tiltAngle - y_theta < 0.01)
		y_theta = tiltAngle - 0.01;

	Matrix rotMat = Matrix::MakeAxisRotation(up, x_theta);
	rotMat = Matrix::MakeAxisRotation(horizontal, y_theta);

	rotMat.Transform(center);
	rotMat.TransformDirection(direction);
	direction.Normalize();
}

void PerspectiveCamera::glInit(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle *180.0 / 3.14159, (float)w / float(h), 0.5, 40.0);
}

void PerspectiveCamera::truckCamera(float dx, float dy)
{
	Vec3f screenUp;
	Vec3f::Cross3(screenUp, horizontal, direction);
	center += horizontal * dx + screenUp * dy;
}

