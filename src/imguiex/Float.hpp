#pragma once
#ifndef IMGUIEX_FLOAT_HPP
#define IMGUIEX_FLOAT_HPP
#include <string>
namespace imguiex {
/**
 * Float �́AImGui�̃��b�p�[�ł��B
 */
class Float {
       public:
        explicit Float(const std::string& label, float step);

        /**
         * GUI��`�悵�Ēl���X�V���܂��B
         */
        void draw();

        std::string label;
        float value;
        float step;
        float min;
        float max;

       private:
};
}  // namespace imguiex
#endif