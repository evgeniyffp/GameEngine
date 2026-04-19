#include "./RenderSystem.h"

#include <Engine/ECS/Components/TransformComponent.h>
#include <Engine/ECS/Components/MeshComponent.h>
#include <Engine/ECS/Components/MaterialComponent.h>

glm::mat4 calculateModelMatrix(TransformComponent transform_component) {
    using namespace glm;

    vec3 position = transform_component.position_component.position;
    vec3 rotation = transform_component.rotation_component.rotation;
    vec3 scale = transform_component.scale_component.scale;
    vec3 origin = transform_component.origin;

    mat4 modelMatrix(1.f);

	modelMatrix = translate(modelMatrix, origin);
	modelMatrix = rotate(modelMatrix, radians(rotation.x), vec3(1.f, 0.f, 0.f));
	modelMatrix = rotate(modelMatrix, radians(rotation.y), vec3(0.f, 1.f, 0.f));
	modelMatrix = rotate(modelMatrix, radians(rotation.z), vec3(0.f, 0.f, 1.f));
	modelMatrix = translate(modelMatrix, position - origin);
	modelMatrix = glm::scale(modelMatrix, scale);

    return modelMatrix;
}

void RenderSystem::update(const entt::registry& registry, const Shader& shader) {
    auto view = registry.view<TransformComponent, MeshComponent, MaterialComponent>();

    for (const auto& entity : view) {
        const auto& transform = view.get<TransformComponent>(entity);
        const auto& mesh = view.get<MeshComponent>(entity).mesh;
        const auto& material = view.get<MaterialComponent>(entity).material;
        
        material.bind();

        {
            ShaderUser _su(shader);

            shader.setUniform(material, "material");
            shader.setUniform(calculateModelMatrix(transform), "modelMatrix");
        }
       
        mesh.render(shader);
    }
}

