#include "Engine/Render/mesh.h"

Mesh::Mesh(const std::vector<glm::vec3>& positions,
    const std::vector<unsigned int>& indices,
    const std::vector<glm::vec4>& colors,
    const std::vector<glm::vec3>& normals,
    const std::vector<glm::vec2>& textureCoords,
    ColorType colorType)
    : positions(positions),
    indices(indices),
    colors(colors),
    normals(normals),
    textureCoords(textureCoords),
    colorType(colorType) {

    this->colorLength = static_cast<int>(colorType);

    this->positionsOffset = 0;
    this->colorsOffset = this->positionsOffset + this->positionLength;
    this->normalsOffset = this->colorsOffset + this->colorLength;
    this->textureCoordsOffset = this->normalsOffset + this->normalLength;
    this->vertexLength = this->positionLength + this->colorLength + this->normalLength + this->textureCoordsLength;

    this->indicesLength = static_cast<int>(indices.size());

    for (size_t i = 0; i < positions.size(); ++i) {
        vboData.push_back(positions[i].x);
        vboData.push_back(positions[i].y);
        vboData.push_back(positions[i].z);

        vboData.push_back(colors[i].r);
        vboData.push_back(colors[i].g);
        vboData.push_back(colors[i].b);
        vboData.push_back(colors[i].a);

        vboData.push_back(normals[i].x);
        vboData.push_back(normals[i].y);
        vboData.push_back(normals[i].z);

        vboData.push_back(textureCoords[i].x);
        vboData.push_back(textureCoords[i].y);
    }
}

const std::vector<glm::vec3>& Mesh::getPositions() const {
    return positions;
}

const std::vector<unsigned int>& Mesh::getIndices() const {
    return indices;
}

const std::vector<glm::vec4>& Mesh::getColors() const {
    return colors;
}

const std::vector<glm::vec3>& Mesh::getNormals() const {
    return normals;
}

const std::vector<glm::vec2>& Mesh::getTextureCoords() const {
    return textureCoords;
}

ColorType Mesh::getColorType() const {
    return colorType;
}

int Mesh::getPositionsOffset() const {
    return positionsOffset;
}

int Mesh::getColorsOffset() const {
    return colorsOffset;
}

int Mesh::getNormalsOffset() const {
    return normalsOffset;
}

int Mesh::getTextureCoordsOffset() const {
    return textureCoordsOffset;
}

int Mesh::getVertexLength() const {
    return vertexLength;
}

const std::vector<float>& Mesh::getVboData() const {
    return vboData;
}

const std::vector<unsigned int>& Mesh::getEboData() const {
    return indices;
}

int Mesh::getPositionLength() const {
    return positionLength;
}

int Mesh::getColorLength() const {
    return colorLength;
}

int Mesh::getNormalLength() const {
    return normalLength;
}

int Mesh::getTextureCoordsLength() const {
    return textureCoordsLength;
}

int Mesh::getPositionsLength() const {
    return static_cast<int>(positions.size());
}

int Mesh::getIndicesLength() const {
    return indicesLength;
}