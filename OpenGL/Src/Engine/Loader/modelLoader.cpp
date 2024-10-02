#include "Engine/Loader/ModelLoader.h"

const float M_PI = 3.14159265358979323846f;




Mesh ModelLoader::LoadObjFile(const char* path)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures; // Assuming you have a way to load textures

    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec3> temp_normals;
    std::vector<glm::vec2> temp_texcoords;

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open .obj file");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            glm::vec3 position;
            ss >> position.x >> position.y >> position.z;
            temp_positions.push_back(position);
        }
        else if (prefix == "vt") {
            glm::vec2 texcoord;
            ss >> texcoord.x >> texcoord.y;
            temp_texcoords.push_back(texcoord);
        }
        else if (prefix == "vn") {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
        }
        else if (prefix == "f") {
            std::vector<unsigned int> vertexIndices, texcoordIndices, normalIndices;
            std::string vertexData;
            while (ss >> vertexData) {
                std::istringstream vss(vertexData);
                std::string index;
                unsigned int vertexIndex = 0, texcoordIndex = 0, normalIndex = 0;

                std::getline(vss, index, '/');
                if (!index.empty()) vertexIndex = std::stoi(index);
                if (vss.peek() == '/') {
                    vss.ignore();
                    if (vss.peek() != '/') {
                        std::getline(vss, index, '/');
                        if (!index.empty()) texcoordIndex = std::stoi(index);
                    }
                    if (vss.peek() == '/') {
                        vss.ignore();
                        std::getline(vss, index);
                        if (!index.empty()) normalIndex = std::stoi(index);
                    }
                }

                vertexIndices.push_back(vertexIndex);
                texcoordIndices.push_back(texcoordIndex);
                normalIndices.push_back(normalIndex);
            }

            for (size_t i = 0; i < vertexIndices.size(); i++) {
                Vertex vertex = {};
                vertex.positions = temp_positions[vertexIndices[i] - 1];
                if (texcoordIndices[i] > 0 && texcoordIndices[i] <= temp_texcoords.size()) {
                    vertex.texCoords = temp_texcoords[texcoordIndices[i] - 1];
                }
                else {
                    vertex.texCoords = glm::vec2(0.0f, 0.0f);
                }

                if (normalIndices[i] > 0 && normalIndices[i] <= temp_normals.size()) {
                    vertex.normals = temp_normals[normalIndices[i] - 1];
                }
                else {
                    vertex.normals = glm::vec3(0.0f, 0.0f, 0.0f);
                }

				vertex.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

                vertices.push_back(vertex);
                indices.push_back(indices.size());
            }
        }
    }

    file.close();
    return Mesh(vertices, indices, textures);
}

Mesh ModelLoader::LoadTriangle()
{
	std::vector<glm::vec3> positions = {
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(0.0f, 0.5f, 0.0f)
	};

	std::vector<glm::vec3> normals = {
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};

	std::vector<glm::vec2> texcoords = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.5f, 1.0f)
	};

    std::vector<glm::vec4> normalColors = {
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
    };

	std::vector<Vertex> vertices;
	for (size_t i = 0; i < positions.size(); i++) {
		Vertex vertex = {};
		vertex.positions = positions[i];
		vertex.normals = normals[i];
		vertex.texCoords = texcoords[i];
	
        if (mUseNormalColor) {
			vertex.color = normalColors[i];
        }
        else {
            vertex.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        }
		vertices.push_back(vertex);
	}

	std::vector<unsigned int> indices = {
		0, 1, 2
	};

	return Mesh(vertices, indices, {});
}

Mesh ModelLoader::LoadQuad()
{
    std::vector<glm::vec3> positions = {
        glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(-0.5f, 0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
        glm::vec3(0.5f, 0.5f, 0.0f),
    };

    std::vector<glm::vec3> normals = {
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    };

    std::vector<glm::vec2> texcoords = {
        glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f)
    };

    std::vector<glm::vec4> normalColors = {
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)
    };

    std::vector<Vertex> vertices;
    for (size_t i = 0; i < positions.size(); i++) {
        Vertex vertex = {};
        vertex.positions = positions[i];
        vertex.normals = normals[i];
        vertex.texCoords = texcoords[i];

        if (mUseNormalColor) {
            vertex.color = normalColors[i];
        }
        else {
            vertex.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        }
        vertices.push_back(vertex);
    }

    std::vector<unsigned int> indices = {
        0, 1, 2, 3
    };

    return Mesh(vertices, indices, {}, GL_TRIANGLE_STRIP);
}

// https://stackoverflow.com/questions/28375338/cube-using-single-gl-triangle-strip
// From : 4 3 7 8 5 3 1 4 2 7 6 5 2 1
// To   : 3 2 6 7 4 2 0 3 1 6 5 4 1 0
Mesh ModelLoader::LoadCube()
{
    std::vector<glm::vec3> positions = {
        glm::vec3(0.5f, 0.5f, -0.5f),   // 1 0
        glm::vec3(-0.5f, 0.5f, -0.5f),  // 2 1
        glm::vec3(0.5f, -0.5f, -0.5f),  // 3 2
        glm::vec3(-0.5f, -0.5f, -0.5f), // 4 3
        glm::vec3(0.5f, 0.5f, 0.5f),    // 5 4
        glm::vec3(-0.5f, 0.5f, 0.5f),   // 6 5
		glm::vec3(-0.5f, -0.5f, 0.5f),  // 7 6
		glm::vec3(0.5f, -0.5f, 0.5f),   // 8 7
    };

    std::vector<glm::vec3> normals = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f)
    };

    std::vector<glm::vec2> texcoords = {
        glm::vec2(0.0f, 0.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 0.0f)
    };

    std::vector<glm::vec4> normalColors = {
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)
    };

    std::vector<Vertex> vertices;
    for (size_t i = 0; i < positions.size(); i++) {
        Vertex vertex = {};
        vertex.positions = positions[i];
        vertex.normals = normals[i];
        vertex.texCoords = texcoords[i];

        if (mUseNormalColor) {
            vertex.color = normalColors[i];
        }
        else {
            vertex.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        }
        vertices.push_back(vertex);
    }

    std::vector<unsigned int> indices = {
        3, 2, 6, 7, 4, 2, 0, 3, 1, 6, 5, 4, 1, 0
    };

    return Mesh(vertices, indices, {}, GL_TRIANGLE_STRIP);
}

Mesh ModelLoader::LoadCircle(int sector)
{
    std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	std::vector<glm::vec4> normalColors;

	std::vector<Vertex> vertices;

	std::vector<unsigned int> indices;

	for (int i = 0; i < sector; i++) {
		float angle = 2.0f * M_PI * i / sector;
		float x = cos(angle);
		float y = sin(angle);

		positions.push_back(glm::vec3(x, y, 0.0f));

		normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

		texcoords.push_back(glm::vec2(x, y));

		normalColors.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		Vertex vertex = {};
		vertex.positions = positions[i];
		vertex.normals = normals[i];
		vertex.texCoords = texcoords[i];
		vertex.color = normalColors[i];

		vertices.push_back(vertex);

		indices.push_back(i);

	}
	return Mesh(vertices, indices, {}, GL_TRIANGLE_FAN);
}

Mesh ModelLoader::LoadCylinder(int sector)
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texcoords;
    std::vector<glm::vec4> normalColors;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    float radius = 1.0f;
    float height = 1.0f;
    float halfHeight = height / 2.0f;
    float angleStep = 2.0f * M_PI / sector;

    // Generate vertices for the top and bottom circles
    for (int i = 0; i < sector; ++i) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        // Top circle
        positions.push_back(glm::vec3(x, y, halfHeight));
        normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
        texcoords.push_back(glm::vec2((x / radius + 1.0f) / 2.0f, (y / radius + 1.0f) / 2.0f));
        if (mUseNormalColor) {
            normalColors.push_back(glm::vec4(getNormalFromOrigin(glm::vec3(0.0f, 0.0f, halfHeight), glm::vec3(x, y, halfHeight)), 1));
        }
        else {
            normalColors.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        }

        // Bottom circle
        positions.push_back(glm::vec3(x, y, -halfHeight));
        normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
        texcoords.push_back(glm::vec2((x / radius + 1.0f) / 2.0f, (y / radius + 1.0f) / 2.0f));
        if (mUseNormalColor) {
            normalColors.push_back(glm::vec4(getNormalFromOrigin(glm::vec3(0.0f, 0.0f, -halfHeight), glm::vec3(x, y, -halfHeight)), 1));
        }
        else {
            normalColors.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }

    // Create vertices and indices
    for (size_t i = 0; i < positions.size(); ++i) {
        Vertex vertex = {};
        vertex.positions = positions[i];
        vertex.normals = normals[i];
        vertex.texCoords = texcoords[i];
        vertex.color = normalColors[i];
        vertices.push_back(vertex);
    }

    // Add the top and bottom center vertices
    Vertex topCenterVertex = {
        glm::vec3(0.0f, 0.0f, halfHeight),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec2(0.5f, 0.5f),
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
    };
    Vertex bottomCenterVertex = {
        glm::vec3(0.0f, 0.0f, -halfHeight),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec2(0.5f, 0.5f),
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
    };

    int topCenterIndex = vertices.size();
    vertices.push_back(topCenterVertex);

    int bottomCenterIndex = vertices.size();
    vertices.push_back(bottomCenterVertex);

    // Add indices for the top and bottom circles
    for (int i = 0; i < sector/2; ++i) {
        indices.push_back((sector - i - 1) * 2);
        indices.push_back(i * 2);
    }
	indices.push_back(indices[indices.size() - 1]);
    indices.push_back((sector - sector / 2) * 2 + 1);
    for (int i = sector / 2 - 1; i >= 0; --i) {
        indices.push_back((sector - i - 1) * 2 + 1);
        indices.push_back(i * 2 + 1);
    }
    /*indices.push_back(indices[indices.size() - 1]);
    indices.push_back(0);
    // Add indices for the side of the cylinder
    for (int i = 0; i < sector; ++i) {
        indices.push_back(i % sector * 2);
        indices.push_back(i % sector * 2 + 1);
    }
	indices.push_back(0);
	indices.push_back(1);
	*/

    return Mesh(vertices, indices, {}, GL_TRIANGLE_STRIP);
}

Mesh ModelLoader::LoadSphere(int sector, int stack)
{
    return Mesh({}, {}, {});
}

Mesh ModelLoader::LoadCone(int sector)
{
    return Mesh({}, {}, {});
}

Mesh ModelLoader::LoadPlane()
{
    return Mesh({}, {}, {});
}

glm::vec3 ModelLoader::getNormalFromOrigin(glm::vec3 origin, glm::vec3 point)
{
	return glm::normalize(point - origin);
}
