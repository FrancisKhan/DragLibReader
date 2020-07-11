#ifndef CYLINDER_H
#define CYLINDER_H

#include "AbstractGeometry.h"

class Cylinder : public AbstractGeometry
{
public:
	Eigen::VectorXd volumes(Eigen::VectorXd &boundaries, std::string dim);
	double surface(Eigen::VectorXd &boundaries, std::string dim);
};

#endif