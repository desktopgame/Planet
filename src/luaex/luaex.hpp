#pragma once
#ifndef LUAEX_LUA_HPP
#define LUAEX_LUA_HPP
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <functional>
#include "../any/any.hpp"

struct lua_State;

namespace luaex {
/**
 * Error ��LUA�̃G���[���ł��B
 */
using Error = enum {
	E_NIL = 0,
	E_TYPE_MISSING,
	E_SYNTAX,
	E_OOM,
	E_GC,
	E_GENERIC,
	E_FATAL,
};
/**
 * Type ��LUA�̃f�[�^�^�ł��B
 */
using Type = enum {
	T_NUMBER = 0,
	T_BOOL,
	T_STRING
};
/**
 * Variant ��LUA�̃f�[�^�ł��B
 */
struct Variant {
	double number;
	bool boolean;
	std::string string;
};
/**
 * Object �͌^�ƃf�[�^�̃y�A�ł��B
 */
struct Object {
	explicit Object();
	Type type;
	Variant value;
};
using Function = int(struct lua_State*);
/**
 * Interpreter ��LUA�̃��b�p�[�ł��B
 */
struct Interpreter {
public:
	explicit Interpreter();
	~Interpreter();
	/**
	 * �w��̃t�@�C�����X�N���v�g�Ƃ��ēǂݍ��݂܂��B
	 * @param file
	 * @return
	 */
	Error loadFile(const std::string& file);
	/**
	 * �w��̕�������X�N���v�g�Ƃ��ēǂݍ��݂܂��B
	 * @param str
	 * @return
	 */
	Error loadString(const std::string& str);

	/**
	 * �w��̊֐����Ăяo���܂��B
	 * @param function
	 * @param args
	 * @return Types
	 * @return returnOut
	 * @return
	 */
	Error call(const std::string& function, std::vector<Object> args, std::vector<Type> returnType, std::vector<Variant>& returnOut);

	/**
	 * �w��̖��O�Ŋ֐����`���܂��B
	 * @param name
	 * @param fn
	 */
	void define(const std::string& name, Function fn);

	/**
	 * �w��̖��O�ŃO���[�o���ϐ����`���܂��B
	 * @param name
	 * @param value
	 */
	void setGlobalNumber(const std::string& name, double value);

	/**
	 * �w��̖��O�ŃO���[�o���ϐ����`���܂��B
	 * @param name
	 * @param value
	 */
	void setGlobalInt(const std::string& name, int value);

	/**
	 * �w��̖��O�ŃO���[�o���ϐ����`���܂��B
	 * @param name
	 * @param value
	 */
	void setGlobalBool(const std::string& name, bool value);

	/**
	 * �w��̖��O�ŃO���[�o���ϐ����`���܂��B
	 * @param name
	 * @param value
	 */
	void setGlobalString(const std::string& name, const std::string& value);

	/**
	 * �w��̖��O�̃O���[�o���ϐ���Ԃ��܂��B
	 * @param name
	 * @param value
	 */
	Error getGlobalNumber(const std::string& name, double& outNumber);

	/**
	 * �w��̖��O�̃O���[�o���ϐ���Ԃ��܂��B
	 * @param name
	 * @param value
	 */
	Error getGlobalInt(const std::string& name, int& outInt);

	/**
	 * �w��̖��O�̃O���[�o���ϐ���Ԃ��܂��B
	 * @param name
	 * @param value
	 */
	Error getGlobalBool(const std::string& name, bool& outBool);

	/**
	 * �w��̖��O�̃O���[�o���ϐ���Ԃ��܂��B
	 * @param name
	 * @param value
	 */
	Error getGlobalString(const std::string& name, std::string& outStr);

	/**
	 * �S�Ă̕ϐ���Ԃ��܂��B
	 * @return
	 */
	std::unordered_map<std::string, Object> getAllVariables() const;

	/**
	 * �G���[���������Ă���Ȃ� true ��Ԃ��܂��B
	 * @return
	 */
	bool isOccurred() const;
	/**
	 * �Ō�ɔ��������G���[��Ԃ��܂��B
	 * @return
	 */
	std::string getLastError() const;
private:
	std::string getErrorString();
	Error checkStatus(int status, int ok);
	Error panic(Error error, const std::string& str);

	struct lua_State* state;
	bool occurred;
	std::string lastError;
};
/**
 * Context �́AC�̊֐�����C++�̕ϐ��ɃA�N�Z�X���邽�߂̃N���X�ł��B
 * Interpreter �̓����Ŏg�p����܂��B
 */
class Context : public std::enable_shared_from_this<Context> {
public:
	static std::shared_ptr<Context> create();
	static std::shared_ptr<Context> current();
	void dispose();

	void select();
	void put(const std::string& name, linb::any var);
	linb::any get(const std::string& name) const;
private:
	Context();
	bool selected;
	std::unordered_map<std::string, linb::any> map;
	static std::vector<std::shared_ptr<Context> > values;
};

Object create(int i);
Object create(double d);
Object create(bool b);
Object create(const std::string& str);
}
#endif