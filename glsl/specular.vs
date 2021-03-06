#version 330
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) uniform mat4 camera;
layout(location = 1) uniform mat4 model;

in vec3 Position;
in vec3 Color;
in vec3 Normal;

out vec3 fragPosition;
out vec3 fragNormal;
out vec4 fragColor;

void main()
{
    fragPosition = vec3(model * vec4(Position, 1));
    fragNormal = normalize(transpose(inverse(mat3(model))) * Normal);
    fragColor = vec4(Color,1);

    gl_Position = camera * vec4(fragPosition, 1);
}
