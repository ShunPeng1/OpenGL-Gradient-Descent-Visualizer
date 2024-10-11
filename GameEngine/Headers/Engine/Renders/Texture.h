#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <QOpenGLExtraFunctions>

struct Texture : protected QOpenGLExtraFunctions {
    Texture() {
        initializeOpenGLFunctions();
    }

    unsigned int ID;
    std::string type;
};

#endif // TEXTURE_H