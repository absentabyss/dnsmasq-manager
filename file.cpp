#include "file.h"

#include <fstream>
#include <iostream>

void overwriteFile(const std::string &fileName, const std::string &content)
{
	std::ofstream file;
	try
	{
		file.open(fileName);
		file << content << '\n';
	}
	catch(std::ofstream::failure&)
	{
		std::cerr << fileName << " ςꝋıloı nεꝋbзoε.\n";
	}
	return;
}
