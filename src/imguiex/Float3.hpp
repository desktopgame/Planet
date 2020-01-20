#pragma once
#ifndef IMGUIEX_FLOAT3_HPP
#define IMGUIEX_FLOAT3_HPP
#include <glm/glm.hpp>
#include <string>

namespace imguiex {
/**
 * Float3 �́AImGui�̃��b�p�[�ł��B
 */
class Float3 {
       public:
        explicit Float3(const std::string& label, float step);

        /**
         * GUI��`�悵�Ēl���X�V���܂��B
         */
        void draw();

        std::string label;
        glm::vec3 value;
        float step;
        float min;
        float max;
};
}  // namespace imguiex
#endif