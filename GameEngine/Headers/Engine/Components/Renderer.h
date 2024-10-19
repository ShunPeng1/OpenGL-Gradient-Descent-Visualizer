#ifndef RENDERER_H
#define RENDERER_H

#include "Engine/Engine.h"
#include "Engine/Scenes/Component.h"

#include <qvector3d.h>

class Renderer : public Component
{
public:
	Renderer(GameObject* gameObject);
	virtual ~Renderer();

	void setMaterial(const QVector3D& material);
	QVector3D getMaterial();

	Renderer* clone() override;

private:
	QVector3D mMaterial;
};

#endif // !RENDERER_H
