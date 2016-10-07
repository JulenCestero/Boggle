// Boggle.cpp: define el punto de partida entre el punto de divergencia del 1% y la distopía apocalíptica
//
#include "stdafx.h"
#include "Classes.h"

/* GLOBAL VARIABLES */
#define DIM 4
Trie* trie = new Trie();
static unsigned int letters[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char board[DIM][DIM];
bool visited[DIM][DIM];
vector<string> foundWords;
vector<unsigned int> foundScore;
string maxScoreWord;
unsigned int maxScore = 0;

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
	return 1;
}


void findWord(int posx, int posy, string word)
{
	vector<char> children = trie->getChildren(word);
	vector<char> possibleValues;
	int possiblePositions[2][8];
	visited[posx][posy] = true;	

	for(int a1 = posx - 1; a1 < posx + 2; a1++){
		for(int a2 = posy - 1; a2 < posy + 2; a2++){
			if(!visited[a1][a2] && a1 >= 0 && a2 >= 0 && a1 < DIM && a2 < DIM){
				possibleValues.push_back(board[a1][a2]);
				possiblePositions[0][possibleValues.size() - 1] = a1;
				possiblePositions[1][possibleValues.size() - 1] = a2;
			}
		}
	}

	for(unsigned int ii = 0; ii < possibleValues.size(); ii++){
		if(find(children.begin(), children.end(), possibleValues[ii]) != children.end()){		// uno de los puntos alrededor de nuestro punto existe en el trie
			string auxword = word + possibleValues[ii];
			int consult = trie->consultTrie(auxword);
			if(consult != 1){		// the word finishes here or exists and continues
				if(auxword.size() >= 3 && !(find(foundWords.begin(), foundWords.end(), auxword) != foundWords.end()))
					foundWords.push_back(auxword);
					unsigned int score = calcPoints(auxword);
					foundScore.push_back(score);
					if(score > maxScore){
						maxScore = score;
						maxScoreWord = auxword;
					}
			} 
			if(consult != 2){	// the word doesn't end here and continues
				findWord(possiblePositions[0][ii],possiblePositions[1][ii],auxword);
			}
		}
	}
	visited[posx][posy] = false;
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
		if(line.size() > 2 && line.size() < DIM*DIM - 1) trie->addWord(line);
	} // tiempo en cargar el diccionario: 0.185s

	/* Charge the letters into the board */
	for(unsigned int ii = 0; ii < DIM; ii++){
		for(unsigned int jj = 0; jj < DIM; jj++){
			board[ii][jj] = boardstring[DIM*ii + jj];
			visited[ii][jj] = false;
		}
	} 

	const auto start1 = clock();
	cout << (clock()-start)/(float)CLOCKS_PER_SEC << "s" << endl;

	for(int ii = 0; ii < DIM; ii++){
		for(int jj = 0; jj < DIM; jj++){
			string boardLetter(1,board[ii][jj]);
			findWord(ii,jj, boardLetter);
		}
	}	//tiempo en encontrar palabras: 0.004s

	cout << maxScoreWord << " with " << maxScore << " points" << endl;

	/*cout << foundWords[maxpos] << endl;
	for (unsigned int i = 0; i<foundWords.size(); i++){
		cout << foundWords[i] << endl;
	}
	cout << foundWords.size() << endl;*/

	cout << (clock()-start1)/(float)CLOCKS_PER_SEC << "s" << endl; 
	return 0;
}
