#pragma once

#include <nlohmann/json.hpp>
#include <iostream>

class Output
{
private:
	static void print(std::string msg)
	{
		using namespace std;

		cout << msg << endl;
	}
public:
	static void log(std::string msg)
	{
		print("[LOG] " + msg);
	}

	static void error(std::string msg)
	{
		print("[ERROR] " + msg);
	}

	static void warn(std::string msg)
	{
		print("[WARN] " + msg);
	}

	static void info(std::string msg)
	{
		print("[INFO] " + msg);
	}
};