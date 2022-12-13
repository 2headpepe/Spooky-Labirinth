#include"coordinates.h"

coordinates::coordinates()
{
	x = 0;
	y = 0;
}
coordinates::coordinates(const double& x, const double& y)
{
	this->x = x;
	this->y = y;
}
coordinates coordinates::operator=(const coordinates& coor)
{
	this->x = coor.x;
	this->y = coor.y;
	return *this;
}
coordinates coordinates::operator+=(const coordinates& coor)
{
	this->x += coor.x;
	this->y += coor.y;
	return *this;
}

coordinates coordinates::operator*(const double& coef) {
	this->x *= coef;
	this->y *= coef;
	return *this;
}
coordinates coordinates::operator+(const coordinates& coor) {
	coordinates tmp;
	tmp.x = this->x + coor.x;
	tmp.y = this->y + coor.y;
	return tmp;
}
coordinates coordinates::operator-(const coordinates& coor) {
	coordinates tmp;
	tmp.x = this->x - coor.x;
	tmp.y = this->y - coor.y;
	return tmp;
}