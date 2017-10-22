#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H

#include <Windows.h>
#include <gl\GL.h>
#include <gl\glut.h>
#include "material.h"


class PhongMaterial :public Material
{
public:
	PhongMaterial(const Vec3f &diffuseColor,
		const Vec3f &specularColor,
		float exponent,
		const Vec3f &reflectiveColor,
		const Vec3f &transparentColor,
		float indexOfRefraction);
	virtual void glSetMaterial() const;
	virtual Vec3f shade(Ray ray, Hit hit, Vec3f directionToLight, Vec3f lightColor, bool shade_back);
};

#endif