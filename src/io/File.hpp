#pragma once
#ifndef IO_FILE_HPP
#define IO_FILE_HPP
#include <string>
namespace planet {

namespace File {
/**
 * �w��̃p�X�̃e�L�X�g��S�ēǂݍ���ŕԂ��܂��B
 * @param path
 * @return
 */
std::string readAllText(const std::string& path);

/**
 * �w��̃t�@�C���Ƀe�L�X�g��S�ď������݂܂��B
 * @param path
 * @param str
 */
void writeAllText(const std::string& path, const std::string& str);

/**
 * �w��̃p�X�̃t�@�C�����폜���܂��B
 * @param path
 */
void remove(const std::string& path);

/**
 * from����to�փt�@�C���𕡐����܂��B
 * @param from
 * @param to
 */
void copy(const std::string& from, const std::string& to);
}  // namespace File
}  // namespace planet
#endif