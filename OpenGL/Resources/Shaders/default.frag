#version 330 core

precision mediump float;

in vec4 fragColor;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform sampler2D sampler; // Texture sampler
uniform vec2 mTexScale;
uniform bool mUseTexture;
out vec4 color;

void main()
{
    vec4 fragColorOut = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 texColor = texture(sampler, fragTexCoord);

    if (!mUseTexture) {
        if (texColor.a * fragColor.a <= 0.01) {
            discard;
        }

        fragColorOut = fragColor;
    }
    else{
        fragColorOut = vec4(1.0, 1.0, 1.0, 1.0);
    }
    color = fragColorOut * texColor;
}