#include "Angle.h"

Angle::Angle() {
	angle = 0;
	normalize();
}

Angle::Angle(const double angle): angle(angle) {
	normalize();
}

void Angle::normalize() {
	while (-180 > angle)
		angle += 360;

	while (180 < angle)
		angle -= 360;
}

Angle::operator double() const {
	return angle;
}

bool Angle::operator==(const Angle& rhs) {
	double tolerance = 0.1;

	if (this != &rhs)
		return this->angle * (1 + tolerance) > rhs.angle && this->angle * (1 - tolerance) < rhs.angle;
	
	return true;
}

bool Angle::operator!=(const Angle& rhs) {
	if (this != &rhs)
		return !(*this == rhs);
	
	return false;
}

bool Angle::operator<(const Angle& rhs) {
	if (this != &rhs)
		return this->angle < rhs.angle;

	return false;
}

bool Angle::operator>(const Angle& rhs) {
	if (this != &rhs)
		return angle > rhs.angle;

	return false;
}

void Angle::operator=(const double& rhs) {
	angle = rhs;
	normalize();
}

Angle Angle::operator+(const Angle& rhs) {
	return Angle(angle + rhs.angle);
}

Angle Angle::operator+(const double& rhs) {
	return Angle(angle + rhs);
}

void Angle::operator+=(const double& rhs) {
	angle += rhs;
	normalize();
}

Angle Angle::operator-(const Angle& rhs) {
	return Angle(this->angle - rhs.angle);
}

void Angle::operator-=(const double& rhs) {
	angle -= rhs;
	normalize();
}

Angle Angle::operator-() {
	return Angle(-this->angle);
}

Angle Angle::operator*(const Angle& rhs) {
	return Angle(angle * rhs.angle);
}

Angle Angle::operator*(const double& rhs) {
	return Angle(angle * rhs);
}

Angle Angle::operator/(const Angle& rhs) {
	return Angle(angle * rhs.angle);
}

Angle Angle::operator/(const double& rhs) {
	return Angle(angle * rhs);
}
