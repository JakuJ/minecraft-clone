#version 410 core

in vec3 fPosition;
out vec4 FragColor;

// Common uniforms
uniform float time;

uniform vec3 cameraPosition;

const vec3 fogColor = vec3(0.662745098, 0.776470588, 0.937254902);
const vec3 skyColor = vec3(0.474509804, 0.698039216, 0.952941176);

void main()
{
    float cameraY = clamp(0, 1, cameraPosition.y / 255);
    float planeCoord = fPosition.y * sqrt(3) + (1 + fPosition.z) * sign(fPosition.y);

    float magic = 2 * (0.5 - cameraY) + 0.2;// + fogHeight (-1 .. 1)

    float pos = smoothstep(magic - 0.1, magic + 0.5, planeCoord);
    vec3 color = mix(fogColor, skyColor, pos);

    color *= 0.5 * (1 +  sin(time));

    FragColor = vec4(color, 1.0);
}
