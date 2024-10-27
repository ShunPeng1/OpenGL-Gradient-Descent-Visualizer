#ifndef RENDERER_H
#define RENDERER_H

#include "Engine/Engine.h"

#include <qvector3d.h>

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	void setMaterial(const QVector3D& material);
	QVector3D getMaterial();

private:
	QVector3D mMaterial;
};

#endif // !RENDERER_H
