#pragma once
#ifndef IMGUIEX_LISTBOX_HPP
#define IMGUIEX_LISTBOX_HPP
#include <string>
#include <vector>

namespace imguiex {
/**
 * ListBox �́AImGui�̃��b�p�[�ł��B
 */
class ListBox {
       public:
        explicit ListBox(const std::string& label);

        /**
         * GUI��`�悵�Ēl���X�V���܂��B
         */
        void draw();

        /**
         * ���݂� items �̒l���當����𐶐����܂��B
         * items ��ύX�������Ƃ͕K���Ăяo���Ă��������B
         */
        void rehash();

        std::vector<std::string> items;
        int selectedIndex;
        std::string label;

       private:
        std::vector<char*> raw;
};
}  // namespace imguiex
#endif