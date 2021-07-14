#pragma once
#include <vector>

class Canvas
{
public:
	Canvas()
	{
		framebuffer.resize(ScreenWidth*ScreenHeight*nchannel);
		std::fill(framebuffer.begin(), framebuffer.end(), 0);
	}

	void PutPixel(int x, int y, int r, int g, int b, float alpha= 255.0f)
	{
		int index = get_index(x, y);
		framebuffer[index*nchannel + 0] = (unsigned char)r;
		framebuffer[index*nchannel + 1] = (unsigned char)g;
		framebuffer[index*nchannel + 2] = (unsigned char)b;
		framebuffer[index*nchannel + 3] = (unsigned char)alpha;
	}
	void output(std::string savename)const;

public:
	//static constexpr int ScreenWidth = 200;
	//static constexpr int ScreenHeight = 100;
	static constexpr int ScreenWidth = 600;
	static constexpr int ScreenHeight = 600;
	static constexpr int nchannel = 4;
private:
	int get_index(int x, int y)
	{
		//return (ScreenHeight - y)*ScreenWidth + x;
		return y*ScreenWidth + x;
	}
	//std::vector<unsigned char> framebuffer(500, 0);
	//std::unique_ptr<unsigned char[]> framebuffer(new unsigned char[500]);
	std::vector<unsigned char> framebuffer;

};