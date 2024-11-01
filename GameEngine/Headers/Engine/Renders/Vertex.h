#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QVector2D>
#include <QVector4D>

const int POSITION_LENGTH = 3;
const int NORMAL_LENGTH = 3;
const int TEX_COORD_LENGTH = 2;

const int POSITION_OFFSET = 0;
const int NORMAL_OFFSET = POSITION_LENGTH + POSITION_OFFSET;
const int TEX_COORD_OFFSET = NORMAL_LENGTH + NORMAL_OFFSET;

const int VERTEX_LENGTH = POSITION_LENGTH + NORMAL_LENGTH + TEX_COORD_LENGTH;

struct Vertex {
    QVector3D position;
    QVector3D normal;
    QVector2D texCoord;
    QVector4D color;
};

#endif // VERTEX_H