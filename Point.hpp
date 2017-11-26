/*************************************************************************
    > File Name       : Point.hpp
    > Author          : JackZHY
    > Mail            : 158754845@qq.com 
    > Created Time    : Fri 17 Nov 2017 11:02:41 AM CST
    > Description     : 
*************************************************************************/
#ifndef __POINT_HPP__
#define __POINT_HPP__

extern double sin(double x);
extern double cos(double x);

class Point
{
public:
	explicit Point(unsigned int row,unsigned int col):m_row(row),m_col(col){}
	~Point(void){}
	virtual const Point& showInfo(void)const
	{
		printf("row:%u col: %u \n",m_row,m_col);
		return *this;
	}
	Point& move(int dRow,int dCol)
	{
		m_row+=dRow;
		m_col+=dCol;
		return *this;
	}
	Point& move(double angel,double distance)
	{
		int drow=distance*sin(angel);
		int dcol=distance*cos(angel);
		return move(drow,dcol);
	}
	unsigned int m_row,m_col;
};

#endif//__POINT_HPP__
