#pragma once
#ifndef IMGUIEX_CHECKBOX_HPP
#define IMGUIEX_CHECKBOX_HPP
#include <string>

namespace imguiex {
/**
 * CheckBox �́AImGui�̃��b�p�[�ł��B
 */
class CheckBox {
public:
	explicit CheckBox(const std::string& label);

	/**
	 * GUI��`�悵�āA�l���X�V���܂��B
	 */
	void draw();

	std::string label;
	bool enabled;
private:
};
}
#endif