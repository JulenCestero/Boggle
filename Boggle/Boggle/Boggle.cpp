// Boggle.cpp: define el punto de partida entre el punto de divergencia del 1% y la distopía apocalíptica
//
#include "stdafx.h"
#include "Classes.h"

/* GLOBAL VARIABLES */

#define DIM 2
Trie* trie = new Trie();
static unsigned int letters[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
vector<string> foundWords;
vector<unsigned int> foundScore;
char board[DIM][DIM];
bool visited[DIM][DIM];

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
 *
 * Esta función devuelve un 1 o un 0 dependiendo de si ha encontrado una palabra o no (podemos hacer
 * que si encuentra varias, devuelva otro número, eso cambiaría el tipo de argumento de salida de
 * bool a int). Además de eso, cuando encuentre una palabra hará un push_back paralelo al vector
 * foundWords y foundScore donde se guardarán la palabra encontrada y su puntuación.
*/
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


void findWord(int posx, int posy, string word)
{
	vector<char> children = trie->getChildren(word);
	vector<char> possibleValues;
	int possiblePositions[2][8];
	bool neighbors[3][3];

	visited[posx][posy] = true;			//REMEMBER CHECK ALREADY VISITED CELLS!!!
	for(int a = 0; a < 3; a++){
		for(int b = 0; b < 3; b++){
			neighbors[a][b] = true;
		}
	}
	neighbors[1][1] = false;	// own position of our word

	if (posx == 0) neighbors[0][1] = false;
	else if (posx == DIM - 1) neighbors[2][1] = false;
	if (posy == 0) neighbors[1][0] = false;
	else if (posy == DIM - 1) neighbors[1][2] = false;
	neighbors [0][0] = neighbors[0][1] && neighbors[1][0];
	neighbors [0][2] = neighbors[0][1] && neighbors[1][2];
	neighbors [2][0] = neighbors[1][0] && neighbors[2][1];
	neighbors [2][2] = neighbors[2][1] && neighbors[1][2];

	for(int a = 0; a < 3; a++){
		for(int b = 0; b < 3; b++){
			if(visited[posx - 1 + a][posy - 1 + b]) neighbors[a][b] = false;
		}	
	}

	for(int i1 = 0; i1 < 3; i1++){
		for(int i2 = 0; i2 < 3; i2++){
			if(neighbors[i1][i2]){
				possibleValues.push_back(board[posx-1+i1][posy-1+i2]);
				possiblePositions[0][possibleValues.size()-1] = posx-1+i1;
				possiblePositions[1][possibleValues.size()-1] = posy-1+i2;
			}
		}
	}

	for(unsigned int i1 = 0; i1<possibleValues.size(); i1++){
		string auxword = word;
		if(find(children.begin(), children.end(), possibleValues[i1]) != children.end()){		// uno de los puntos alrededor de nuestro punto existe en el trie
			auxword += possibleValues[i1];
			int consult = trie->consultTrie(auxword);
			if(consult != 1){		// the word finishes here or exists and continues
				foundWords.push_back(auxword);
			} 
			if(consult != 2){	// the word doesn't end here and continues
				findWord(possiblePositions[0][i1],possiblePositions[1][i1],auxword);
			}
		}
	}
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
	for(unsigned int ii = 0; ii < DIM; ii++){
		for(unsigned int jj = 0; jj < DIM; jj++){
			board[ii][jj] = boardstring[DIM*ii + jj];
			visited[ii][jj] = false;
		}
	}

	/*for(int ii = 0; ii < DIM; ii++){
		for(int jj = 0; jj < DIM; jj++){
			string word(1,board[ii][jj]);
			findWord(ii,jj, word);
		}
	}*/

	string word(1,board[0][0]);
	findWord(0,0, word);
	// ANE ESTA EN MODO DE PRUEBA ASI QUE EL INPUT ES input2.txt PORQUE SI NO ME MUERO 
	// SI VAS A HACER ALGO CON input1.txt CAMBIALO SIN PROBLEMAS PERO AVISAAAAAAAAAAAA
	
	for (unsigned int i = 0; i<foundWords.size(); i++){
		cout << foundWords[i] << endl;
	}

	cout << (clock()-start)/(float)CLOCKS_PER_SEC << "s" << endl; // tiempo en cargar el diccionario: 120ms
	return 0;
}
