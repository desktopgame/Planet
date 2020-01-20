#pragma once
#ifndef TEXT_ENCODING_HPP
#define TEXT_ENCODING_HPP
#include <string>
namespace planet {

namespace Encoding {
/**
 * ���C�h��������}���`�o�C�g������֕ϊ����܂��B
 * @param input
 * @return
 */
std::string toMultiByteString(const std::wstring& input);
/**
 * �}���`�o�C�g����������C�h������֕ϊ����܂��B
 * @param input
 * @return
 */
std::wstring toWideString(const std::string& input);
}  // namespace Encoding
}  // namespace planet
#endif