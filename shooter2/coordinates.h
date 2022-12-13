#pragma once

class coordinates
{
public:
	coordinates();
	coordinates(const double& x, const double& y);
	coordinates operator=(const coordinates& coor);
	coordinates operator+(const coordinates& coor);
	coordinates operator-(const coordinates& coor);
	coordinates operator+=(const coordinates& coor);
	coordinates operator*(const double& coef);
	double x;
	double y;
private:
	
};