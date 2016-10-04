// Boggle.cpp: define el punto de entrada de la aplicación de consola.
//
#include "stdafx.h"
#include "Classes.h"

/* GLOBAL VARIABLES */
Trie* trie = new Trie();
static unsigned int letters[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
vector<string> foundWords;
vector<unsigned int> foundPunctuation;

/*
 * Function to calculate the points of a word
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

/*
 * Function to search all letter combination possible 
 */
// Esta función devuelve un 1 o un 0 dependiendo de si ha encontrado una palabra o no (podemos hacer
// que si encuentra varias, devuelva otro número, eso cambiaría el tipo de argumento de salida de
// bool a int). Además de eso, cuando encuentre una palabra hará un push_back paralelo al vector
// foundWords y foundPunctuation donde se guardarán la palabra encontrada y su puntuación.
bool findWordsPlease(string word) {
	for (unsigned int jj = 97; jj <= 122; jj++) { // Separo el primer y ultimo caso para no encontrarnos con un branch problem a la hora de paralelizar
		string letter;
		letter = char(jj);
		string newWord = letter + word;
		if (trie->searchWord(newWord)) {
			foundWords.push_back(newWord);
			foundPunctuation.push_back(calcPoints(newWord));
		}
	}
	for (unsigned int jj = 97; jj <= 122; jj++) {
		string letter;
		letter = char(jj);
		string newWord = word + letter;
		if (trie->searchWord(newWord)) {
			foundWords.push_back(newWord);
			foundPunctuation.push_back(calcPoints(newWord));
		}
	}
	for (size_t ii = 1; ii < word.length(); ii++) {
		string left = "";
		string right = "";
		for (size_t jj = 0; jj < ii; jj++) {
			left += word[jj];
		}
		for (size_t jj = ii; jj < word.length(); jj++) {
			right += word[jj];
		}
		for (unsigned int jj = 97; jj <= 122; jj++) {
			string letter;
			letter = char(jj);
			string newWord = left + letter + right;
			if (trie->searchWord(newWord)) {
				foundWords.push_back(newWord);
				foundPunctuation.push_back(calcPoints(newWord));
			}
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	const auto start = clock();
	/* INITIALIZATIONS OF VARIABLES */
	string board_aux, hash, line;
	char board[4][4];


	/* Charge Trie, hash and auxiliar variable for board */
	getline (cin,board_aux);
	getline (cin,hash);
	while(!cin.eof()){
		getline (cin,line);
		trie->addWord(line);
	}
	
	/* Charge the letters into the board */
	unsigned int tmp = 0;
	for(unsigned int ii = 0; ii < 4; ii++){
		for(unsigned int jj = 0; jj < 4; jj++){
			board[ii][jj] = board_aux[tmp];
			tmp++;
		}
	}
	
	bool a = findWordsPlease("hllo");
	cout << (clock()-start) / (float)CLOCKS_PER_SEC << "s" << endl; // tiempo en cargar el diccionario: 120ms
	delete trie;
	return 0;
}
