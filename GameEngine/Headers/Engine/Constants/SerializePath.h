#ifndef SERIALIZE_PATH
#define SERIALIZE_PATH

#include <QString>

// Vertex
const QString SERIALIZE_VERTEX_POSITION = "position";
const QString SERIALIZE_VERTEX_NORMAL = "normal";
const QString SERIALIZE_VERTEX_TEX_COORD = "texCoord";
const QString SERIALIZE_VERTEX_COLOR = "color";

// Mesh
const QString SERIALIZE_MESH_PATH = "path";
const QString SERIALIZE_MESH_VERTICES = "vertices";
const QString SERIALIZE_MESH_INDICES = "indices";
const QString SERIALIZE_MESH_TEXTURES = "textures";
const QString SERIALIZE_MESH_DRAW_MODE = "draw_mode";

// Node
const QString SERIALIZE_NODE_NAME = "name";
const QString SERIALIZE_NODE_CHILDREN = "children";
const QString SERIALIZE_NODE_IS_ALIVE = "is_alive";

// Scene
const QString SERIALIZE_SCENE_NODES = "nodes";
const QString SERIALIZE_SCENE_MESHES = "meshes";



#endif // !SERIALIZE_PATH
