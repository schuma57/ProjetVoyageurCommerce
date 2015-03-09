#pragma once

//!
//! \file InfoSommetCarte.h
//!

#include <string>
#include "Vecteur2D.h"
using namespace std;

//!
//! \class InfoSommetCarte
//!
class InfoSommetCarte
{
public:
	string nom;
	Vecteur2D position;

	InfoSommetCarte(const string & nom, const Vecteur2D & position) :nom(nom), position(position)
	{}

	virtual ~InfoSommetCarte()
	{}

	operator string() const;
};

ostream & operator << (ostream & os, const InfoSommetCarte & infoSommetCarte);
