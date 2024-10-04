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

	Mesh LoadObjFile(const char* path);	
	Mesh LoadTriangle();
	Mesh LoadQuad();
	Mesh LoadCube();
	Mesh LoadCircle(int sector);
	Mesh LoadCylinder(int sector);
	Mesh LoadSphere(int sector, int stack);
	Mesh LoadIcoshere(int subdivision);
	Mesh LoadCubeSphere(int sector);
	Mesh LoadCone(int sector);
	Mesh LoadPlane(std::function<float(float, float)> func, Range& xRange, Range& yRange);


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

	glm::vec3 getNormalFromOrigin(glm::vec3 origin, glm::vec3 point);


	ModelLoader() {};
};

#endif // MODELLOADER_H