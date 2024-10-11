#include "Engine/Loaders/ModelLoader.h"
#include <QFile>
#include <QTextStream>
#include <map>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

Mesh* ModelLoader::loadObjFile(const char* path)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures; // Assuming you have a way to load textures

    std::vector<QVector3D> temp_positions;
    std::vector<QVector3D> temp_normals;
    std::vector<QVector2D> temp_texcoords;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return new Mesh(vertices, indices, textures);
    }

    QTextStream in(&file);
    QString line;
    while (in.readLineInto(&line)) {
        std::istringstream ss(line.toStdString());
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            QVector3D position;
            float x, y, z;
            ss >> x >> y >> z;
            position.setX(x);
            position.setY(y);
            position.setZ(z);
            temp_positions.push_back(position);
        }
        else if (prefix == "vt") {
            QVector2D texcoord;
            float x, y;
            ss >> x >> y;
            texcoord.setX(x);
            texcoord.setY(y);
            temp_texcoords.push_back(texcoord);
        }
        else if (prefix == "vn") {
            QVector3D normal;
            float x, y, z;
            ss >> x >> y >> z;
            normal.setX(x);
            normal.setY(y);
            normal.setZ(z);
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
                    vertex.texCoords = QVector2D(0.0f, 0.0f);
                }

                if (normalIndices[i] > 0 && normalIndices[i] <= temp_normals.size()) {
                    vertex.normals = temp_normals[normalIndices[i] - 1];
                }
                else {
                    vertex.normals = QVector3D(0.0f, 0.0f, 0.0f);
                }

                vertex.color = QVector4D(1.0f, 1.0f, 1.0f, 1.0f);

                vertices.push_back(vertex);
                indices.push_back(indices.size());
            }
        }
    }

    file.close();
    return new Mesh(vertices, indices, textures);
}


Mesh* ModelLoader::loadTriangle()
{
	std::vector<QVector3D> positions = {
		QVector3D(-0.5f, -0.5f, 0.0f),
		QVector3D(0.5f, -0.5f, 0.0f),
		QVector3D(0.0f, 0.5f, 0.0f)
	};

	std::vector<QVector3D> normals = {
		QVector3D(0.0f, 0.0f, 1.0f),
		QVector3D(0.0f, 0.0f, 1.0f),
		QVector3D(0.0f, 0.0f, 1.0f)
	};

	std::vector<QVector2D> texcoords = {
		QVector2D(0.0f, 0.0f),
		QVector2D(1.0f, 0.0f),
		QVector2D(0.5f, 1.0f)
	};

    std::vector<QVector4D> normalColors = {
		QVector4D(1.0f, 0.0f, 0.0f, 1.0f),
		QVector4D(0.0f, 1.0f, 0.0f, 1.0f),
		QVector4D(0.0f, 0.0f, 1.0f, 1.0f)
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
            vertex.color = QVector4D(1.0f, 1.0f, 1.0f, 1.0f);
        }
		vertices.push_back(vertex);
	}

	std::vector<unsigned int> indices = {
		0, 1, 2
	};

	return new Mesh(vertices, indices, {});
}

Mesh* ModelLoader::loadQuad()
{
    std::vector<QVector3D> positions = {
        QVector3D(-0.5f, -0.5f, 0.0f),
		QVector3D(-0.5f, 0.5f, 0.0f),
        QVector3D(0.5f, -0.5f, 0.0f),
        QVector3D(0.5f, 0.5f, 0.0f),
    };

    std::vector<QVector3D> normals = {
        QVector3D(0.0f, 0.0f, 1.0f),
        QVector3D(0.0f, 0.0f, 1.0f),
        QVector3D(0.0f, 0.0f, 1.0f),
        QVector3D(0.0f, 0.0f, 1.0f)
    };

    std::vector<QVector2D> texcoords = {
        QVector2D(0.0f, 0.0f),
		QVector2D(0.0f, 1.0f),
        QVector2D(1.0f, 0.0f),
		QVector2D(1.0f, 1.0f)
    };

    std::vector<QVector4D> normalColors = {
        QVector4D(1.0f, 0.0f, 0.0f, 1.0f),
		QVector4D(0.0f, 1.0f, 0.0f, 1.0f),
		QVector4D(0.0f, 0.0f, 1.0f, 1.0f),
		QVector4D(1.0f, 1.0f, 0.0f, 1.0f)
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
            vertex.color = QVector4D(1.0f, 1.0f, 1.0f, 1.0f);
        }
        vertices.push_back(vertex);
    }

    std::vector<unsigned int> indices = {
        0, 1, 2, 3
    };

    return new Mesh(vertices, indices, {}, GL_TRIANGLE_STRIP);
}

// https://stackoverflow.com/questions/28375338/cube-using-single-gl-triangle-strip
// From : 4 3 7 8 5 3 1 4 2 7 6 5 2 1
// To   : 3 2 6 7 4 2 0 3 1 6 5 4 1 0
Mesh* ModelLoader::loadCube()
{
    std::vector<QVector3D> positions = {
        QVector3D(0.5f, 0.5f, -0.5f),   // 1 0
        QVector3D(-0.5f, 0.5f, -0.5f),  // 2 1
        QVector3D(0.5f, -0.5f, -0.5f),  // 3 2
        QVector3D(-0.5f, -0.5f, -0.5f), // 4 3
        QVector3D(0.5f, 0.5f, 0.5f),    // 5 4
        QVector3D(-0.5f, 0.5f, 0.5f),   // 6 5
		QVector3D(-0.5f, -0.5f, 0.5f),  // 7 6
		QVector3D(0.5f, -0.5f, 0.5f),   // 8 7
    };

    std::vector<QVector3D> normals = {
        QVector3D(0.0f, 0.0f, 0.0f),
        QVector3D(0.0f, 0.0f, 0.0f),
        QVector3D(0.0f, 0.0f, 0.0f),
        QVector3D(0.0f, 0.0f, 0.0f),
		QVector3D(0.0f, 0.0f, 0.0f),
		QVector3D(0.0f, 0.0f, 0.0f),
		QVector3D(0.0f, 0.0f, 0.0f),
		QVector3D(0.0f, 0.0f, 0.0f)
    };

    std::vector<QVector2D> texcoords = {
        QVector2D(0.0f, 0.0f),
        QVector2D(0.0f, 0.0f),
        QVector2D(0.0f, 0.0f),
        QVector2D(0.0f, 0.0f),
		QVector2D(0.0f, 0.0f),
		QVector2D(0.0f, 0.0f),
		QVector2D(0.0f, 0.0f),
		QVector2D(0.0f, 0.0f)
    };

    std::vector<QVector4D> normalColors = {
        QVector4D(0.0f, 0.0f, 0.0f, 1.0f),
        QVector4D(1.0f, 0.0f, 0.0f, 1.0f),
        QVector4D(0.0f, 1.0f, 0.0f, 1.0f),
        QVector4D(1.0f, 1.0f, 0.0f, 1.0f),
		QVector4D(0.0f, 0.0f, 1.0f, 1.0f),
		QVector4D(0.0f, 1.0f, 1.0f, 1.0f),
		QVector4D(1.0f, 1.0f, 1.0f, 1.0f),
		QVector4D(0.0f, 1.0f, 1.0f, 1.0f)
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
            vertex.color = QVector4D(1.0f, 1.0f, 1.0f, 1.0f);
        }
        vertices.push_back(vertex);
    }

    std::vector<unsigned int> indices = {
        3, 2, 6, 7, 4, 2, 0, 3, 1, 6, 5, 4, 1, 0
    };

    return new Mesh(vertices, indices, {}, GL_TRIANGLE_STRIP);
}

Mesh* ModelLoader::loadCircle(int sector)
{
    std::vector<QVector3D> positions;
	std::vector<QVector3D> normals;
	std::vector<QVector2D> texcoords;
	std::vector<QVector4D> normalColors;

	std::vector<Vertex> vertices;

	std::vector<unsigned int> indices;

	for (int i = 0; i < sector; i++) {
		float angle = 2.0f * M_PI * i / sector;
		float x = cos(angle);
		float y = sin(angle);

		positions.push_back(QVector3D(x, y, 0.0f));

		normals.push_back(QVector3D(0.0f, 0.0f, 1.0f));

		texcoords.push_back(QVector2D(x, y));

		normalColors.push_back(QVector4D(1.0f, 1.0f, 1.0f, 1.0f));

		Vertex vertex = {};
		vertex.positions = positions[i];
		vertex.normals = normals[i];
		vertex.texCoords = texcoords[i];
		vertex.color = normalColors[i];

		vertices.push_back(vertex);

		indices.push_back(i);

	}
	return new Mesh(vertices, indices, {}, GL_TRIANGLE_FAN);
}

Mesh* ModelLoader::loadCylinder(int sector)
{
    std::vector<QVector3D> positions;
    std::vector<QVector3D> normals;
    std::vector<QVector2D> texcoords;
    std::vector<QVector4D> normalColors;
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
        positions.push_back(QVector3D(x, y, halfHeight));
        normals.push_back(QVector3D(0.0f, 0.0f, 1.0f));
        texcoords.push_back(QVector2D((x / radius + 1.0f) / 2.0f, (y / radius + 1.0f) / 2.0f));
        if (mUseNormalColor) {
            normalColors.push_back(QVector4D(getNormalFromOrigin(QVector3D(0.0f, 0.0f, halfHeight), QVector3D(x, y, halfHeight)), 1));
        }
        else {
            normalColors.push_back(QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
        }

        // Bottom circle
        positions.push_back(QVector3D(x, y, -halfHeight));
        normals.push_back(QVector3D(0.0f, 0.0f, -1.0f));
        texcoords.push_back(QVector2D((x / radius + 1.0f) / 2.0f, (y / radius + 1.0f) / 2.0f));
        if (mUseNormalColor) {
            normalColors.push_back(QVector4D(getNormalFromOrigin(QVector3D(0.0f, 0.0f, -halfHeight), QVector3D(x, y, -halfHeight)), 1));
        }
        else {
            normalColors.push_back(QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
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
        QVector3D(0.0f, 0.0f, halfHeight),
        QVector3D(0.0f, 0.0f, 1.0f),
        QVector2D(0.5f, 0.5f),
        QVector4D(1.0f, 1.0f, 1.0f, 1.0f)
    };
    Vertex bottomCenterVertex = {
        QVector3D(0.0f, 0.0f, -halfHeight),
        QVector3D(0.0f, 0.0f, -1.0f),
        QVector2D(0.5f, 0.5f),
        QVector4D(1.0f, 1.0f, 1.0f, 1.0f)
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
    indices.push_back(indices[indices.size() - 1]);
    indices.push_back(0);
    // Add indices for the side of the cylinder
    for (int i = 0; i < sector; ++i) {
        indices.push_back(i % sector * 2);
        indices.push_back(i % sector * 2 + 1);
    }
	indices.push_back(0);
	indices.push_back(1);
	

    return new Mesh(vertices, indices, {}, GL_TRIANGLE_STRIP);
}

Mesh* ModelLoader::loadSphere(int sector, int stack)
{
    std::vector<QVector3D> positions;
    std::vector<QVector3D> normals;
    std::vector<QVector2D> texcoords;
    std::vector<QVector4D> normalColors;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    float radius = 1.0f;
    float sectorAngleStep = 2.0f * M_PI / sector;
	float stackAngleStep = M_PI / (stack-1);



    for (int j = 1; j < stack-1; j++) {
        float stackAngle = j * stackAngleStep;
        float z = radius * cos(stackAngle);

        for (int i = 0; i < sector; ++i) {
            float sectorAngle = i * sectorAngleStep;
            float x = radius * sin(stackAngle) * cos(sectorAngle);
            float y = radius * sin(stackAngle) * sin(sectorAngle);

        
            positions.push_back(QVector3D(x, y, z));
            normals.push_back(QVector3D(0.0f, 0.0f, 1.0f));
            texcoords.push_back(QVector2D((x / radius + 1.0f) / 2.0f, (y / radius + 1.0f) / 2.0f));
            if (mUseNormalColor) {
                normalColors.push_back(QVector4D(getNormalFromOrigin(QVector3D(0.0f, 0.0f, 0.0f), QVector3D(x, y, z)), 1));
            }
            else {
                normalColors.push_back(QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
            }

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
        QVector3D(0.0f, 0.0f, radius),
        QVector3D(0.0f, 0.0f, 1.0f),
        QVector2D(0.5f, 0.5f),
        QVector4D(1.0f, 1.0f, 1.0f, 1.0f)
    };
    Vertex bottomCenterVertex = {
        QVector3D(0.0f, 0.0f, -radius),
        QVector3D(0.0f, 0.0f, 1.0f),
        QVector2D(0.5f, 0.5f),
        QVector4D(0.0f, 0.0f, 0.0f, 1.0f)
    };

    int topCenterIndex = vertices.size();
    vertices.push_back(topCenterVertex);

    int bottomCenterIndex = vertices.size();
    vertices.push_back(bottomCenterVertex);


    for (int j = 0; j < stack - 1; j++) {
        for (int i = 0; i < sector; ++i) {
            indices.push_back(j - 1 == -1 ? topCenterIndex : (j - 1) * sector + i);
			indices.push_back(j == stack - 2 ? bottomCenterIndex : j * sector + i);
		}

		indices.push_back(j - 1 == -1 ? topCenterIndex : (j - 1) * sector);
		indices.push_back(j == stack - 2 ? bottomCenterIndex : j * sector);

	}


    return new Mesh(vertices, indices, {}, GL_TRIANGLE_STRIP);
}

unsigned int addMiddlePoint(unsigned int p1, unsigned int p2, std::vector<QVector3D>& vertices, std::map<uint64_t, unsigned int> &middlePointCache) {
    uint64_t smallerIndex = std::min(p1, p2);
    uint64_t greaterIndex = std::max(p1, p2);
    uint64_t key = (smallerIndex << 32) + greaterIndex;

    auto it = middlePointCache.find(key);
    if (it != middlePointCache.end()) {
        return it->second;
    }

    QVector3D point1 = vertices[p1];
    QVector3D point2 = vertices[p2];
    QVector3D middle = (point1 + point2) * 0.5f;
    middle.normalize();
    vertices.push_back(middle);
    unsigned int index = vertices.size() - 1;
    middlePointCache[key] = index;
    return index;
}

Mesh* ModelLoader::loadIcosphere(int subdivision)
{
	std::vector<QVector3D> positions(12);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

    // constants
    const float PI = 3.1415926f;
    const float H_ANGLE = PI / 180 * 72;    // 72 degree = 360 / 5
    const float V_ANGLE = atanf(1.0f / 2);  // elevation = 26.565 degree
    const float RADIUS = 1.0f;

    float z, xy;                            // coords
    float hAngle1 = -PI / 2 - H_ANGLE / 2;  // start from -126 deg at 1st row
    float hAngle2 = -PI / 2;                // start from -90 deg at 2nd row

    // the first top vertex at (0, 0, r)
    positions[0] = QVector3D(0, 0, RADIUS);
    positions[11] = QVector3D(0, 0, -RADIUS);

    // compute 10 vertices at 1st and 2nd rows
    for (int i = 1; i <= 5; ++i)
    {
        int i1 = i;         // index for 1st row
		int nextI1 = i % 5 + 1; // index for next vertex in 1st row
        int i2 = (i + 5);   // index for 2nd row
		int nextI2 = (i) % 5 + 6; // index for next vertex in 2nd row

        z = RADIUS * sinf(V_ANGLE);     // elevaton
        xy = RADIUS * cosf(V_ANGLE);    // length on XY plane

        positions[i1] = QVector3D(xy * cosf(hAngle1), xy * sinf(hAngle1), z);     // 1st row
        positions[i2] = QVector3D(xy * cosf(hAngle2), xy * sinf(hAngle2), -z);    // 2nd row

        // next horizontal angles
        hAngle1 += H_ANGLE;
        hAngle2 += H_ANGLE;

		// add indices
		indices.push_back(0);
		indices.push_back(i1);
		indices.push_back(nextI1);

		indices.push_back(11);
		indices.push_back(i2);
		indices.push_back(nextI2);

		indices.push_back(i1);
		indices.push_back(i2);
		indices.push_back(nextI1);

		indices.push_back(nextI1);
		indices.push_back(i2);
		indices.push_back(nextI2);
    }
    
    
    
    std::map<uint64_t, unsigned int> middlePointCache;

    for (int i = 0; i < subdivision; ++i) {
        std::vector<unsigned int> newIndices;
        for (size_t j = 0; j < indices.size(); j += 3) {
            unsigned int a = addMiddlePoint(indices[j], indices[j + 1], positions, middlePointCache);
            unsigned int b = addMiddlePoint(indices[j + 1], indices[j + 2], positions, middlePointCache);
            unsigned int c = addMiddlePoint(indices[j + 2], indices[j], positions, middlePointCache);

            newIndices.push_back(indices[j]);
            newIndices.push_back(a);
            newIndices.push_back(c);

            newIndices.push_back(indices[j + 1]);
            newIndices.push_back(b);
            newIndices.push_back(a);

            newIndices.push_back(indices[j + 2]);
            newIndices.push_back(c);
            newIndices.push_back(b);

            newIndices.push_back(a);
            newIndices.push_back(b);
            newIndices.push_back(c);
        }
        indices = newIndices;
    }

    for (const auto& pos : positions) {
        Vertex vertex;
        vertex.positions = pos;
        vertex.normals = pos;
        vertex.texCoords = QVector2D(0.0f, 0.0f); // Placeholder, you can calculate proper UVs if needed
        if (mUseNormalColor) {
            vertex.color = QVector4D(getNormalFromOrigin(QVector3D(0.0f, 0.0f, 0.0f), QVector3D(pos)), 1);
        }
        else {
            vertex.color = QVector4D(1.0f, 1.0f, 1.0f, 1.0f);
        }
        vertices.push_back(vertex);
    }

	return new Mesh(vertices, indices, {}, GL_TRIANGLES);

}

Mesh* ModelLoader::loadCubeSphere(int subdivision)
{
    



    return new Mesh({}, {}, {});
}

Mesh* ModelLoader::loadCone(int sector)
{
    std::vector<QVector3D> positions;
    std::vector<QVector3D> normals;
    std::vector<QVector2D> texcoords;
    std::vector<QVector4D> normalColors;
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

        // Bottom circle
        positions.push_back(QVector3D(x, y, -halfHeight));
        normals.push_back(QVector3D(0.0f, 0.0f, -1.0f));
        texcoords.push_back(QVector2D((x / radius + 1.0f) / 2.0f, (y / radius + 1.0f) / 2.0f));
        if (mUseNormalColor) {
            normalColors.push_back(QVector4D(getNormalFromOrigin(QVector3D(0.0f, 0.0f, -halfHeight), QVector3D(x, y, -halfHeight)), 1));
        }
        else {
            normalColors.push_back(QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
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
        QVector3D(0.0f, 0.0f, halfHeight),
        QVector3D(0.0f, 0.0f, 1.0f),
        QVector2D(0.5f, 0.5f),
        QVector4D(1.0f, 1.0f, 1.0f, 1.0f)
    };
    int topCenterIndex = vertices.size();
    vertices.push_back(topCenterVertex);



	// Add indices for the bottom circle
    for (int i = 0; i < sector / 2; ++i) {
        indices.push_back((sector - i - 1));
        indices.push_back(i);
    }

	indices.push_back(indices[indices.size() - 1]);
	indices.push_back(0);

	// Add indices for the side of the cone
	for (int i = 0; i < sector; ++i) {
		indices.push_back(i);
		indices.push_back(topCenterIndex);
	}
	indices.push_back(0);
	indices.push_back(topCenterIndex);



    return new Mesh(vertices, indices, {}, GL_TRIANGLE_STRIP);
}

void getHeatMapColor(float value, float* red, float* green, float* blue)
{
    const int NUM_COLORS = 4;
    static float color[NUM_COLORS][3] = { {0,0,1}, {0,1,0}, {1,1,0}, {1,0,0} };

    int idx1, idx2;
    float fractBetween = 0;

    if (value <= 0) {
        idx1 = idx2 = 0;
    }
    else if (value >= 1) {
        idx1 = idx2 = NUM_COLORS - 1;
    }
    else {
        value = value * (NUM_COLORS - 1);
        idx1 = floor(value);
        idx2 = idx1 + 1;
        fractBetween = value - float(idx1);
    }

    *red = (color[idx2][0] - color[idx1][0]) * fractBetween + color[idx1][0];
    *green = (color[idx2][1] - color[idx1][1]) * fractBetween + color[idx1][1];
    *blue = (color[idx2][2] - color[idx1][2]) * fractBetween + color[idx1][2];

}

Mesh* ModelLoader::loadPlane(float (*func)(float, float), Range& xRange, Range& yRange)
{
    std::vector<QVector3D> positions;
    std::vector<QVector3D> normals;
    std::vector<QVector2D> texcoords;
    std::vector<QVector4D> normalColors;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    float xStep = (xRange.to - xRange.from) / xRange.step;
    float yStep = (yRange.to - yRange.from) / yRange.step;
    float minZ = std::numeric_limits<float>::max();
    float maxZ = std::numeric_limits<float>::lowest();

    for (int i = 0; i <= xStep; i++) {
        for (int j = 0; j <= yStep; j++) {
            float x = xRange.from + i * xRange.step;
            float y = yRange.from + j * yRange.step;
            float z = func(x, y);
            if (z < minZ) minZ = z;
            if (z > maxZ) maxZ = z;

        }
    }

    for (int i = 0; i <= xStep; i++) {
        for (int j = 0; j <= yStep; j++) {
            float x = xRange.from + i * xRange.step;
            float y = yRange.from + j * yRange.step;
            float z = func(x, y);

            positions.push_back(QVector3D(x, y, z));
            QVector3D normal = QVector3D::crossProduct(
                QVector3D(1.0f, 0.0f, func(x + 0.01f, y) - z),
                QVector3D(0.0f, 1.0f, func(x, y + 0.01f) - z)
            );
            normals.push_back(normal.normalized());

            texcoords.push_back(QVector2D(x, y));

            float r, g, b;
            float normalizedZ = (z - minZ) / (maxZ - minZ);
            getHeatMapColor(normalizedZ, &r, &g, &b);
            normalColors.push_back(QVector4D(r, g, b, 1.0f));
        }
    }

    for (int i = 0; i <= xStep; i++) {
        for (int j = 0; j <= yStep; j++) {
            int index = j + i * (yStep + 1);

            Vertex vertex = {};
            vertex.positions = positions[index];
            vertex.normals = normals[index];
            vertex.texCoords = texcoords[index];
            vertex.color = normalColors[index];
            vertices.push_back(vertex);
        }
    }

    for (int i = 0; i < xStep; i++) {
        for (int j = 0; j <= yStep; j++) {
            int index1 = j + i * (yStep + 1);
            int index2 = j + (i + 1) * (yStep + 1);

            indices.push_back(index1);
            indices.push_back(index2);
        }

        if (i < xStep - 1) {
            indices.push_back(indices[indices.size() - 1]);
            indices.push_back((i + 1) * (yStep + 1));
        }
    }

    return new Mesh(vertices, indices, {}, GL_TRIANGLE_STRIP);
}

QVector3D ModelLoader::getNormalFromOrigin(QVector3D origin, QVector3D point)
{
    return (point - origin).normalized();
}
