/*
 *@file     Parameters.h
 *@brief    ������ȡ����
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

	//����ģʽ��ȡָ��
	static Parameters* getInstance();

	//���浱ǰ��������
	void saveData();

	//��������
	void loadData();

	//�ⲿ��ȡdata
	std::map<std::string, std::string> getParam();

	//�ⲿ����data
	void set(const std::string& key, const std::string& value);

private:
	Parameters();
	std::string fileName;
	std::map<std::string, std::string> data;
};
