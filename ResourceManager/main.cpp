#include <vector>
//#define TRUSTING_RESOURCEMANAGER
#include "ResourceManager.h"
#include "Image.h"
#include "Model.h"
#include "Utils.h"
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

#define BUFFER_SIZE 8
int main(int argc, char** argv)
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 0xFF, BUFFER_SIZE -1);
	buffer[BUFFER_SIZE-1] = '\0';
	double max = FLT_MIN;
	double min = FLT_MAX;
	long long average = 0;
	for (int i = 0; i < 100000; ++i)
	{
		auto start = PerformanceCounter();
		volatile auto temp = Utils::hash(buffer);
		auto end = PerformanceCounter();
		double elapsed = (double)(end - start) / PerformanceFrequency();
		max = std::max(elapsed, max);
		min = std::min(elapsed, min);
		average += (end - start);
	}
	printf("max time: %lf\n", max);
	printf("min time: %lf\n", min);
	printf("avg time: %lf\n", average / (PerformanceFrequency() * 100000.0));
	printf("avg ticks: %lld\n", average / 100000);
	printf("total ticks: %lld\n", average);

	//AddResourcesToRM();
	//GetResourcesToRM();
	system("PAUSE");
}