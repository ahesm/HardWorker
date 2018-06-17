#include "GlobalVar.h"

std::map<std::string, bool>  GlobalVar::_varBool;
std::map<std::string, int>   GlobalVar::_varInt;
std::map<std::string, float> GlobalVar::_varFloat;
std::map<std::string, long>  GlobalVar::_varLong;


bool GlobalVar::GetVariable_B(const std::string &tag)
{
	return _varBool[tag];
}

int GlobalVar::GetVariable_I(const std::string &tag)
{
	return _varBool[tag];
}

float GlobalVar::GetVariable_F(const std::string &tag)
{
	return _varBool[tag];
}

long GlobalVar::GetVariable_L(const std::string &tag)
{
	return _varBool[tag];
}

void GlobalVar::DefineVariable_B(bool iValue, const std::string &tag)
{
	bool value = iValue;
	_varBool.insert(std::make_pair(tag, value));
}

void GlobalVar::DefineVariable_I(int iValue, const std::string &tag)
{
	int value = iValue;
	_varInt.insert(std::make_pair(tag, value));
}

void GlobalVar::DefineVariable_F(float iValue, const std::string &tag)
{
	float value = iValue;
	_varFloat.insert(std::make_pair(tag, value));
}

void GlobalVar::DefineVariable_L(long iValue, const std::string &tag)
{
	long value = iValue;
	_varLong.insert(std::make_pair(tag, value));
}

void GlobalVar::AdjustVariable_B(bool value, const std::string &tag)
{
	_varBool[tag] = value;
}

void GlobalVar::AdjustVariable_I(int value, const std::string &tag)
{
	_varInt[tag] = value;
}

void GlobalVar::AdjustVariable_F(float value, const std::string &tag)
{
	_varFloat[tag] = value;
}

void GlobalVar::AdjustVariable_L(long value, const std::string &tag)
{
	_varLong[tag] = value;
}
