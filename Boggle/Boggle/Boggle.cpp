// Boggle.cpp: define el punto de entrada de la aplicación de consola.
//
#include <cstdio>
#include "stdafx.h"
#include "Classes.h"

static unsigned int letters[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
/*
 * Función para calcular el total de puntos de una palabra
 */
unsigned int calcPoints(const string word)
{
	unsigned int totalPoints = 0;
	unsigned int differentWords = 0;
	// Puntos por letra
	for (size_t ii = 0; ii < word.length(); ii++) {
		totalPoints += letters[word[ii] - 97];
	}
	// Puntos por longitud
	totalPoints += word.length() - 2; // Asegurarse de que nunca salga un numero negativo aqui

	// Puntos por entropía
	vector<char> aux;
	for (size_t ii = 0; ii < word.length(); ii++) {
		if (find(aux.begin(), aux.end(), word[ii]) == aux.end()) {
			aux.push_back(word[ii]);
			differentWords++;
		}
	}
	return totalPoints + differentWords;
}

int _tmain(int argc, _TCHAR* argv[])
{
	const auto start = clock();
	const int N = 4;
	char in[N * N + 1]; // max length of a word
	Trie* trie = new Trie();
	string board, hash, line;

	FILE *fDict;
	const char* fileName = "input1.txt";
	fopen_s(&fDict, fileName, "r");

	while(fgets(in, N*N + 1, fDict)){
		trie->addWord(in);
	}

	cout<<(clock()-start)/(float)CLOCKS_PER_SEC<<"s"<<endl;

	const auto start1 = clock();

  if (trie->searchWord("hello"))
     cout << "Found hello" << endl;

	/*
  if (trie->searchWord("abandonments"))
      cout << "Found abandonments" << endl;

  if (trie->searchWord("abdomens"))
      cout << "Found abdomens" << endl;

  if (trie->searchWord("abdomes"))
      cout << "Found abdomes" << endl;

  if (trie->searchWord("geography"))
      cout << "Found Balloon" << endl;*/

	cout<<(clock()-start1)/(float)CLOCKS_PER_SEC<<"s"<<endl;

  delete trie;
	return 0;
}
