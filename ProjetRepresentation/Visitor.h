#ifndef VISITOR
#define VISITOR
#pragma once

//!
//! \brief class mere des visiteurs
//! \file Visitor.h
//!


//!
//! \class Visitor
//! \brief design pattern Visitor
//! classe abstract
//!
class Visitor
{
protected:
	//!
	//! \brief Constructeur
	//!
	Visitor(){}

public:
	//!
	//! \brief Destructeur
	//!
	virtual ~Visitor(){}

	//!
	//! \brief visite un graphe
	//! \param graphe
	//!
	virtual void visiteGraphe() const = 0;
};

#endif
