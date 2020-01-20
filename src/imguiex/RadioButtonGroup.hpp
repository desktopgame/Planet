#pragma once
#ifndef IMGUIEX_RADIOBUTTONGROUP_HPP
#define IMGUIEX_RADIOBUTTONGROUP_HPP
#include <vector>
#include <string>

namespace imguiex {
/**
 * RadioButtonGroup �́AImGui�̃��b�p�[�ł��B
 */
class RadioButtonGroup {
public:
	explicit RadioButtonGroup();

	/**
	 * GUI��`�悵�Ēl���X�V���܂��B
	 */
	void draw();

	std::vector<std::string> labels;
	int mode;
	bool sameLine;
private:
};
}
#endif