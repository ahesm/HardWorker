#include "ExtraData.h"

void *ExtraData::GetData(const std::string &tag)
{
	return _data.find(tag)->second;
}

void ExtraData::PutData(bool &data, const std::string &tag)
{
	_data.insert(std::make_pair(tag, &data));
}

void ExtraData::PutData(int &data, const std::string &tag)
{
	_data.insert(std::make_pair(tag, &data));
}

void ExtraData::PutData(float &data, const std::string &tag)
{
	_data.insert(std::make_pair(tag, &data));
}

void ExtraData::PutData(double &data, const std::string &tag)
{
	_data.insert(std::make_pair(tag, &data));
}

void ExtraData::PutData(long &data, const std::string &tag)
{
	_data.insert(std::make_pair(tag, &data));
}