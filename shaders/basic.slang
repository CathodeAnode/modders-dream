struct VertexInput {
    float3 position : POSITION;
    float3 color : COLOR0;
}

struct VertexOutput {
    float4 position : SV_POSITION;
    float3 color : COLOR0;
}

[shader("vertex")]
VertexOutput vertexMain(VertexInput input) {
    VertexOutput output;
    output.position = float4(input.position, 1.0);
    output.color = input.color;
    return output;
}

[shader("fragment")]
float4 fragmentMain(VertexOutput input) {
    return float4(input.color, 1.0);
}

