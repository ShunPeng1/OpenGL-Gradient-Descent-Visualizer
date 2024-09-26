#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm.hpp>

enum class ColorType {
    RGB = 3,
    RGBA = 4
};

class Mesh {
private:
    std::vector<glm::vec3> positions;
    std::vector<unsigned int> indices;
    std::vector<glm::vec4> colors;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoords;
    ColorType colorType;

    int positionLength = 3;
    int colorLength = 4;
    int normalLength = 3;
    int textureCoordsLength = 2;

    int positionsOffset = 0;
    int colorsOffset = 0;
    int normalsOffset = 0;
    int textureCoordsOffset = 0;

    std::vector<float> vboData;
    int vertexLength = 0;
    int indicesLength = 0;

public:
    Mesh(const std::vector<glm::vec3>& positions, const std::vector<unsigned int>& indices, const std::vector<glm::vec4>& colors, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& textureCoords, ColorType colorType = ColorType::RGBA);

    const std::vector<glm::vec3>& getPositions() const;
    const std::vector<unsigned int>& getIndices() const;
    const std::vector<glm::vec4>& getColors() const;
    const std::vector<glm::vec3>& getNormals() const;
    const std::vector<glm::vec2>& getTextureCoords() const;
    ColorType getColorType() const;

    int getPositionsOffset() const;
    int getColorsOffset() const;
    int getNormalsOffset() const;
    int getTextureCoordsOffset() const;
    int getVertexLength() const;
    const std::vector<float>& getVboData() const;
    const std::vector<unsigned int>& getEboData() const;

    int getPositionLength() const;
    int getColorLength() const;
    int getNormalLength() const;
    int getTextureCoordsLength() const;
    int getPositionsLength() const;
    int getIndicesLength() const;
};

#endif // MESH_H