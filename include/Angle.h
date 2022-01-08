#ifndef ANGLE_H
#define ANGLE_H

class Angle {
public:
	Angle(const double& angle);

	bool operator==(const Angle& rhs);
	bool operator!=(const Angle& rhs);
	bool operator<(const Angle& rhs);
	bool operator>(const Angle& rhs);
private:
	double angle;
};

#endif
