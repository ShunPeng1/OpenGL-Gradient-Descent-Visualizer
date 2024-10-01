#ifndef MODELLOADER_H
#define MODELLOADER_H


#include "Engine/Render/Mesh.h"

static class ModelLoader {
public:
	static Mesh LoadObjFile(const char* path);	

private: 
	ModelLoader() {}
	~ModelLoader() {}
};

#endif // MODELLOADER_H