#pragma once


enum class PolygonMode {
    FILL = 0x1B02,
    LINE = 0x1B01,
    POINT = 0x1B00
};

enum class DrawBufferMode {
    NONE = 0,
    FRONT_LEFT = 0x0400,
    FRONT_RIGHT = 0x0401,
    BACK_LEFT = 0x0402,
    BACK_RIGHT = 0x0403,
    FRONT = 0x0404,
    BACK = 0x0405,
    LEFT = 0x0406,
    RIGHT = 0x0407,
    FRONT_AND_BACK = 0x0408,
    AUX0 = 0x0409,
    AUX1 = 0x040A,
    AUX2 = 0x040B,
    AUX3 = 0x040C
};