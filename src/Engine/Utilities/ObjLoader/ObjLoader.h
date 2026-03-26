#pragma once

#include <string>
#include <vector>

struct Vertex;

class ObjectLoader
{
private:
	static std::string compile(std::string fileName);

public:
	static std::vector<Vertex> get(std::string fileName);
};

