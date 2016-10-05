// Boggle.cpp: define el punto de partida entre el punto de divergencia del 1% y la distopía apocalíptica
//
#include "stdafx.h"
#include "Classes.h"

/* GLOBAL VARIABLES */
Trie* trie = new Trie();
static unsigned int letters[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
vector<string> foundWords;
vector<unsigned int> foundScore;
char board[4][4];

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
// foundWords y foundScore donde se guardarán la palabra encontrada y su puntuación.
bool findWordsPlease(string word) {
	for (size_t ii = 0; ii <= word.length(); ii++) {	// empezando desde 0 hasta <= wordlength se puede no hacer el for de arriba
		string left = "";
		string right = "";
		for (size_t jj = 0; jj < ii; jj++) { //optimizable?
			left += word[jj];
		}
		for (size_t kk = ii; kk < word.length(); kk++) { //optimizable?
			right += word[kk];
		}
		for (unsigned int jj = 97; jj <= 122; jj++) {
			string newWord = left + char(jj) + right;
			if (trie->consultTrie(newWord) == 2) {
				foundWords.push_back(newWord);
				foundScore.push_back(calcPoints(newWord));
			}
		}
	}
	return 1; // ?
}

int _tmain(int argc, _TCHAR* argv[])
{
	const auto start = clock();
	/* INITIALIZATION OF VARIABLES */
	string boardstring, hash, line;

	/* Charge Trie, hash and auxiliar variable for board */
	getline (cin,boardstring);
	getline (cin,hash);
	while(!cin.eof()){
		getline (cin,line);
		trie->addWord(line);
	}
	
	/* Charge the letters into the board */
	for(unsigned int ii = 0; ii < 4; ii++){
		for(unsigned int jj = 0; jj < 4; jj++){
			board[ii][jj] = boardstring[4*ii + jj];
		}
	}

	//prueba a ver si detecta que vamos bien
	string word = "hell";
	//cout << trie->consultTrie(word) << endl;

	// prueba de checkear 2 nodos por debajo
	string prueba = "abg";
	trie->checkSecondNode(prueba);

	// ANE ESTA EN MODO DE PRUEBA ASI QUE EL INPUT ES input2.txt PORQUE SI NO ME MUERO 
	// SI VAS A HACER ALGO CON input1.txt CAMBIALO SIN PROBLEMAS PERO AVISAAAAAAAAAAAA
	
	//bool a = findWordsPlease("hell");
	for (int i = 0; i<foundWords.size(); i++){
		cout << foundWords[i] << endl;
	}
	cout << (clock()-start)/(float)CLOCKS_PER_SEC << "s" << endl; // tiempo en cargar el diccionario: 120ms
	delete trie;
	return 0;
}
