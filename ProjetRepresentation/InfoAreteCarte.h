#pragma once

#include <string>
using namespace std;


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
