#version 440

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    sampler2D diffuseTex;
    sampler2D specularTex;

    vec3 color;

    bool useTexture;
};

struct Light {
    float intensity;

    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
};

struct Camera {
    vec3 position;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;

#define MAX_LIGHTS 32

uniform struct {
    uint count;
    Light array[MAX_LIGHTS];
} u_lights;

uniform Camera u_camera;

vec3 diffuseLight(Material material, Light light) {
    vec3 posToLightDirVec = normalize(light.position - vs_position);
    float diffuse = max(dot(posToLightDirVec, normalize(vs_normal)), 0.0);
    vec3 diffuseFinal = material.diffuse * diffuse;
    return diffuseFinal;
}

vec3 specularLight(Material material, Light light) {
    vec3 lightToPosDirVec = normalize(vs_position - light.position);
    vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
    vec3 posToViewDirVec = normalize(u_camera.position - vs_position);
    float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0.0), 32);
    vec3 specularFinal = material.specular * specularConstant;
    
    if (material.useTexture) {
        specularFinal *= texture(material.specularTex, vs_texcoord).rgb;
    }
    
    return specularFinal;
}

float attenuation(Light light) {
    float distance = length(light.position - vs_position);
    float attenuationFinal = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    return attenuationFinal;
}

vec3 calculateLight(Material material, Light light) {
    vec3 ambient = material.ambient;
    vec3 diffuse  = diffuseLight(material, light);
    vec3 specular = specularLight(material, light);
    
    return attenuation(light) * light.intensity * light.color * (ambient + diffuse + specular);
}

void main() {
    vec3 lightFinal = vec3(0.0, 0.0, 0.0);

    for (uint i = 0; i < u_lights.count; ++i)
        lightFinal += calculateLight(material, u_lights.array[i]);

    vec3 colorPixel = lightFinal * material.color;
   
    if (material.useTexture)
        colorPixel = texture(material.diffuseTex, vs_texcoord).rgb;
    
    fs_color = vec4(colorPixel, 1.0);
}

