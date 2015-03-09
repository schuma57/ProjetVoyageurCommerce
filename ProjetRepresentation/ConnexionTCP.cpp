//!
//! \file ConnexionTCP.cpp
//!
#include "ConnexionTCP.h"


//--------------------- static --------------------------------
ConnexionTCP* ConnexionTCP::instanceUnique = NULL;
SOCKET ConnexionTCP::sock;

ConnexionTCP* ConnexionTCP::getConnexionTCP()
{
	if (instanceUnique == NULL)
		instanceUnique = new ConnexionTCP();
	return instanceUnique;
}
//---------------------- fin static ------------------------------

ConnexionTCP::ConnexionTCP()
{
	int retour;
	retour = WSAStartup(MAKEWORD(2, 0), &wsaData);
	if (retour) throw Erreur("L'initialisation a échoué");
	cout << "initialisation winsock effectuée" << endl;
	int familleAdresses = AF_INET; // IPv4
	int typeSocket = SOCK_STREAM; // mode connecté TCP
	int protocole = IPPROTO_TCP;
	sock = socket(familleAdresses, typeSocket, protocole);
	if (sock == INVALID_SOCKET)
	{
		ostringstream oss;
		oss << "la création du socket a echoue : code d'erreur = " << WSAGetLastError() << endl;
		throw Erreur(oss.str().c_str());
	}
	cout << "socket cree" << endl;
	cout << "tapez l'adresse IP du serveur de dessin : " << endl;
	cin >> adresseServeur;
	cout << "tapez le port du serveur du serveur de dessin : " << endl;
	cin >> portServeur;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = inet_addr(adresseServeur); // inet_addr() convertit de l'ASCII en entier
	sockaddr.sin_port = htons(portServeur);
	retour = connect(sock, (SOCKADDR *)&sockaddr, sizeof(sockaddr)); // renvoie une valeur non nulle en cas d'échec.
	// Le code d'erreur peut être obtenu par un appel à WSAGetLastError()
	if (retour == SOCKET_ERROR)
		throw Erreur("La connexion a échoué");
	cout << "Connexion au serveur de dessin reussie" << endl;
}


ConnexionTCP::~ConnexionTCP()
{
	int retour;
	retour = shutdown(sock, SD_BOTH);
	if (retour == SOCKET_ERROR)
		throw Erreur("la coupure de connexion a échoué");
	retour = closesocket(sock);
	if (retour)
		throw Erreur("La fermeture du socket a échoué");
	WSACleanup();
	cout << "Arret normal du client" << endl;
}

void ConnexionTCP::dessinerGraphe()
{
	//ConnexionTCP::getConnexionTCP();
}
