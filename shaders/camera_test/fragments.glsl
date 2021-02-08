#version 330 core
in vec2 TexCoords;

out vec4 fragColor;

uniform sampler2D diffuse1;

void main() {
    fragColor = texture(diffuse1, TexCoords);
    // fragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}