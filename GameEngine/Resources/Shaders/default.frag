#version 330 core
#ifdef GL_KHR_blend_equation_advanced
#extension GL_ARB_fragment_coord_conventions : enable
#extension GL_KHR_blend_equation_advanced : enable
#endif


in vec3 fragPosition;
in vec4 fragColor;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 color;


uniform sampler2D sampler; // Texture sampler

uniform mat3 mMaterial;
uniform mat3 mLightIntensity;


uniform float mColorFactor;
uniform float mTextureFactor;
uniform float mPhongFactor; // Shininess
uniform float mShininess; // Shininess
uniform vec3 mLightPosition; // Light position

void main()
{
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(mLightPosition - fragPosition);
    vec3 R = reflect(-L, N);      // Reflected light vector
    vec3 V = normalize(-fragPosition); // Vector to viewer

    vec3 lv = mLightPosition - fragPosition;
    float lvd = 1.0/(dot(lv, lv));
    float specAngle = max(dot(R, V), 0.0);
    float specular = pow(specAngle, mShininess);
    vec3 g = vec3(lvd*max(dot(L, N), 0.0), specular, 1.0);
    vec3 rgb = matrixCompMult(mMaterial, mLightIntensity) * g; // +  colorInterp;
    vec4 phongColor = vec4(rgb, 1.0);

    float totalFactor = mColorFactor + mPhongFactor + mTextureFactor;
    float mColorFactorNormalize = mColorFactor / totalFactor;
    float mPhongFactorNormalize = mPhongFactor / totalFactor;
    float mTextureFactorNormalize = mTextureFactor / totalFactor;
    color = mColorFactorNormalize*fragColor + mPhongFactorNormalize * phongColor + mTextureFactorNormalize*texture2D(sampler, fragTexCoord);


    if (color.a <= 0.01) {
        discard;
    }
}