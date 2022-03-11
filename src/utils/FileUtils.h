#pragma once

#include <iostream>
#include <fstream>
#include <string>

#define ERRSTRING "-1-Err"

class FileUtils
{
public:
	static std::string readFile(std::string path)
	{
		using namespace std;

		string res;
		string line;
		ifstream file(path);

		if (file.is_open() && file.good())
		{
			while (getline(file, line)) 
			{
				res += line;
			}
			file.close();
			return res;
		}
		else return ERRSTRING;
	}
};