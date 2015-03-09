#ifndef VISITORBSPLINES
#define VISITORBSPLINES
#pragma once

//!
//! \file VisitorBSplines.h
//!

#include "Visitor.h"

//!
//! \class VisitorBSplines
//! \brief herite de la classe Visitor
//!
class VisitorBSplines : public Visitor
{
public:
	//!
	//! \brief Constructeur
	//!
	VisitorBSplines();
	//!
	//! \brief Destructeur
	//!
	virtual ~VisitorBSplines();

	//!
	//! \brief override
	//!
	virtual void visiteGraphe() const;
};

#endif
