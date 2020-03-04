/** @file */
#include <iostream>

#ifndef _FUNKCJE_H_
#define _FUNKCJE_H_

/** Funkcja tworzy list� w kt�rej przechowywane b�d� w�z�y drzewa z pliku
@param headTreeList g�owa listy (pocz�tkowo jest nullptr)
@param root korze� drzewa (pocz�tkowo jest nullptr)
@param nameTreeStructFile nazwa pliku struktury drzewa
@return void
*/
void getTreeList(treeList*& headTreeList, tree*& root, std::string nameTreeStructFile);

/** Funkcja tworzy drzewo decyzji binarnej z drzew z listy
@param headTreeList g�owa listy
@param mainHead kopia g�owy listy (pocz�tkowo ten sam adres co headTreeList)
@param root korze� drzewa decyzji binarnej
@param index warto�� indeksu li�cia do pobrania (na pocz�tku wywo�ujemy z indeksem  0)
@return void
*/
void getTreeStruct(treeList*& headTreeList, treeList*& mainHead, tree*& root, int index);

/** Funkcja przyporz�dkowuje warto�ci atrybut�w pod etykiety i wypisuje je do pliku
@param root korzen drzewa decyzji binarnej
@param labelHead g�owa listy etykiet (pocz�tkowo jest nullptr)
@param measureHead g�owa listy warto�ci atrybut�w (pocz�tkowo jest nullptr)
@param nameDataFile nazwa pliku z danymi
@param nameOutputFile nazwa pliku wyj�ciowego
@return void
*/
void sortData(tree* root, labelList*& labelHead, measureList*& measureHead, std::string nameDataFile, std::string nameOutputFile);

/** Funkcja usuwa list� drzew razem z w�z�ami drzew
@param headTreeList g�owa listy drzew
@param root korzen drzewa decyzyjnego
@return void
*/
void destroyTreeList(treeList*& headTreeList, tree*& root);

/** Funkcja usuwa list� etykiet i list� warto�ci atrybut�w
@param labelHead g�owa listy etykiet
@param measureHead g�owa listy warto�ci atrybut�w
@return void
*/
void destroyList(labelList*& labelHead, measureList*& measureHead);

#endif