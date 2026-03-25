#pragma once

#include <memory>

#include "../Mesh/Mesh.h"
#include "../Texture/Texture.h"
#include "../Shader/Shader.h"
#include "../Material/Material.h"

class Model : public Movable, public Rotatable, public Scalable {
private:
	const Material& material;
    const Texture& texture;
    std::unique_ptr<Mesh> mesh;

public:
	Model(
		const vec3& position,
		const Material& material,
        std::unique_ptr<Mesh> mesh,
	    const Texture& texture
	);

    Model(
		vec3 position,
		const Material& material,
		std::string objectFileName,
	    const Texture& texture
	);

    Model(Model&& other);

	~Model();
	
    vec3 getPosition() const override;
    void setPosition(const vec3& new_position) override;
    void move(const vec3& delta_position) override;
    
    vec3 getRotation() const override;
    void setRotation(const vec3& new_rotation) override;
    void rotate(const vec3& delta_rotation) override;
 
    vec3 getScale() const override;
    void setScale(const vec3& new_scale) override;
	void doScale(const vec3& delta_scale) override;

    void update();
	void render(const Shader& shader) const;
};

