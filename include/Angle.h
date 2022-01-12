#ifndef ANGLE_H
#define ANGLE_H

class Angle {
public:
	Angle();
	Angle(const double angle);

	//Puts angle within the rangle of [-180, 180]
	void normalize();

	operator double() const;

	//Overloaded equality
	bool operator==(const Angle& rhs);
	//Overloaded inequality
	bool operator!=(const Angle& rhs);
	//Overloaded less than
	bool operator<(const Angle& rhs);
	//Overloaded greater than
	bool operator>(const Angle& rhs);
	//Overloaded assignment
	void operator=(const double& rhs);
	//Overloaded addition
	Angle operator+(const Angle& rhs);
	//Overloaded addition for doubles
	Angle operator+(const double& rhs);
	//Overloaded addition and assignment for doubles
	void operator+=(const double& rhs);
	//Overloaded subtraction
	Angle operator-(const Angle& rhs);
	//Overlaoded subtraction and assignment for doubles
	void operator-=(const double& rhs);
	//Overloaded negation
	Angle operator-();
	//Overloaded multiplication
	Angle operator*(const Angle& rhs);
	//Overloaded multiplication for doubles
	Angle operator*(const double& rhs);
	//Overloaded division
	Angle operator/(const Angle& rhs);
	//Overloaded division for doubles
	Angle operator/(const double& rhs);
private:
	double angle;
};

#endif
