#pragma once
#ifndef IO_DIRECTORY_HPP
#define IO_DIRECTORY_HPP
#include <Windows.h>

#include <functional>
#include <string>
#include <vector>
namespace planet {

namespace Directory {
/**
 * �w��̃f�B���N�g���̃t�@�C���ꗗ��Ԃ��܂��B
 * @param path
 * @param recursive
 * @return
 */
std::vector<std::string> files(const std::string& path, bool recursive);

/**
 * �w��̃f�B���N�g���̃T�u�f�B���N�g���ꗗ��Ԃ��܂��B
 * @param path
 * @param recursive
 * @return
 */
std::vector<std::string> directories(const std::string& path, bool recursive);

/**
 * �w��̃f�B���N�g���̃t�@�C��, �T�u�f�B���N�g���ꗗ��Ԃ��܂��B
 * @param path
 * @param recursive
 * @return
 */
std::vector<std::string> entries(const std::string& path, bool recursive);

/**
 * �w��̃f�B���N�g�����쐬���܂��B
 * @param dir
 */
void create(const std::string& dir);

namespace hidden {
std::vector<std::string> entries(
    const std::string& path, bool recursive,
    std::function<bool(std::string, DWORD)> filter);
}
}  // namespace Directory
}  // namespace planet
#endif