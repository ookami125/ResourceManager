#pragma once
#include <unordered_map>
#include "Utils.h"

struct Skeleton
{
	struct Bone
	{

		float mat[16];
	};
	Bone* bones = nullptr;
	std::unordered_map<const char*, Bone*>* BoneMap;
//functions
	void init()
	{
		bones = nullptr;
		BoneMap = new std::unordered_map<const char*, Bone*>();
	}
};