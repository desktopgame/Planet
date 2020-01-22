#pragma once
#ifndef CSVR_CSVR_HPP
#define CSVR_CSVR_HPP
#include <vector>
#include <string>

namespace csvr {
constexpr char separator = ',';
constexpr char newline = '\n';


using Line = std::vector<std::string>;
using Table = std::vector<Line>;
/**
 * csvr::Parser �� CSV �̓Ǝ��g���t�H�[�}�b�g���T�|�[�g����p�[�T�ł��B
 * ���̃p�[�T��CSV�ɂ���ĕ\�����񎟌��z��̔z���ێ����܂��B
 * �p�[�X���ɂ�, �ʏ��CSV���l ,(�J���}) ���J�����̋�؂蕶���Ƃ��Ďg�p���鑼�A
 * �Ȃɂ��Ȃ���s�� CSV�P�̏I�� �Ƃ݂Ȃ��܂��B
 */
class Parser {
public:
	explicit Parser();

	void parse(const std::string& source);

	Table& getTableAt(int index);
	const Table& getTableAt(int index) const;
	int getTableCount() const;

private:
	static int parse(int start, const std::string& source, Table& table);
	static bool isNullOrEmpty(const std::string& str);
	std::vector<Table> tables;
};
}
#endif