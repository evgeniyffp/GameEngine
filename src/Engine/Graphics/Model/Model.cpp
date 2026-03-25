#include "Model.h"

#include <Engine/Utilities/ObjLoader/ObjLoader.h>

Model::Model(
	const vec3& position,
	const Material& material,
    std::unique_ptr<Mesh> _mesh,
	const Texture& texture
) : material(material), texture(texture), mesh(std::move(_mesh))
{
    mesh->setPosition(position);
    mesh->setOrigin(position);
}

Model::Model(
	vec3 position,
	const Material& material,
	std::string objectFileName,
	const Texture& texture
) : Model(
		position, material,
		std::make_unique<Mesh>(ObjectLoader::get(objectFileName)), 
        texture
) {}

Model::Model(Model&& other)
        : material(std::move(other.material))
        , texture(std::move(other.texture))
        , mesh(std::move(other.mesh)) {}

Model::~Model() = default;

vec3 Model::getPosition() const {
    return mesh->getPosition();
}
void Model::setPosition(const vec3& new_position) {
    mesh->setPosition(new_position);
}
void Model::move(const vec3& delta_position) {
    mesh->move(delta_position);
}   
 
vec3 Model::getRotation() const {
    return mesh->getRotation();
}
void Model::setRotation(const vec3& new_rotation) {
    mesh->setRotation(new_rotation);
}
void Model::rotate(const vec3& delta_rotation) { 
    mesh->rotate(delta_rotation);
}

vec3 Model::getScale() const {
    return mesh->getScale();
}
void Model::setScale(const vec3& new_scale) {
    mesh->setScale(new_scale);
}
void Model::doScale(const vec3& delta_scale) {
    mesh->doScale(delta_scale);
}

void Model::update() {
    mesh->update();
}

void Model::render(const Shader& shader) const {
	shader.use();

	if (!texture.is_empty())
		texture.bind(0);
		
	mesh->render(shader);

	shader.unUse();
}

