#include "Engine/Components/Renderer.h"

Renderer::Renderer(GameObject* gameObject) : Component(gameObject)
{
}

Renderer::~Renderer()
{
}

void Renderer::setMaterial(const QVector3D& material)
{
}

QVector3D Renderer::getMaterial()
{
	return QVector3D();
}

Renderer* Renderer::clone()
{
	return nullptr;
}

