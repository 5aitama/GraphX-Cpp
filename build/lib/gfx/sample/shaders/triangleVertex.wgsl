struct VertexInput {
    [[location(0)]] position: vec3<f32>;
    [[location(1)]] color: vec3<f32>;
};

struct VertexOutput {
    [[builtin(position)]] clip_position: vec4<f32>;
    [[location(0)]] color: vec3<f32>;
};

struct MVP {
    model: mat4x4<f32>;
    view: mat4x4<f32>;
    proj: mat4x4<f32>;
};

struct UniformData {
    pos: vec2<f32>;
};

[[group(0), binding(0)]]
var<uniform> uniformData: UniformData;

[[group(1), binding(0)]]
var<uniform> mvpData: MVP;

[[stage(vertex)]]
fn vs_main(
    model: VertexInput,
) -> VertexOutput {
    var out: VertexOutput;
    out.color = model.color;
    out.clip_position = mvpData.proj * mvpData.view * mvpData.model * vec4<f32>(model.position, 1.0); // vec4<f32>(model.position + vec3<f32>(uniformData.pos, 0.0), 1.0);
    return out;
}

[[stage(fragment)]]
fn fs_main(in: VertexOutput) -> [[location(0)]] vec4<f32> {
    return vec4<f32>(in.color, 1.0);
}
