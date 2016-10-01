// Boggle.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "Classes.h"

static vector<int> letters = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
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
	totalPoints += word.length() - 2;

	// Puntos por entropía
	//differentWords = std::count(word.begin(), word.end(), '_');

	return totalPoints;
}

int _tmain(int argc, _TCHAR* argv[])
{
    Trie* trie = new Trie();
	ifstream dictionary("input1.txt");
	string board, hash, line;
	const auto start = clock();

	getline(dictionary, board);
	getline(dictionary, hash);

	int cont = 0;

	while (getline(dictionary, line)){
		if(line.size() > 3){
			trie->addWord(line);
		}
		cont++;
		if(cont == 100) break;
	}
	dictionary.close();

	cout<<(clock()-start)/(float)CLOCKS_PER_SEC<<"s"<<endl;

  if (trie->searchWord("kaixo"))
     cout << "Found kaixo" << endl;

  if (trie->searchWord("abandonments"))
      cout << "Found abandonments" << endl;

  if (trie->searchWord("abdomens"))
      cout << "Found abdomens" << endl;

  if (trie->searchWord("abdomes"))
      cout << "Found abdomes" << endl;

  if (trie->searchWord("geography"))
      cout << "Found Balloon" << endl;

	//cout<<(clock()-start)/(float)CLOCKS_PER_SEC<<"s"<<endl;

  delete trie;
	return 0;
}
