#pragma once

#include "./Shader.h"

class ShaderUser {
private:
    const Shader& shader;

public:
    ShaderUser(const Shader& shader) : shader(shader) {
        shader.use();
    }

    ~ShaderUser() {
        shader.unUse();
    }
};

