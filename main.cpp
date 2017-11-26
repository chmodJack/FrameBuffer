#include<iostream>
#include"FrameBuffer.hpp"
using namespace std;

FrameBuffer* fb=new FrameBuffer("/dev/fb0");

int main(int argc,char *argv[])
{
	while(1)
	{
		fb->clear(0xff0000);
		usleep(500000);
		fb->clear(0x00ff00);
		usleep(500000);
		fb->clear(0xffffff);
		usleep(500000);
	}
	return 0;
}
