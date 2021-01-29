#include <iostream>

#include "resourcemanager.h"

ResourceManager::ResourceManager()
{
	loadData();
}

ResourceManager::~ResourceManager()
{
	for (std::map<std::string, Mesh>::iterator it = data.begin(); it != data.end(); ++it) {
		delete data[it->first].colors;
		delete data[it->first].vertices;
	}
}

ResourceManager* ResourceManager::instance = NULL;

ResourceManager* ResourceManager::getInstance()
{
	if (!instance)
	{
		instance = new ResourceManager();
	}
	return instance;
}

void ResourceManager::deleteInstance()
{
	delete instance;
	instance = nullptr;
}

void ResourceManager::loadData()
{
	const std::string path = "data/gfx/";

	// NOTE: POSIX only

	DIR *dir;
	struct dirent *ent;

	dir = opendir(path.c_str());
	while ((ent = readdir(dir)) != NULL)
	{
		const std::string filename = ent->d_name;

		if (filename == "." || filename == "..") {
			continue;
		}

		const std::string name = filename.substr(0, filename.rfind('.'));

		std::ifstream file((path + filename).c_str());

		// count num lines
		int numlines = std::count(std::istreambuf_iterator<char>(file),
				std::istreambuf_iterator<char>(), '\n');
		file.clear();
		file.seekg(0);

		data[name].alpha = GLfloat(1);
		if (name == "explosion-0") {
			data[name].alpha = GLfloat(1);
		}
		if (name == "explosion-1") {
			data[name].alpha = GLfloat(0.1);
		}

		// resize array
		data[name].size = numlines * 3;
		data[name].colors = new Color[numlines * 3];
		data[name].vertices = new Vertex[numlines * 3];


		int j = 0;
		int i, ii = 0;
		std::string line;
		while (std::getline(file, line))
		{
			i = 0;
			float arr[18];
			std::stringstream ssin(line);
			while (ssin.good() && i < 18)
			{
				ssin >> arr[i];
				++i;
			}
			for (i = 0; i < 9; i += 3)
			{
				data[name].vertices[ii].x = arr[i + 0];
				data[name].vertices[ii].y = arr[i + 1];
				data[name].vertices[ii].z = arr[i + 2];
				++ii;
			}
			for (i = 9; i < 18; i += 3)
			{
				data[name].colors[j].r = arr[i + 0];
				data[name].colors[j].g = arr[i + 1];
				data[name].colors[j].b = arr[i + 2];
				data[name].colors[j].a = data[name].alpha;
				++j;
			}
		}
	}
	closedir(dir);
}

