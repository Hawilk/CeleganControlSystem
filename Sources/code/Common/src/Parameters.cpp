#include "Parameters.h"
#include "const_def.h"
#include <iostream>

Parameters* Parameters::getInstance()
{
	static Parameters param;
	return &param;
}

void Parameters::saveData()
{
	std::ofstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "can't open ini file" << std::endl;
		return;
	}
	
	for (const auto& entry : data)
	{
		file << entry.first << "=" << entry.second << "\n";
	}

	file.close();
}

void Parameters::loadData()
{
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "can't open ini file" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (line.empty() || line[0] == '#' || line[0] == ';') {
			continue;  // 跳过空行和注释
		}

		std::istringstream lineStream(line);
		std::string key, value;
		if (std::getline(lineStream, key, '=') && std::getline(lineStream, value)) {
			data[key] = value;  // 将键值对保存到 map 中
		}
	}

	file.close();
}

std::map<std::string, std::string> Parameters::getParam()
{
	if(data.empty())
		loadData();

	return this->data;
}

void Parameters::set(const std::string& key, const std::string& value)
{
	data[key] = value;
}

Parameters::Parameters()
{
	fileName = configName;
}
