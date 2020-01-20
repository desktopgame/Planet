#pragma once
#ifndef TEXT_STRINGS_HPP
#define TEXT_STRINGS_HPP
#include <string>
#include <vector>
namespace planet {

namespace Strings {
/**
 * �������C�ӂ̕����ŕ������܂��B
 * @param input
 * @param c
 * @return
 */
std::vector<std::string> split(const std::string& input, const char c);

/**
 * ���̃X�y�[�X���폜���܂��B
 * @param input
 * @return
 */
std::string lstrip(const std::string& input);

/**
 * �E�̃X�y�[�X���폜���܂��B
 * @param input
 * @return
 */
std::string rstrip(const std::string& input);

/**
 * �C�ӂ̕������܂܂��Ȃ� true ��Ԃ��܂��B
 * @param input
 * @param c
 * @return
 */
bool include(const std::string& input, const char c);

/**
 * �����񒆂̕�����u�������܂��B
 * @param input
 * @param oldc
 * @param newc
 * @return
 */
std::string replace(const std::string& input, char oldc, char newc);

/**
 * �����񒆂̕������u�������܂��B
 * @param input
 * @param from
 * @param to
 * @return
 */
std::string replace(const std::string target, const std::string from,
                    const std::string to);

/**
 * �w��̃v���t�B�b�N�X�����Ȃ� true ��Ԃ��܂��B
 * @param input
 * @param prefix
 */
bool hasPrefix(const std::string& input, const std::string& prefix);

/**
 * �w��̃T�t�B�b�N�X�����Ȃ� true ��Ԃ��܂��B
 * @param input
 * @param suffix
 */
bool hasSuffix(const std::string& input, const std::string& suffix);

/**
 * �v���t�B�b�N�X��t�������܂��B
 * @param input
 * @param pefix
 * @return
 */
std::string fixprefix(const std::string& input, const std::string& prefix);

/**
 * �T�t�B�b�N�X��t�������܂��B
 * @param input
 * @param suffix
 */
std::string fixsuffix(const std::string& input, const std::string& suffix);
}  // namespace Strings
}  // namespace planet
#endif