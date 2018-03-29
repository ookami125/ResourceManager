#pragma once
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Image
{
	int width, height, bpp;
	unsigned char* rgb = nullptr;
public:

	Image(const char* filename);
	Image(int width, int height);
	~Image();

	void SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	//void Save(const char * filename);

	inline int getWidth() { return width; };
	inline int getHeight() { return height; };
};

Image::Image(const char* filename)
{
	rgb = stbi_load(filename, &width, &height, &bpp, 3);
}

Image::Image(int width, int height) : width(width), height(height)
{
	rgb = (unsigned char*)malloc(width * height * 4);
	memset(rgb, 0, width * height * 4);
}

Image::~Image()
{
	stbi_image_free(rgb);
}

void Image::SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	int pos = x * 4 + y * width * 4;
	if (x >= width || x < 0 || y >= height || y < 0)
		return;
	rgb[pos + 0] = r;
	rgb[pos + 1] = g;
	rgb[pos + 2] = b;
	rgb[pos + 3] = a;
}