#pragma once
#ifndef IMGUIEX_INTEGER_HPP
#define IMGUIEX_INTEGER_HPP
#include <string>
namespace imguiex {
/**
 * Integer �́AImGui�̃��b�p�[�ł��B
 */
class Integer {
       public:
        explicit Integer(const std::string& label, int step);

        /**
         * GUI��`�悵�Ēl���X�V���܂��B
         */
        void draw();

        std::string label;
        int value;
        int step;
        int min;
        int max;

       private:
};
}  // namespace imguiex
#endif