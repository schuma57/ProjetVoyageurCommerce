#ifndef GELEMENT
#define GELEMENT
#pragma once

//!
//! \file GElement.h
//!

#include <iostream>
#include <string>
using namespace std;

//!
//! \class GElement
//!
class GElement
{
public:
	int clef;
	GElement(const int clef);
	operator string() const;
};

ostream & operator << (ostream & os, const GElement& gElement);

#endif
