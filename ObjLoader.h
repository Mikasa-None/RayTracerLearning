#pragma once
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "utils.h"
bool ObjLoad(std::string filename, std::vector<vec3>& vertexs, std::vector<std::vector<int>>& faces)
{
	std::string line;
	std::ifstream in(filename, std::ifstream::in);// pay attention to   /    //
	if (in.fail())
	{
		std::cout << "load objfile fail\n";
		return false;
	}
	//std::vector<vec3> vertexs;
	//std::vector<std::vector<int>> faces;
	while (!in.eof())
	{
		std::getline(in, line);
		std::istringstream iss(line);


		std::string trash;;
		if (!line.compare(0, 2, "v "))
		{
			iss >> trash;
			vec3 tt;
			for (int i = 0; i < 3; ++i)
			{
				iss >> tt[i];
			}
			vertexs.emplace_back(tt);
		}
		if (!line.compare(0, 2, "f "))
		{
			iss >> trash;
			std::vector<int> f;
			int tmp;
			for (int i = 0; i < 3; ++i)
			{
				iss >> tmp;
				f.push_back(tmp-1);
			}
			faces.push_back(f);

		}
	}
	return true;
}