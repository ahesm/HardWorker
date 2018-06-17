#ifndef _EXTRADATA_H_
#define _EXTRADATA_H_

#include <string>
#include <map>

class ExtraData
{
private:
	std::map<std::string, void *> _data;

public:
	void *GetData(const std::string &tag);

public:
	void PutData(bool &data, const std::string &tag);
	void PutData(int &data, const std::string &tag);
	void PutData(float &data, const std::string &tag);
	void PutData(double &data, const std::string &tag);
	void PutData(long &data, const std::string &tag);
};

#endif