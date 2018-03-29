#pragma once
#include <unordered_map>
#include <string>
#include "Resource.h"

class ResourceManager
{
	std::unordered_map<std::string, Resource<void>*> Resources;

public:
	template<typename T>
	Resource<T>* GetResource(std::string ResourceID);

	template<typename T>
	void AddResource(std::string ResourceID, Resource<T>* resource);
	void RemoveResource(std::string ResourceID);

	void PrintAllKeys()
	{
		for (auto kp : Resources)
			printf("%s\n", kp.first.c_str());
	}
};

template<typename T>
inline Resource<T>* ResourceManager::GetResource(std::string ResourceID)
{
#ifndef TRUSTING_RESOURCEMANAGER
	if (Resources.find(ResourceID) == Resources.end())
		throw new std::invalid_argument("GetResource called on a non existent ResourceID (" + ResourceID + ")");
#endif
	return (Resource<T>*)(Resources[ResourceID]);
};

template<typename T>
inline void ResourceManager::AddResource(std::string ResourceID, Resource<T>* _Resource)
{
#ifndef TRUSTING_RESOURCEMANAGER
	if (Resources.find(ResourceID) != Resources.end())
		throw new std::invalid_argument("Can not add two Resources with the same ID ( "+ResourceID+" )");
#endif
	Resources[ResourceID] = (Resource<void>*)(_Resource);
};

inline void ResourceManager::RemoveResource(std::string ResourceID)
{
#ifndef TRUSTING_RESOURCEMANAGER
	if (Resources.find(ResourceID) == Resources.end())
		throw new std::invalid_argument("RemoveResource called on a non existent ResourceID (" + ResourceID + ")");
#endif
	Resources.erase(ResourceID);
}