#pragma once
#ifndef IO_PATH_HPP
#define IO_PATH_HPP
#include <string>
#include <vector>
namespace planet {

namespace Path {
/**
 * �p�X����g���q����菜���ĕԂ��܂��B
 * @param path
 * @return
 */
std::string withoutExtension(const std::string& path);

/**
 * �p�X����t�@�C���������o���ĕԂ��܂��B
 * @param path
 * @return
 */
std::string getFileNameFromPath(const std::string& path);

/**
 * �p�X����f�B���N�g���������o���ĕԂ��܂��B
 * @param path
 * @return
 */
std::string getDirectoryPathFromPath(const std::string& path);

/**
 * �p�X�̋�؂蕶�� / ���o�b�N�X���b�V���֕ϊ����ĕԂ��܂��B
 * @param path
 * @return
 */
std::string slashToEscape(const std::string path);

/**
 * �p�X�̋�؂蕶�� �o�b�N�X���b�V�� �� / �֕ϊ����ĕԂ��܂��B
 * @param path
 * @return
 */
std::string escapeToSlash(const std::string path);

/**
 * ��΃p�X full �� base ���猩�����΃p�X�֕ϊ����܂��B
 * @param ful
 * @param base
 * @return
 */
std::string relative(const std::string& full, const std::string& base);

/**
 * �p�X�̈ꗗ��S�Đڑ����ĕԂ��܂��B
 * @param components
 * @return
 */
std::string build(std::vector<std::string> components);

/**
 * �p�X�̈ꗗ��S�Đڑ����ĕԂ��܂��B
 * @param car
 * @param cdr
 * @return
 */
std::string build(std::string car, std::vector<std::string> cdr);

/**
 * �p�X�̐擪�ɃX���b�V����ǉ����ĕԂ��܂��B
 * @param path
 * @return
 */
std::string appendFirstSlash(const std::string& path);

/**
 * �p�X�̐擪����X���b�V������菜���ĕԂ��܂��B
 * @param path
 * @return
 */
std::string removeFirstSlash(const std::string& path);

/**
 * �p�X�̖����ɃX���b�V����ǉ����ĕԂ��܂��B
 * @param path
 * @return
 */
std::string appendLastSlash(const std::string& path);

/**
 * �p�X�̖����ɃX���b�V����ǉ����ĕԂ��܂��B
 * @param path
 * @return
 */
std::string removeLastSlash(const std::string& path);

/**
 * �w��̃p�X�����݂���Ȃ� true ��Ԃ��܂��B
 * @param path
 * @return
 */
bool isExists(const std::string& path);

/**
 * �w��̃p�X���f�B���N�g���Ȃ� true ��Ԃ��܂��B
 * @param path
 * @return
 */
bool isDirectory(const std::string& path);

/**
 * �w��̃p�X���f�B���N�g���Ȃ� false ��Ԃ��܂��B
 * @param path
 * @return
 */
bool isFile(const std::string& path);
}  // namespace Path
}  // namespace planet
#endif