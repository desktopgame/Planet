#pragma once
#ifndef TEXT_STRINGS_HPP
#define TEXT_STRINGS_HPP
#include <string>
#include <vector>
namespace planet {

namespace Strings {
std::vector<std::string> split(const std::string& input, const char c);

std::string lstrip(const std::string& input);

std::string rstrip(const std::string& input);

bool include(const std::string& input, const char c);

std::string replace(const std::string& input, char oldc, char newc);

std::string replace(const std::string target, const std::string from,
                    const std::string to);

bool hasPrefix(const std::string& input, const std::string& prefix);

bool hasSuffix(const std::string& input, const std::string& suffix);

std::string fixprefix(const std::string& input, const std::string& prefix);

std::string fixsuffix(const std::string& input, const std::string& suffix);
}  // namespace Strings
}  // namespace planet
#endif