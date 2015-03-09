//!
//! \file VisitorBSplines.cpp
//!
#include "VisitorBSplines.h"
#include "ConnexionTCP.h"


VisitorBSplines::VisitorBSplines()
{
}


VisitorBSplines::~VisitorBSplines()
{
}


void VisitorBSplines::visiteGraphe() const
{
	ConnexionTCP::getConnexionTCP();
}
