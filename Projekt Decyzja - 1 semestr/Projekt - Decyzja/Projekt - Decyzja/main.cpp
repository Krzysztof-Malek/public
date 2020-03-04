/** @file */
/*
Projekt PPK - Decyzja
*/
//Projekt uruchamiany z komend� -i inputFile.txt -t treeFile.txt -o outputFile.txt
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ios>

#include "struktury.h"
#include "funkcje.h"

int main(int argc, char** argv)
{
	std::string nameDataFile = "";
	std::string nameTreeStructFile = "";
	std::string nameOutputFile = "";

	if (argc != 7) {
		std::cerr << "Some of the arguments are not included" << std::endl;
		return EXIT_FAILURE;
	}
	else {
		for (int i = 1; i < argc; i = i + 2) {
			std::string swift(argv[i]);
			std::string name(argv[i + 1]);

			if (swift == "-i") {
				if (nameDataFile != "") {
					std::cerr << "You cannot duplicate argument" << std::endl;
					return EXIT_FAILURE;
				}
				nameDataFile = name;
			}
			else if (swift == "-t") {
				if (nameTreeStructFile != "") {
					std::cerr << "You cannot duplicate argument" << std::endl;
					return EXIT_FAILURE;
				}
				nameTreeStructFile = name;
			}
			else if (swift == "-o") {
				if (nameOutputFile != "") {
					std::cerr << "You cannot duplicate argument" << std::endl;
					return EXIT_FAILURE;
				}
				nameOutputFile = name;
			}
			else {
				std::cerr << "You have to specify file pathes in specific order" << std::endl;
				std::cerr << "Example: -i inputFile.txt -t treeFile.txt -o outputFile.txt" << std::endl;
				return EXIT_FAILURE;
			}
		}
	}
	if (!std::ifstream(nameDataFile)) {
		std::cerr << "File " << nameDataFile << " wasn't found" << std::endl;
		return EXIT_FAILURE;
	}
	if (!std::ifstream(nameTreeStructFile)) {
		return EXIT_FAILURE;
	}
	if (!std::ifstream(nameTreeStructFile, std::ios::ate).tellg()) {
		std::cerr << "File with tree structure is empty" << std::endl;
		return EXIT_FAILURE;
	}

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	treeList* headTreeList = nullptr;
	tree* root = nullptr;
	labelList* labelHead = nullptr;
	measureList* measureHead = nullptr;

	getTreeList(headTreeList, root, nameTreeStructFile);	//Stworzenie listy z w�z�ami drzewa

	treeList* mainHead = headTreeList;	//stworzenie kopi g�owy listy z w�z�ami drzewa
	getTreeStruct(headTreeList, mainHead, root, 0);	//uruchamiany z 0 jako jego korze� (warunek ustalony)	 //Stworzenie w�a�ciwego drzewa z listy

	sortData(root, labelHead, measureHead, nameDataFile, nameOutputFile);	//uporz�dkowanie warto��i pod etykiety i wypisanie ich do pliku

	destroyTreeList(headTreeList, root);			//zwalnianie pami�ci
	destroyList(labelHead, labelHead->measureHead);	//zwalnianie pami�ci

	return 0;
}