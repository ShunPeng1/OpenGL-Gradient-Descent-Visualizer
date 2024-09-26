#version 330 core

layout(location = 0) in vec3 vertPosition;
layout(location = 1) in vec3 vertNormal;
layout(location = 2) in vec2 vertTexCoord;
layout(location = 3) in vec4 vertColor;

out vec4 fragColor;
out vec3 fragNormal;
out vec2 fragTexCoord;

uniform mat4 mWorld;
uniform mat4 mView;
uniform mat4 mProj;
uniform vec2 mTexScale;
uniform bool mUseTexture;

void main()
{
    fragColor = vertColor;
    fragTexCoord = vertTexCoord * mTexScale;
    fragNormal = vertNormal;
    gl_Position = mProj * mView * mWorld * vec4(vertPosition, 1.0);
}