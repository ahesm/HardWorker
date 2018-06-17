#ifndef _GLOBALVAR_H_
#define _GLOBALVAR_H_

#include <string>
#include <map>

class GlobalVar
{
private:
	static std::map<std::string, bool> _varBool;
	static std::map<std::string, int> _varInt;
	static std::map<std::string, float> _varFloat;
	static std::map<std::string, long> _varLong;

public:
	static bool GetVariable_B(const std::string &tag);
	static int GetVariable_I(const std::string &tag);
	static float GetVariable_F(const std::string &tag);
	static long GetVariable_L(const std::string &tag);

public:
	static void DefineVariable_B(bool iValue, const std::string &tag);
	static void DefineVariable_I(int iValue, const std::string &tag);
	static void DefineVariable_F(float iValue, const std::string &tag);
	static void DefineVariable_L(long iValue, const std::string &tag);

	static void AdjustVariable_B(bool value, const std::string &tag);
	static void AdjustVariable_I(int value, const std::string &tag);
	static void AdjustVariable_F(float value, const std::string &tag);
	static void AdjustVariable_L(long value, const std::string &tag);
};

#endif