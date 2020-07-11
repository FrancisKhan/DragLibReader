#include "BaseHeatCode.h"
#include "SphHeatCode.h"
#include "numeric_tools.h"

using namespace Eigen;
using namespace PrintFuncs;

std::tuple<MatrixXd, VectorXd> SphHeatCode::setupSystem()
{
    MatrixXd T = MatrixXd::Zero(m_cells, m_cells);

    m_temperatures     = m_mesh.getTemperatures("C");
    m_heatSources      = m_mesh.getHeatSources();
    VectorXd lambda    = getInterfaceThermalConductivities();
    VectorXd cellSizes = m_mesh.getCellSizes("m");

    for(int i = 0; i < m_cells; i++)
    {
        if(i == 0)
        {
            T(i, i)     = + lambda[i + 1] * pow(m_radii(i + 1), 2) / cellSizes(i + 1);
            T(i, i + 1) = - lambda[i + 1] * pow(m_radii(i + 1), 2) / cellSizes(i + 1);
        }
        else if(i == m_cells - 1)
        {
            T(i, i)     = + lambda[i] * pow(m_radii(i), 2) / cellSizes(i - 1);
            T(i, i - 1) = - lambda[i] * pow(m_radii(i), 2) / cellSizes(i - 1);
        }
        else
        {
            T(i, i)     = + lambda[i] * pow(m_radii(i), 2) / cellSizes(i - 1) + 
                            lambda[i + 1] * pow(m_radii(i + 1), 2) / cellSizes(i + 1);

            T(i, i - 1) = - lambda[i] * pow(m_radii(i), 2) / cellSizes(i - 1);
            T(i, i + 1) = - lambda[i + 1] * pow(m_radii(i + 1), 2) / cellSizes(i + 1);
        }

        m_heatSources(i) *= cellSizes(i) * pow((m_radii(i) + 0.5 * cellSizes(i)), 2);
    }

    return std::make_tuple(T, m_heatSources);
}

std::tuple<MatrixXd, VectorXd> SphHeatCode::applyBoundaryConditions(MatrixXd &T, VectorXd &source)
{
    VectorXd boundaries = m_mesh.getHeatBoundaryConditions();
    VectorXd lambda     = getInterfaceThermalConductivities();

    // Right boundary condition

    double deltaXR = m_radii(m_cells) - m_radii(m_cells - 1);

    double AR = boundaries(3);
    double BR = boundaries(4);
    double CR = boundaries(5);

    double denominatorR = (deltaXR / (2.0 * pow(m_radii(m_cells), 2) * lambda(m_cells - 1))) * AR + BR;
    double alphaR =  AR / denominatorR;
    double betaR  = -CR / denominatorR;

    T(m_cells - 1, m_cells - 1) = T(m_cells - 1, m_cells - 1) + alphaR;
    source(m_cells - 1) = source(m_cells - 1) - betaR;

    out.getLogger()->debug("Thermal conductivities [W/(m*K)]:");
    printVector(lambda, out, TraceLevel::DEBUG);

    out.getLogger()->debug("T matrix [W/K]:");
    printMatrix(T, out, TraceLevel::DEBUG);

    out.getLogger()->debug("Source [W]:");
    printVector(source, out, TraceLevel::DEBUG);

    return std::make_tuple(T, source);
}