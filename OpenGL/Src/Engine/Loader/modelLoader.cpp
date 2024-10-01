#include "Engine/Loader/ModelLoader.h"

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
    return Mesh({}, {}, {});
}

Mesh ModelLoader::LoadCube()
{
    return Mesh({}, {}, {});
}

Mesh ModelLoader::LoadCylinder(float height, float radius)
{
    return Mesh({}, {}, {});
}

Mesh ModelLoader::LoadSphere(float radius, int sector, int stack)
{
    return Mesh({}, {}, {});
}

Mesh ModelLoader::LoadCone(float height, float radius)
{
    return Mesh({}, {}, {});
}

Mesh ModelLoader::LoadPlane()
{
    return Mesh({}, {}, {});
}
