#ifndef SOLVERDATA_H
#define SOLVERDATA_H

#include "SolverKind.h"

class SolverData
{
public:
    SolverData(const SolverKind &kind) : m_kind(kind), m_accuracy(0.0), 
    m_maxIterNumber(0) {}
	
    void setKind(SolverKind kind) {m_kind = kind;}
    SolverKind getKind() {return m_kind;}
    void setAccuracy(double accuracy) {m_accuracy = accuracy;}
    double getAccuracy() {return m_accuracy;}
    void setMaxIterNumber(int maxIterNumber) {m_maxIterNumber = maxIterNumber;}
    int getMaxIterNumber() {return m_maxIterNumber;}
	
private:
    SolverKind m_kind;
	double m_accuracy;
    int m_maxIterNumber;
};

#endif