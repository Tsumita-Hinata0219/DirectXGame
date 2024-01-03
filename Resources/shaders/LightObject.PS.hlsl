#include "LightObject.hlsli"

struct Material {
    float32_t4 color;
    int32_t enableLighting;
};
ConstantBuffer<Material> gMaterial : register(b0);

struct DirectionalLight{
    float32_t4 color;
    float32_t3 direction;
    float intensity;
};
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);


Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct PixcelShaderOutput {
    float32_t4 color : SV_TARGET0;
};


PixcelShaderOutput main(VertexShaderOutput input){
    PixcelShaderOutput output;
    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    
    if (gMaterial.enableLighting != 0) {
        
        float NdotL = dot(normalize(input.normal), -gDirectionalLight.direction);
        float cos = pow(NdotL*0.5f+0.5f,2.0f);
        
        if (textureColor.a == 0.0f) {
             discard;
         }

        output.color.rgb = gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * cos * gDirectionalLight.intensity;
        output.color.a = gMaterial.color.a * textureColor.a;
    }
    else {
         
         if (textureColor.a == 0.0f) {
             discard;
         }
         
         output.color = gMaterial.color * textureColor;
    }

    return output;
}