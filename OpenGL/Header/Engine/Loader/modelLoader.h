#ifndef MODELLOADER_H
#define MODELLOADER_H


#include "Engine/Render/Mesh.h"

class ModelLoader {
public:

	Mesh LoadObjFile(const char* path);	
	Mesh LoadTriangle();
	Mesh LoadQuad();
	Mesh LoadCube();
	Mesh LoadCylinder(float height, float radius);
	Mesh LoadSphere(float radius, int sector, int stack);
	Mesh LoadCone(float height, float radius);
	Mesh LoadPlane();

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



	ModelLoader() {};
};

#endif // MODELLOADER_H