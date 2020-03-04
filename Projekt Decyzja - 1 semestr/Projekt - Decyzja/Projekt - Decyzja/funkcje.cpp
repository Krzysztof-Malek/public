/** @file */
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ios>
#include <climits>
#include <random>
#include <chrono>
#include <iomanip>
#include <deque>

#include "struktury.h"
#include "funkcje.h"

void getTreeList(treeList*& headTreeList, tree*& root, std::string nameTreeStructFile) {//funkcja pobiera linię, pokolei wyczytuje z niej kolejne dane i tworzy węzły w liście
	std::ifstream treeFile(nameTreeStructFile);

	std::string temp = {};
	std::string line;
	std::stringstream ssline;

	int index = NULL;
	std::string a = {};
	char b = {};
	float c = NULL;
	std::string d = {};
	std::string e = {};
	size_t possition = {};

	treeList* mainHead;
	int if_ft;

	while (std::getline(treeFile, line)) {	//wczytywanie lini z pliku
		ssline.clear();
		ssline.str(line);	//stworzenie stringStreama dla lini z pliku
		ssline >> temp;
		index = std::stof(temp);
		ssline >> a;

		if ((possition = a.find('<')) != std::string::npos) {	//sprawdzenie znaku porównania
			temp = a.substr(possition + 1);
			c = std::stof(temp);
			a = a.substr(0, possition);
			b = '<';
		}
		else if ((possition = a.find('>')) != std::string::npos) {
			temp = a.substr(possition + 1);
			c = std::stof(temp);
			a = a.substr(0, possition);
			b = '>';
		}

		ssline >> d;
		ssline >> e;

		headTreeList = new treeList{ new tree{ index, a, b, c, d, e, nullptr, nullptr }, headTreeList };	//tworzenie węzła w liście
	}
	treeFile.close();
}

void getTreeStruct(treeList*& headTreeList, treeList*& mainHead, tree*& root, int index) {	//funkcja tworzy drzewo właściwe z listy węzłów
	if (!root) {
		while (headTreeList->root->index != index) {	//wyszukiwanie odpowiedniego indeksu i przeskok o jeden dalej
			headTreeList = headTreeList->nextTree;
		}
		root = headTreeList->root;
		headTreeList = mainHead;
	}
	if (isdigit(root->if_false[0])) {	//jeżeli przejściem jest liczba to funkcja wywołuje się dla lewej gałęzi
		index = std::stoi(root->if_false);
		getTreeStruct(headTreeList, mainHead, root->left, index);
	}
	if (isdigit(root->if_true[0])) {	//jeżeli przejściem jest liczba to funkcja wywołuje się dla prawej gałęzi
		index = std::stoi(root->if_true);
		getTreeStruct(headTreeList, mainHead, root->right, index);
	}
}

void sortData(tree* root, labelList*& labelHead, measureList*& measureHead, std::string nameDataFile, std::string nameOutputFile) {
	std::ifstream dataFile(nameDataFile);

	std::stringstream sStreamAttributes;
	std::stringstream sStream;
	std::string attributeLine;
	std::string line;
	std::string a;
	float b = NULL;
	int doWhile;

	std::getline(dataFile, attributeLine);	//string z atrybutami z pliku

	tree* mainRoot = root;
	labelList* mainLabel = nullptr;
	while (std::getline(dataFile, line))
	{
		doWhile = 1;
		root = mainRoot;
		do {
			a = "";
			b = NULL;
			sStreamAttributes.clear();
			sStream.clear();
			sStreamAttributes.str(attributeLine);
			sStream.str(line);
			labelHead = mainLabel;	//powrót lini etykiet na początek

			do {	//leci po lini z atrybutami razem z linią wartości, dzięki czemu pobiera odpowiednią wartość (np. jeśli szybkość jest 3 to pobierze po kolei 3 wartości i zostanie z tą 3)
				sStream >> b;
			} while (sStreamAttributes >> a && a != root->attribute);

			if (root->comp_sign == '<') {	//sprawdzanie znaku porównania z węzła drzewa
				if (b < root->requirement) {	//sprawdzenie czy warunek jest spełniony
					if (isdigit(root->if_true[0])) {	//jeśli warunek spełniony -> przejście do kolejnego węzła drzewa
						root = root->right;
					}
					else {	//jeśli warunek niespełniony -> przypisanie do etykiety
						do {
							if (!labelHead) {	//jeśli etykieta nie istnieje, stwórz nową wraz z pierszą przypisaną wartością
								labelHead = mainLabel;
								labelHead = new labelList{ root->if_true, measureHead = new measureList {line, nullptr}, labelHead };	//wpisuje nową etykietę na początek
								mainLabel = labelHead;

								doWhile = 0;	//dopóki program nie wpisze wartości pod etykietę linia z wartośćiami krąży najpierw po drzewie a potem po liście etykiet -> doWhile przerywa 2 pętle, z drzewem i listą etykiet
							}
							else {
								if (root->if_true != labelHead->label) {	//szukanie w liście czy podana etykieta już istnieje
									labelHead = labelHead->nextLabel;
								}
								else {	//przypisanie kolejnej wartości do etykiety
									labelHead->measureHead = measureHead = new measureList{ line, labelHead->measureHead }; //wpisuje nową wartość na początek
									doWhile = 0;
								}
							}
						} while (doWhile);
					}
				}
				else {
					if (isdigit(root->if_false[0])) {
						root = root->left;
					}
					else {
						do {
							if (!labelHead) {
								labelHead = mainLabel;
								labelHead = new labelList{ root->if_false, measureHead = new measureList {line, nullptr}, labelHead };
								mainLabel = labelHead;

								doWhile = 0;
							}
							else {
								if (root->if_false != labelHead->label) {
									labelHead = labelHead->nextLabel;
								}
								else {
									labelHead->measureHead = measureHead = new measureList{ line, labelHead->measureHead };
									doWhile = 0;
								}
							}
						} while (doWhile);
					}
				}
			}
			else {
				if (b > root->requirement) {
					if (isdigit(root->if_true[0])) {
						root = root->right;
					}
					else {
						do {
							if (!labelHead) {
								labelHead = mainLabel;
								labelHead = new labelList{ root->if_true, measureHead = new measureList {line, nullptr}, labelHead };
								mainLabel = labelHead;

								doWhile = 0;
							}
							else {
								if (root->if_true != labelHead->label) {
									labelHead = labelHead->nextLabel;
								}
								else {
									labelHead->measureHead = measureHead = new measureList{ line, labelHead->measureHead };
									doWhile = 0;
								}
							}
						} while (doWhile);
					}
				}
				else {
					if (isdigit(root->if_false[0])) {
						root = root->left;
					}
					else {
						do {
							if (!labelHead) {
								labelHead = mainLabel;
								labelHead = new labelList{ root->if_false, measureHead = new measureList {line, nullptr}, labelHead };
								mainLabel = labelHead;
								doWhile = 0;
							}
							else {
								if (root->if_false != labelHead->label) {
									labelHead = labelHead->nextLabel;
								}
								else {
									labelHead->measureHead = measureHead = new measureList{ line, labelHead->measureHead };
									doWhile = 0;
								}
							}
						} while (doWhile);
					}
				}
			}
		} while (doWhile);
	}

	std::ofstream outputFile(nameOutputFile);
	labelHead = mainLabel;	//przygotowuje labelHead do wypisania do pliku
	while (labelHead) {
		outputFile << labelHead->label << '\n';
		measureList* mainMeasureHead = labelHead->measureHead;	//zachowanie oryginalnego adresu głowy listy wartości (to jest linia 222: póżniej wykorzystana w lini 229)
		while (labelHead->measureHead) {
			outputFile << labelHead->measureHead->measure << '\n';
			labelHead->measureHead = labelHead->measureHead->next;
		}
		outputFile << '\n';	//przerwa pomiędzy etykietami

		labelHead->measureHead = mainMeasureHead;	//powrót etykiety do orygilanego adresu głowy listy wartości
		labelHead = labelHead->nextLabel;	//przejście do następnej etykiety
	}
	labelHead = mainLabel;	//przygotowuje labelHead do zwlonienia pamięci
	outputFile.close();
	dataFile.close();
}

void destroyTreeList(treeList*& headTreeList, tree*& root) {	//usuwa listę z węzłami i drzewo binarne poprzez tą listę
	if (headTreeList) {
		destroyTreeList(headTreeList->nextTree, headTreeList->root);	//idzie na koniec listy po czym usuwa się
		delete headTreeList->root;
		headTreeList->root = nullptr;
		delete headTreeList;
		headTreeList = nullptr;
	}
}

void destroyList(labelList*& labelHead, measureList*& measureHead) {	//usuwa listę wartości i listę etykiet
	if (labelHead) {
		destroyList(labelHead->nextLabel, labelHead->nextLabel->measureHead);	//idzie na koniec listy etykiet
		do {
			if (!labelHead->measureHead->next) {	//jeśli została ostania wartość usuwa głowę listy wartości
				delete labelHead->measureHead;
				labelHead->measureHead = nullptr;
			}
			else {	//jeśli jest więcej niż 1 element listy wartości, program usuwa element 1 i przypisuje etykiecie element 2
				measureList* temp = labelHead->measureHead->next;	//zmienna pomocnicza -> 2 element listy wartości
				delete labelHead->measureHead;
				labelHead->measureHead = nullptr;
				labelHead->measureHead = temp;
			}
		} while (labelHead->measureHead != nullptr);
		delete labelHead;
		labelHead = nullptr;
	}
}