#ifndef ERREUR_H
#define ERREUR_H

//!
//! \file Erreur.h
//!

#include <string>
#include <iostream>
using namespace std;

//!
//! \class Erreur
//!
class Erreur
{
public:
	const static int LONGUEURMESSAGE = 100;
	char message[1 + LONGUEURMESSAGE];
	//!
	//! \brief Constructeur vide
	//!
	Erreur();
	//!
	//! \brief Constructeur
	//! \param messageErreur
	//!
	Erreur(const char * messageErreur);
	//!
	//! \biref surcharge operator string()
	//!
	operator string() const;
};

//!
//! \brief surcharge operator <<
//!
ostream & operator << (ostream & os, const Erreur & erreur);

#endif
