#ifndef VERTEX_H
#define VERTEX_H

#include <glm.hpp>




const int POSITION_LENGTH = 3;
const int NORMAL_LENGTH = 3;
const int TEX_COORD_LENGTH = 2;

const int POSITION_OFFSET = 0;
const int NORMAL_OFFSET = POSITION_LENGTH + POSITION_OFFSET;
const int TEX_COORD_OFFSET = NORMAL_LENGTH + NORMAL_OFFSET;

const int VERTEX_LENGTH = POSITION_LENGTH + NORMAL_LENGTH + TEX_COORD_LENGTH;

struct Vertex {
    glm::vec3 positions;
    glm::vec3 normals;
    glm::vec2 texCoords;


};

#endif // VERTEX_H