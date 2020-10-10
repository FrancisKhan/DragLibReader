#ifndef CYLDIFFUSIONCODE_H
#define CYLDIFFUSIONCODE_H

#include "BaseDiffusionCode.h"

class CylDiffusionCode : public BaseDiffusionCode
{
public:
    CylDiffusionCode(Reactor &reactor, Library &library) : 
	BaseDiffusionCode(reactor, library), 
	m_library(library), m_mesh(reactor.getMesh()), m_radii(m_mesh.getBoundaries("m")),
	m_volumes(m_mesh.getVolumes("m")),
	m_cells(m_mesh.getCellsNumber()) {}

	Eigen::MatrixXd calcMMatrix() override;
	Eigen::MatrixXd calcFMatrix() override {;} 
	Eigen::MatrixXd applyBoundaryConditions(Eigen::MatrixXd &T) override;
	
private:
	Library &m_library;
	Mesh &m_mesh;
	Eigen::VectorXd m_radii;
	Eigen::VectorXd m_volumes;
	int m_cells;
	Eigen::VectorXd m_temperatures;
	Eigen::VectorXd m_heatSources;
};

#endif