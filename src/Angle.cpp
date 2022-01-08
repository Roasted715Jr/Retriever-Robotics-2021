#include "Angle.h"

Angle::Angle(const double& angle) {
	this->angle = angle;
}

bool Angle::operator==(const Angle& rhs) {
	return this->angle * 1.05 > rhs.angle && this->angle * 0.95 < rhs.angle;
}

bool Angle::operator!=(const Angle& rhs) {
	return !(*this == rhs);
}

bool Angle::operator<(const Angle& rhs) {
	return this->angle < rhs.angle;
}

bool Angle::operator>(const Angle& rhs) {
	return this->angle > rhs.angle;
}
