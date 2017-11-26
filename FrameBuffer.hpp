#ifndef __FRAMEBUFFER_HPP__
#define __FRAMEBUFFER_HPP__

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<linux/fb.h>
#include<sys/mman.h>
#include<sys/ioctl.h>

#include"Point.hpp"
#include"Line.hpp"
class FrameBuffer
{
public:
	explicit FrameBuffer(const char* dev="/dev/fb0"):m_dev(dev)
	{
		if(0>(fb_fd=open(m_dev,O_RDWR)))
		{
			printf("Error : Can not open framebuffer device\n");
			exit(1);
		}

		if(ioctl(fb_fd,FBIOGET_FSCREENINFO,&finfo))
		{
			printf("Error reading fixed information\n");
			exit(2);
		}

		if (ioctl(fb_fd,FBIOGET_VSCREENINFO,&vinfo))
		{
			printf("Error reading variable information\n");
			exit(3);
		}

		buffersize=vinfo.xres*vinfo.yres*vinfo.bits_per_pixel/8;

		mmap_start=(unsigned char*)mmap(0,buffersize,PROT_READ|PROT_WRITE,MAP_SHARED,fb_fd,0);
		if((long)mmap_start==-1)
		{
			perror("mmap error!\n");
			exit(EXIT_FAILURE);
		}

		m_row=vinfo.yres;
		m_col=vinfo.xres;
	}
	~FrameBuffer(void)
	{
		if(-1==munmap(mmap_start,buffersize))
		{
			printf("munmap error!\n");
		}
		close(fb_fd);
	}
	const FrameBuffer& showInfo(void)const
	{
		printf("the fixed information is as follow:\n");
		printf("id=%s\n",finfo.id);  
		printf("sem_start=%lx\n",finfo.smem_start);  
		printf("smem_len=%u\n",finfo.smem_len);  
		printf("type=%u\n",finfo.type);  
		printf("line_length=%u\n",finfo.line_length);  
		printf("mmio_start=%lu\n",finfo.mmio_start);  
		printf("mmio_len=%d\n",finfo.mmio_len);  

		printf("variable information is as follow:\n");  
		printf("The xres is :%u\n",vinfo.xres);  
		printf("The yres is :%u\n",vinfo.yres);  
		printf("xres_virtual=%u\n",vinfo.xres_virtual);  
		printf("yres_virtual=%u\n",vinfo.yres_virtual);  
		printf("xoffset=%u\n",vinfo.xoffset);  
		printf("yoffset=%u\n",vinfo.yoffset);  
		printf("bits_per_pixel is :%u\n",vinfo.bits_per_pixel);  
		printf("red.offset=%u\n",vinfo.red.offset);  
		printf("red.length=%u\n",vinfo.red.length);  
		printf("red.msb_right=%u\n",vinfo.red.msb_right);  
		printf("green.offset=%d\n",vinfo.green.offset);  
		printf("green.length=%d\n",vinfo.green.length);  
		printf("green.msb_right=%d\n",vinfo.green.msb_right);  
		printf("blue.offset=%d\n",vinfo.blue.offset);  
		printf("blue.length=%d\n",vinfo.blue.length);  
		printf("blue.msb_right=%d\n",vinfo.blue.msb_right);  
		printf("transp.offset=%d\n",vinfo.transp.offset);  
		printf("transp.length=%d\n",vinfo.transp.length);  
		printf("transp.msb_right=%d\n",vinfo.transp.msb_right);  
		printf("height=%x\n",vinfo.height);  
		printf("width=%x\n",vinfo.width);
		return *this;
	}
	unsigned char* getAddr(void)const
	{
		return mmap_start;
	}
public:
	const FrameBuffer& draw(const Point& p,unsigned int color)const
	{
		unsigned int (*fb)[m_row][m_col]=(unsigned int (*)[m_row][m_col])mmap_start;
		(*fb)[p.m_row][p.m_col]=color;
		return *this;
	}
	const FrameBuffer& draw(const Line& l,unsigned int color)const
	{
	}
	const FrameBuffer& clear(unsigned int color)
	{
		unsigned int* temp=(unsigned int*)mmap_start;
		unsigned int max=m_row*m_col;
		for(unsigned int i=0;i<max;i++)
			temp[i]=color;
		return *this;
	}
private:
	const char* m_dev;
	int fb_fd;

	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;

	unsigned char* mmap_start;
	unsigned long buffersize;

	unsigned int m_row;
	unsigned int m_col;
};

#endif//__FRAMEBUFFER_HPP__
