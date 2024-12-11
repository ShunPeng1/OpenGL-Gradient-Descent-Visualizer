#version 330 core

layout(location = 0) in vec3 vertPosition;
layout(location = 1) in vec3 vertNormal;
layout(location = 2) in vec2 vertTexCoord;
layout(location = 3) in vec4 vertColor;

out vec3 fragPosition;
out vec4 fragColor;
out vec3 fragNormal;
out vec2 fragTexCoord;

uniform mat4 mWorld;
uniform mat4 mView;
uniform mat4 mProj;
uniform vec2 mTexScale;

void main()
{
    fragColor = vertColor;
    fragTexCoord = vertTexCoord * mTexScale;


    mat4 modelViewMatrix = mView * mWorld;
    vec4 modelViewPosition = modelViewMatrix * vec4(vertPosition, 1.0);
    fragPosition = vec3(modelViewPosition) / modelViewPosition.w;

    
    mat4 normal_matrix = transpose(inverse(modelViewMatrix));
    fragNormal = vec3(normal_matrix * vec4(vertNormal, 0.0));

    gl_Position = mProj * modelViewPosition;
}