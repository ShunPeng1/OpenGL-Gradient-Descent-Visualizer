#ifndef MODELLOADER_H
#define MODELLOADER_H


#include "Engine/Renders/Mesh.h"
#include "Engine/Constants/ResourcePath.h"
#include <QJSEngine>
#include <QJSValueIterator>

class ModelLoader {
public:


	Mesh* loadObjFile(const char* path);	
	Mesh* loadTriangle();
	Mesh* loadQuad();
	Mesh* loadCube();
	Mesh* loadCircle(int sector);
	Mesh* loadCylinder(int sector);
	Mesh* loadSphere(int sector, int stack);
	Mesh* loadIcosphere(int subdivision);
	Mesh* loadCubeSphere(int sector);
	Mesh* loadCone(int sector);

	class Builder {
	public:
		Builder() {
			mUseNormalColor = false;
		}

		Builder& SetUseNormalColor(bool useNormalColor) {
			this->mUseNormalColor = useNormalColor;
			return *this;
		}

		ModelLoader Build() {
			ModelLoader modelLoader;
			modelLoader.mUseNormalColor = mUseNormalColor;
			return modelLoader;
		}

	private:
		bool mUseNormalColor;
	};
	

	~ModelLoader() {};
private: 
	bool mUseNormalColor;

	QVector3D getNormalFromOrigin(QVector3D origin, QVector3D point);


	ModelLoader() {};
};

#endif // MODELLOADER_H