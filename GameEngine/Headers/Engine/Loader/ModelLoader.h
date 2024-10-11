#ifndef MODELLOADER_H
#define MODELLOADER_H


#include "Engine/Render/Mesh.h"
#include <functional>

class ModelLoader {
public:

	class Range {
	public:
		float from;
		float to;
		float step;

		Range(float from, float to, float step) : from(from), to(to), step(step) {}
	};

	Mesh* LoadObjFile(const char* path);	
	Mesh* LoadTriangle();
	Mesh* LoadQuad();
	Mesh* LoadCube();
	Mesh* LoadCircle(int sector);
	Mesh* LoadCylinder(int sector);
	Mesh* LoadSphere(int sector, int stack);
	Mesh* LoadIcosphere(int subdivision);
	Mesh* LoadCubeSphere(int sector);
	Mesh* LoadCone(int sector);
	Mesh* LoadPlane(float (*func)(float, float), Range& xRange, Range& yRange);


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