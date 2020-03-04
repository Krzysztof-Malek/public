/** @file */
#include <iostream>

#ifndef _STRUKTURY_H_
#define _STRUKTURY_H_

/** Lista przechowuj�ca w�z�y drzewa decyzji binarnej */
struct treeList {
	struct tree* root;		///< adres drzewa
	treeList* nextTree;		///< adres nast�pnego drzewa w li�cie
};

/** Drzewo decyzji binarnej */
struct tree
{
	int index;			///< warto�� indeksu wej�cia
	std::string attribute;		///< nazwa attrybutu do por�wnania
	char comp_sign;			///< znak por�wnania
	float requirement;		///< warto�� decyzyjna atrybutu
	std::string if_false;		///< indeks wyj�cia NIE
	std::string if_true;		///< indeks wyj�cia TAK
	tree* left;			///< adres lewego potomka
	tree* right;			///< adres prawego potomka
};

/** Lista etykiet ze wska�nikami na list� warto�ci atrybut�w  */
struct labelList
{
	std::string label;			///< nazwa etykiety
	struct measureList* measureHead;	///< adres pocz�tku listy warto�ci atrybut�w
	labelList* nextLabel;			///< adres nast�pnego elementu listy
};

/** Lista warto�ci atrybut�w */
struct measureList
{
	std::string measure;	///< warto�ci atrybut�w
	measureList* next;	///< adres nast�pnego elementu listy
};

#endif