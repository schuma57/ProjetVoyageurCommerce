#ifndef CONNEXIONTCP
#define CONNEXIONTCP
#pragma once

//!
//! \file ConnexionTCP.h
//!
#pragma comment(lib,"Ws2_32.lib")
#include <iostream>
#include <sstream>
#include <winsock2.h>
#include "Erreur.h"
using namespace std;

#define L 200

//!
//! \class ConnexionTCP
//! \brief classe en singleton
//!
class ConnexionTCP
{
private:
	WSADATA wsaData;
	SOCKADDR_IN sockaddr;
	static SOCKET sock;
	char adresseServeur[L];
	short portServeur;
	//!
	//! \brief Constructeur private
	//!
	ConnexionTCP();
	//!
	//! \brief instance unique de la classe
	//!
	static ConnexionTCP* instanceUnique;

public:
	//!
	//! \brief Destructeur
	//!
	virtual ~ConnexionTCP();
	//!
	//! construit l'instance unique si NULL
	//! \return l'instance unique
	//!
	static ConnexionTCP* getConnexionTCP();
	//!
	//! \brief ouvre bsplines
	//!
	void dessinerGraphe();
};

#endif
