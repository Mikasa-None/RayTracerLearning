#include "Canvas.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void Canvas::output(std::string savename)const
{
	stbi_write_png(savename.c_str(), ScreenWidth, ScreenHeight, nchannel, framebuffer.data(), ScreenWidth * 4);
}