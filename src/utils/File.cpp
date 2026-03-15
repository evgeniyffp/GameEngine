#include "./File.h"

#include <exception>
#include <fstream>

#include <utils/displayInfo.h>

std::string readFile(std::string fileName) {
	std::ifstream in_file;

	std::string file;
	std::string temp;

	in_file.open(fileName);
    
    std::string info = "File.h => readFile() => file \"" + fileName + "\" open";
	displayInfo(info);
	
    if (!in_file.is_open())
		throw info;
	
    while (std::getline(in_file, temp))
		file += temp + "\n";
	
    in_file.close();

	return file;
}

