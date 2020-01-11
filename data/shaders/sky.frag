#version 410 core

#define skyColor vec3(0.474509804, 0.698039216, 0.952941176)
#define fogColor vec3(0.662745098, 0.776470588, 0.937254902)

in vec3 fPosition;
out vec4 FragColor;
uniform vec3 cameraPosition;

void main()
{
    float cameraY = clamp(0, 1, cameraPosition.y / 255);
    float planeCoord = fPosition.y * sqrt(3) + (1 + fPosition.z) * sign(fPosition.y);

    float fogHeight = -0.2;
    float magic = 2 * (0.5 - cameraY) + fogHeight;

    float pos = smoothstep(magic - 0.1, magic + 0.1, planeCoord);
    vec3 color = mix(fogColor, skyColor, pos);

    FragColor = vec4(color, 1.0);
}
