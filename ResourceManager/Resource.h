#pragma once

template<typename T>
class Resource
{
	bool persistant = false;
	T* data = nullptr;
public:
	Resource(T* data) : data(data), persistant(false) {};
	Resource(T* data, bool persistant) : data(data), persistant(persistant) {};

	//operator Resource<void>() const { return (Resource<void>*)this; };
	//operator Resource<T>() const { return (Resource<T>*)this; };

	T* GetData(){
		return data;
	}
};