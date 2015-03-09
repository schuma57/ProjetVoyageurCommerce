#pragma once

//!
//! \file InfoAreteCarte.h
//!

#include <string>
using namespace std;

//!
//! \class InfoAreteCarte
//!
class InfoAreteCarte
{
public:
	double cout;

	InfoAreteCarte(const double & cout) :cout(cout)
	{}
	virtual ~InfoAreteCarte()
	{}

	operator string() const;
	
};

ostream & operator << (ostream & os, const InfoAreteCarte & infoAreteCarte);
