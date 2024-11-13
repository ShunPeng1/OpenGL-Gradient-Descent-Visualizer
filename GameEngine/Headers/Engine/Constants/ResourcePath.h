#ifndef RESOURCE_PATH_H
#define RESOURCE_PATH_H


const QString SEPARATOR = "/";

const QString DEFAULT_MODEL_PATH = "Models" + SEPARATOR +"Default" + SEPARATOR;
const QString DEFAULT_TEXTURE_PATH = "Textures" + SEPARATOR + "Default" + SEPARATOR;
const QString DEFAULT_SHADER_PATH = "Shaders" + SEPARATOR + "Default" + SEPARATOR;

// Model paths
const QString MODEL_CUBE = DEFAULT_MODEL_PATH + "cube";
const QString MODEL_SPHERE = DEFAULT_MODEL_PATH + "sphere";
const QString MODEL_ICOSPHERE = DEFAULT_MODEL_PATH + "icosphere";
const QString MODEL_CYLINDER = DEFAULT_MODEL_PATH + "cylinder";
const QString MODEL_CONE = DEFAULT_MODEL_PATH + "cone";
const QString MODEL_QUAD = DEFAULT_MODEL_PATH + "quad";
const QString MODEL_TRIANGLE = DEFAULT_MODEL_PATH + "triangle";
const QString MODEL_CIRCLE = DEFAULT_MODEL_PATH + "circle";
const QString MODEL_PLANE = DEFAULT_MODEL_PATH + "plane";


#endif // RESOURCE_PATH_H