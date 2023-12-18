#include "SpriteObject3d.hlsli"

struct TransformationMatrix {
	float32_t4x4 WVP;
};
ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);

struct TransformationViewMatrix {
	float32_t4x4 view;
	float32_t4x4 viewProjection;
	float32_t4x4 orthoGraphic;
	float32_t3 cameraPosition;
};
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b1);


struct VertexShaderInput {
	float32_t4 position : POSITION0;
	float32_t2 texcoord : TEXCOORD0;
};

VertexShaderOutput main(VertexShaderInput input) {
	VertexShaderOutput output;
	float32_t4x4 resultMat;

	float32_t4x4 cameraMat = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.viewProjection);
	resultMat = mul(gTransformationMatrix.WVP, cameraMat);

	output.position = mul(input.position, resultMat);
	output.texcoord = input.texcoord;
	return output;
}