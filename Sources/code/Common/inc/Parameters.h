/*
 *@file     Parameters.h
 *@brief    参数读取保存
 *@author   yangshuhao
 *@date     2024/9/8
 *@remarks
 *@version  1.1
 */

#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <map>

class Parameters
{
public:
	Parameters(const Parameters& p) = delete;
	Parameters& operator= (const Parameters& p) = delete;

	//单例模式获取指针
	static Parameters* getInstance();

	//保存当前配置数据
	void saveData();

	//载入数据
	void loadData();

	//外部获取data
	std::map<std::string, std::string> getParam();

	//外部设置data
	void set(const std::string& key, const std::string& value);

private:
	Parameters();
	std::string fileName;
	std::map<std::string, std::string> data;
};
