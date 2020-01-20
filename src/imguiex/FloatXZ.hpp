#pragma once
#ifndef IMGUIEX_FLOATXZ_HPP
#define IMGUIEX_FLOATXZ_HPP
#include <string>
#include <glm/glm.hpp>

namespace imguiex {
/**
 * FloatXZ �́AImGui�̃��b�p�[�ł���AXZ����������悤�ɂȂ��Ă��܂��B
 */
class FloatXZ {
public:
	explicit FloatXZ(const std::string& label, float step);

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
}
#endif