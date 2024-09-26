#ifndef MODELLOADER_H
#define MODELLOADER_H


#include "Engine/Render/Mesh.h"

static class ModelLoader {
public:
	static Mesh loadModel(const char* path);	

};

#endif // MODELLOADER_H