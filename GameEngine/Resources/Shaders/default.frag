#version 330 core
#ifdef GL_KHR_blend_equation_advanced
#extension GL_ARB_fragment_coord_conventions : enable
#extension GL_KHR_blend_equation_advanced : enable
#endif

in vec4 fragColor;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform sampler2D sampler; // Texture sampler
uniform vec2 mTexScale;
uniform bool mUseTexture;
uniform bool mUseColor;
out vec4 color;

void main()
{
    color = vec4(1.0, 1.0, 1.0, 1.0);

    if (mUseTexture) {
        vec4 texColor = texture(sampler, fragTexCoord);
        color = color * texColor;
    }

    if (mUseColor) {
        color = color * fragColor;
    }

    if (color.a <= 0.01) {
        discard;
    }
}