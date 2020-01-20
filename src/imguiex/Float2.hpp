#pragma once
#ifndef IMGUIEX_FLOAT2_HPP
#define IMGUIEX_FLOAT2_HPP
#include <glm/glm.hpp>
#include <string>

namespace imguiex {
/**
 * Float2 �́AImGui�̃��b�p�[�ł��B
 */
class Float2 {
       public:
        explicit Float2(const std::string& label, float step);

        /**
         * GUI��`�悵�Ēl���X�V���܂��B
         */
        void draw();

        std::string label;
        glm::vec2 value;
        float step;
        float min;
        float max;

       private:
};
}  // namespace imguiex
#endif