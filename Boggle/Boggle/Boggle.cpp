// +
// Network Security 2016 - Project template

// Important note: when cleaning the project for final submission delete all the content of
//                 Debug and Release directories BUT the libeay32MD.dll file.

// Boggle.cpp: define el punto de partida entre el punto de divergencia del 1% y la distopía apocalíptica
//
#include "stdafx.h"
#include "Classes.h"
//#include </openssl/rand.h> // dummy example to illustrate the use of OpenSSL

/* GLOBAL VARIABLES */
Trie* trie = new Trie();
static unsigned int letters[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };
char board[DIM][DIM];
bool visited[DIM][DIM];
unsigned int maxScore = 0;
vector<vector<string>> maxScoreWords;
vector<string> mixedWords;

void mixWords(string word)
{
  string bin, aux;
  double len = word.length();
  double max = pow(2, len);
  /*bin = bitset<DIM*DIM+1>(max).to_string();
  for(int i = 0; i<DIM*DIM+1; i++){
  if(bin[i] == '0'){
  const int bits = len - (i + 1);
  }
  }*/
  for (size_t ii = 0; ii < max; ii++) {
    aux = word;
    bin = bitset<DIM*DIM + 1>(ii).to_string();
    for (size_t jj = 0; jj < word.length(); jj++) {		//optimizable con find y subtract/erase ???????????????????????????????????
      if (bin[64 - jj] == '1') {
        aux[jj] = word[word.length() - jj] - 32;
      }
    }
    // aquí iría el hash
  }
}

/*
* Function to calculate the points of a word
*/
int calcPoints(const string word)
{
  int totalPoints = 0;
  int differentWords = 0;
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
*
bool findWordsPlease(string word)
{
for(size_t ii = 0; ii <= word.length(); ii++) {	// empezando desde 0 hasta <= wordlength se puede no hacer el for de arriba
string left = "";
string right = "";
for(size_t jj = 0; jj < ii; jj++) { //optimizable?
left += word[jj];
}
for(size_t kk = ii; kk < word.length(); kk++) { //optimizable?
right += word[kk];
}
for(int jj = 97; jj <= 122; jj++) {
string newWord = left + char(jj) + right;
if (trie->consultTrie(newWord) == 2) {
foundWords.push_back(newWord);
foundScore.push_back(calcPoints(newWord));
}
}
}
return 1;
}*/


void findWord(int posx, int posy, string word)
{
  vector<char> children = trie->getChildren(word);
  if (!children.empty()) {
    int possiblePositions[2][8], possiblesize = 0;
    char possibleValues[8];
    visited[posx][posy] = true;

    for (int a1 = posx - 1; a1 < posx + 2; a1++) {
      for (int a2 = posy - 1; a2 < posy + 2; a2++) {
        if (!visited[a1][a2] && a1 >= 0 && a1<DIM && a2 >= 0 && a2<DIM) {
          possibleValues[possiblesize] = board[a1][a2];
          possiblePositions[0][++possiblesize - 1] = a1;
          possiblePositions[1][possiblesize - 1] = a2;
        }
      }
    }

    for (int ii = 0; ii < possiblesize; ii++) {
      if (find(children.begin(), children.end(), possibleValues[ii]) != children.end()) {
        string auxword(word + possibleValues[ii]);
        int consult = trie->consultTrie(auxword);
        if (consult != 1 && auxword.size() >= 3) {
          unsigned int score = calcPoints(auxword);
          if (score > maxScore) { // TODO CORREGIR!!
            maxScore = score;
            maxScoreWords.push_back(vector<string>(NULL));
            maxScoreWords.back().push_back(auxword);
          }
          else if (score == maxScore) {
            maxScoreWords.back().push_back(auxword);
          }
        }
        if (consult != 2) findWord(possiblePositions[0][ii], possiblePositions[1][ii], auxword);
      }
    }
    visited[posx][posy] = false;
  }
}

void findAllWords(int posx, int posy, string word, bool flag)
{
  /*if(word == "unsavor"){
  cout << "found unsavor!" << endl;
  }*/
  int possiblePositions[2][8], possiblesize = 0;
  char possibleValues[8];
  visited[posx][posy] = true;

  for (int a1 = posx - 1; a1 < posx + 2; a1++) {
    for (int a2 = posy - 1; a2 < posy + 2; a2++) {
      if (!visited[a1][a2] && a1 >= 0 && a1<DIM && a2 >= 0 && a2<DIM) {
        possibleValues[possiblesize] = board[a1][a2];
        possiblePositions[0][++possiblesize - 1] = a1;
        possiblePositions[1][possiblesize - 1] = a2;
      }
    }
  }
  if (!flag) {
    for (int jj = 0; jj < possiblesize; jj++) {
      vector<string> incompleteWords = trie->check2ndGen(word, board[possiblePositions[0][jj]][possiblePositions[1][jj]]);
      for (size_t i = 0; i < incompleteWords.size(); i++) {
        findWord(possiblePositions[0][jj], possiblePositions[1][jj], incompleteWords.at(i));	// findWord normal function
      }
    }
  }
  vector<char> children = trie->getChildren(word);
  if (!children.empty()) {
    for (int ii = 0; ii < possiblesize; ii++) {
      if (find(children.begin(), children.end(), possibleValues[ii]) != children.end()) {
        string auxword(word + possibleValues[ii]);
        int consult = trie->consultTrie(auxword);
        if (consult == 2 && auxword.size() >= 3) {
          unsigned int score = calcPoints(auxword);
          if (score > maxScore) {
            if (find(maxScoreWords.back().begin(), maxScoreWords.back().end(), auxword) == maxScoreWords.back().end()) {
              maxScore = score;
              maxScoreWords.push_back(vector<string>(NULL));
              maxScoreWords.back().push_back(auxword);
            }
          }
          else if (score == maxScore) {
            if (find(maxScoreWords.back().begin(), maxScoreWords.back().end(), auxword) == maxScoreWords.back().end()) {
              maxScoreWords.back().push_back(auxword);
            }
          }
        }
        else findAllWords(possiblePositions[0][ii], possiblePositions[1][ii], auxword, flag);
      }
      else {
        vector<string> finalWords = trie->check2ndGen(word, ' ');
        for (size_t i = 0; i<finalWords.size(); i++) {
          unsigned int score = calcPoints(finalWords[i]);
          if (finalWords[i].size() >= 3 && score >= maxScore) {
            if (score > maxScore) maxScoreWords.push_back(vector<string>(NULL));
            if (find(maxScoreWords.back().begin(), maxScoreWords.back().end(), finalWords[i]) == maxScoreWords.back().end()) {
              maxScore = score;
              maxScoreWords.back().push_back(finalWords[i]);
            }
          }
        }
      }
    }
    visited[posx][posy] = false;
  }
}


int _tmain(int argc, _TCHAR* argv[])
{
  /* Charge Trie, hash and auxiliar variable for board */
  const auto start = clock();
  string boardstring, hash, line;
  getline(cin, boardstring);
  getline(cin, hash);
  trie->addDictionary();

  /* Charge the letters into the board */
  for (int ii = 0; ii < DIM; ii++) {
    for (int jj = 0; jj < DIM; jj++) {
      board[ii][jj] = boardstring[DIM * ii + jj];
      visited[ii][jj] = false;
    }
  }
  /* Find words in board */
  vector<string> incompleteWords;
  for (int ii = 0; ii < DIM; ii++) {
    for (int jj = 0; jj < DIM; jj++) {
      incompleteWords = trie->check2ndGen("", board[ii][jj]);
      for (int a = 0; a<incompleteWords.size(); a++) {
        findWord(ii, jj, incompleteWords[a]);
      }
      string boardLetter(1, board[ii][jj]);
      findAllWords(ii, jj, boardLetter, 0);
    }
  }

  for (size_t i = 0; i < maxScoreWords.back().size(); i++)
    cout << maxScoreWords.back().at(i) << " with " << maxScore << " points" << endl;

  mixWords("grazers");  //DA PROBLEMAS DE OUT OF RANGE





  // OpenSSL random example (delete for final project!)
  //unsigned long long rnd;
  //RAND_bytes((unsigned char*)&rnd, sizeof(rnd));
  //cout << rnd << endl;
  // End of OpenSSL example

  cout << (clock() - start) / (float)(CLOCKS_PER_SEC) << endl; // comment out this line for final submission
  delete trie;
	return 0;
}

