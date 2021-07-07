#ifndef NUCLIDE_H
#define NUCLIDE_H

#include "numeric_tools.h"
#include "CrossSectionSet.h"
#include "CrossSectionMatrixSet.h"

#include <memory>
#include <vector>
#include <string>

class Nuclide
{
public:

    typedef std::pair<XSKind, CrossSectionSet> XSSetType;

	Nuclide();
    Nuclide(std::string name) : m_name(name), m_isResonant(false) {}

    void setName(std::string name) {m_name = name;}
    std::string getName() {return m_name;}
    void setAWR(double awr) {m_awr = awr;}
    double getAWR() {return m_awr;}
    void setIsResonant(bool value) {m_isResonant = value;}
    bool isResonant() {return m_isResonant;}
    void setTemperatures(std::vector<double> &temps) {m_temperatures = temps;}
    std::vector<double> getTemperatures() {return m_temperatures;}
    double getTemperature(unsigned i) {return m_temperatures.at(i);}
    void setDilutions(std::vector<double> &values) {m_dilutions = values;}
    std::vector<double> getDilutions() {return m_dilutions;}
    double getDilution(unsigned i) {return m_dilutions.at(i);}
    void setEnergyGroupsNumber(unsigned n) {m_energyGroupsNumber = n;}
    unsigned getEnergyGroupsNumber() {return m_energyGroupsNumber;}
    unsigned getXSsNumber() {return isResonant() ? (getDilutions().size() * getTemperatures().size()) : getTemperatures().size();}

    void setXS(CrossSectionSet &xsSet);
    void setXSMatrix(CrossSectionMatrixSet &xsMatrixSet);
    CrossSectionSet& getXSSet(XSKind xsKind);
    static CrossSectionSet& getXSSet(XSKind xsKind, std::vector<XSSetType>& crossSectionSets);
    CrossSectionMatrixSet getXSMatrixSet(XSMatrixKind kind);

    std::vector<XSSetType>& getXSSets() {return m_crossSectionSets;}
    std::vector<XSSetType> getCopyOfXSSets() {return m_crossSectionSets;}
    void setXSSets(std::vector<XSSetType>& crossSectionSets) {m_crossSectionSets = crossSectionSets;}

    void calcXSSets();

    void printDebugData();
    void printXSs(XSKind kind);
    void printMatrixXSs(XSMatrixKind xsKind);

private:

    std::string m_name;
    double m_awr;
    std::vector<double> m_temperatures;
    std::vector<double> m_dilutions;
    unsigned m_energyGroupsNumber;
    bool m_isResonant;

    std::vector<XSSetType> m_crossSectionSets;

    CrossSectionMatrixSet m_scattMatrix00;
    CrossSectionMatrixSet m_scattMatrix01;
};

#endif