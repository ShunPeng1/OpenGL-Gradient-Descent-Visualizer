#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include <QOpenGLExtraFunctions>

#include "Engine/GameObjects/Container.h"

class MeshRenderer : public Container
{
public:
	MeshRenderer();
	virtual ~MeshRenderer() noexcept;


};

#endif // !MESH_RENDERER_H