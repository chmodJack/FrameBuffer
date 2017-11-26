/*************************************************************************
    > File Name       : Line.hpp
    > Author          : JackZHY
    > Mail            : 158754845@qq.com 
    > Created Time    : Fri 17 Nov 2017 11:10:49 AM CST
    > Description     : 
*************************************************************************/
#ifndef __LINE_HPP__
#define __LINE_HPP__

#include"Point.hpp"
class Line
{
public:
	Line(const Point& p1,const Point& p2):m_p1(p1),m_p2(p2){}
	Point m_p1,m_p2;
};
#endif//__LINE_HPP__
