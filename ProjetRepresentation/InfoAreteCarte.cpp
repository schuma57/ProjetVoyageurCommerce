//!
//! \file InfoAreteCarte.cpp
//!
#include <sstream>
#include "InfoAreteCarte.h"


InfoAreteCarte::operator string() const
{
	ostringstream oss;

	oss << "cout = " << cout << endl;

	return oss.str();
}


ostream & operator << (ostream & os, const InfoAreteCarte & infoAreteCarte)
{
	return os << (string)infoAreteCarte;
}
