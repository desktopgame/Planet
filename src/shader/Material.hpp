#pragma once
#ifndef SHADER_MATERIAL_HPP
#define SHADER_MATERIAL_HPP
#include <ofVec4f.h>
namespace planet {
/**
 * Material �́A�I�u�W�F�N�g�̍ގ����`���܂��B
 */
class Material {
       public:
        explicit Material();

        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;
        float shininess;
};
}  // namespace planet
#endif