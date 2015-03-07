#pragma once
#include <string>
using namespace std;

template <class T>
class PElement
{
public:
	T * v;
	PElement<T> * s;

	///
	/// \brief Constructeur
	/// Ne cr�e pas de copie de *v.
	/// Pointe donc sur la donn�e originale *v
	///
	PElement(T * v, PElement<T> * s);


	static const string toString(const PElement<T> * p,
		const char * debut = "( ",
		const char * separateur = ", ",
		const char * fin = ")");

	static int taille(const PElement<T> * l);

	///
	/// efface toute la liste l
	/// mais n'efface pas les donn�es *v
	///
	static void efface1(PElement<T>* & l);

	///
	/// efface toute la liste l
	/// et efface toutes les donn�es *v
	///
	static void efface2(PElement<T>* & l);


	///
	/// Ins�re * a dans l de telle sorte que l reste ordonn�e par ordre croissant (l'�lement en t�te est le plus petit).
	/// Ne r�alise pas de copie de *a. En sortie l et a partagent donc physiquement des donn�es.
	///
	/// Donn�es : a (l'�l�ment � ins�rer), l, estPlusPetitOuEgal(la fonction de comparaison))
	/// R�sultats : l modifi�e par l'insertion
	/// Hypoth�ses : on suppose l ordonn�e par ordre croissant � l'appel
	///
	///
	static void insertionOrdonnee(T * a, PElement<T> * & l,
		bool(*estPlusPetitOuEgal)(const T * a1, const T * a2));

	///
	/// retire la 1�re occurrence de a de l si a est pr�sent dans l, sinon ne fait rien
	///
	/// L'�l�ment trouv� n'est pas effac�
	///
	/// La comparaison est faite sur les pointeurs
	///
	/// Donn�es : a, l
	/// R�sultats : l (�ventuellement modifi�e), par return : true si l'�l�ment a �t� trouv�, false sinon
	///
	static bool retire(const T * a, PElement<T> * & l);


	///
	/// retire l'�l�ment situ� en t�te de l et le renvoie. Le 1er maillon de l est effac�.
	///
	/// l est donc modifi�e par l'appel. En sortie l compte un �l�ment de moins.
	/// lance une exception Erreur si l == NULL � l'appel
	///
	///
	static T * depiler(PElement<T> * & l);

	//-------------------------- PElement<T> ---------------------------
};

template<class T>
ostream& operator <<(ostream & os, const PElement<T> * p)
{
	return os << PElement<T>::toString(p);
}

///
/// Ne cr�e pas de copie de *v.
/// Pointe donc sur la donn�e originale *v
///
template <class T>
PElement<T>::PElement(T * v, PElement<T> * s) :v(v), s(s){}


template <class T>
/*static*/ const string PElement<T>::toString(const PElement<T> * p, const char * debut, const char * separateur, const char * fin)
{
	PElement<T> * r;
	ostringstream oss;

	for (r = (PElement<T>*) p, oss << debut; r; r = r->s)
		oss << *(r->v) << separateur;

	oss << fin;
	return oss.str();
}

template <class T>
/* static */ int PElement<T>::taille(const PElement<T> * l)
{
	if (!l) return 0;
	else
		return 1 + PElement<T>::taille(l->s);
}

///
/// efface toute la liste l
/// mais n'efface pas les donn�es *v
///
template <class T>
/* static */ void PElement<T>::efface1(PElement<T>* & l)
{
	if (l)
	{
		PElement<T>::efface1(l->s);
		delete l; l = NULL;
	}
}

///
/// efface toute la liste l
/// et efface toutes les donn�es *v
///
template <class T>
/* static */ void PElement<T>::efface2(PElement<T>* & l)
{
	if (l)
	{
		PElement<T>::efface2(l->s);
		delete l->v; delete l; l = NULL;
	}
}

///
/// Ins�re * a dans l de telle sorte que l reste ordonn�e par ordre croissant (l'�lement en t�te est le plus petit).
/// Ne r�alise pas de copie de *a. En sortie l et a partagent donc physiquement des donn�es.
///
/// Donn�es : a (l'�l�ment � ins�rer), l, estPlusPetitOuEgal(la fonction de comparaison))
/// R�sultats : l modifi�e par l'insertion
/// Hypoth�ses : on suppose l ordonn�e par ordre croissant � l'appel
///
///
template<class T>
/*static*/ void PElement<T>::
insertionOrdonnee(T * a, PElement<T> * & l,
bool(*estPlusPetitOuEgal)(const T * a1, const T * a2))
{
	if (!l || estPlusPetitOuEgal(a, l->v))
		l = new PElement<T>(a, l);
	else
		PElement<T>::insertionOrdonnee(a, l->s, estPlusPetitOuEgal);
}

///
/// retire la 1�re occurrence de a de l si a est pr�sent dans l, sinon ne fait rien
///
/// L'�l�ment trouv� n'est pas effac�
///
/// La comparaison est faite sur les pointeurs
///
/// Donn�es : a, l
/// R�sultats : l (�ventuellement modifi�e), par return : true si l'�l�ment a �t� trouv�, false sinon
///
template<class T>
/*static*/ bool PElement<T>::retire(const T * a, PElement<T> * & l)
{
	if (!l)
		return false;
	else
	{
		if (a == l->v)
		{
			PElement<T> * r = l;
			l = l->s;
			delete r;
			return true;
		}
		else
			return PElement<T>::retire(a, l->s);
	}
}

///
/// retire l'�l�ment situ� en t�te de l et le renvoie. Le 1er maillon de l est effac�.
///
/// l est donc modifi�e par l'appel. En sortie l compte un �l�ment de moins.
/// lance une exception Erreur si l == NULL � l'appel
///
///
template <class T>
/* static */ T * PElement<T>::depiler(PElement<T> * & l)
{
	if (!l) throw Erreur("impossible de d�piler une pile vide");

	T * a = l->v;
	PElement<T> * tete = l;

	l = l->s; delete tete;
	return a;

}