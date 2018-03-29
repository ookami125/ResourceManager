#include <vector>
//#define TRUSTING_RESOURCEMANAGER
#include "ResourceManager.h"
#include "Image.h"
#include "Model.h"
#include <Windows.h>

ResourceManager rm;

#define resourceCount 100000
void AddResourcesToRM()
{
	Image* img = new Image("resources/textures/bricks.jpg");
	Resource<Image>* img_res = new Resource<Image>(img);
	rm.AddResource("tex.bricks", img_res);

	Model* model = new Model("resources/models/test/Looking Around.dae");
	Resource<Model>* model_res = new Resource<Model>(model);
	rm.AddResource("model.player", model_res);
}

inline long long PerformanceCounter() noexcept
{
	LARGE_INTEGER li;
	::QueryPerformanceCounter(&li);
	return li.QuadPart;
}

inline long long PerformanceFrequency() noexcept
{
	LARGE_INTEGER li;
	::QueryPerformanceFrequency(&li);
	return li.QuadPart;
}

#define iters 100000
void GetResourcesToRM()
{
	long long start = PerformanceCounter();
	for (int i = 0; i < iters; ++i)
	{
		Resource<Image>* vecIntResource = rm.GetResource<Image>("tex.bricks");
		volatile auto temp = vecIntResource->GetData();
	}
	long long finish = PerformanceCounter();
	long long elapsed = (finish - start);
	double elapsedSeconds = ((double)(finish - start)) / PerformanceFrequency();
	printf("Elapsed Time: %lf s\n", elapsedSeconds);
	printf("Elapsed Time Per Resource: %lf s\n", elapsedSeconds / iters);
}

int main(int argc, char** argv)
{
	AddResourcesToRM();
	//GetResourcesToRM();
	system("PAUSE");
}