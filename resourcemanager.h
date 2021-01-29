#ifndef RZ_RESOURCEMANAGER_H
#define RZ_RESOURCEMANAGER_H

#include <dirent.h>

#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "mesh.h"

class ResourceManager
{
	public:
		static ResourceManager* getInstance();
		static void deleteInstance();
		std::map<std::string, Mesh> data;

		ResourceManager();
		~ResourceManager();

		void loadData();

	private:
		static ResourceManager* instance;
		static constexpr float SCALE = 100.f;
};

#endif

