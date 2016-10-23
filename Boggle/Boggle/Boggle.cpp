// +
// Network Security 2016 - Boggle

// Important note: when cleaning the project for final submission delete all the content of
//                 Debug and Release directories BUT the libeay32MD.dll file.

#include "stdafx.h"
#include "Classes.h"

/* GLOBAL VARIABLES */
Trie* trie = new Trie();
static unsigned int letters[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };
char board[DIM][DIM];
bool visited[DIM][DIM];
unsigned int maxScore = 0;
vector<vector<string>> maxScoreWords;
vector<string> mixedWords;


string sha256(const string str)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	stringstream ss;
	for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
		ss << hex << setw(2) << setfill('0') << (int)hash[i];
	return ss.str();
}

bool mixWords(string word, string hash)
{
  string bin, aux, auxHash;
  for (size_t ii = 0; ii < pow(2, word.length()); ii++) {
    aux = word;
    bin = bitset<DIM*DIM+1>(ii).to_string();
    for(size_t jj = 0; jj < word.size(); jj++){
      if(bin[DIM*DIM - jj] == '1'){
        aux[jj] = word[jj] - 32;
			}
		}
    auxHash = sha256(aux);
    if(hash.compare(auxHash) == 0){
      cout << aux << endl;
      return 1;
    }
  }
  return 0;
}

void points(const string word)
{
  unsigned int letterPoints = 0, differentWords = 0, score;

  // Puntos por letra
  for(size_t ii = 0; ii < word.length(); ii++)
    letterPoints += letters[word[ii] - 97];

  // Puntos por longitud
  letterPoints += word.length() - 2; 

  // Puntos por entropía
  vector<char> aux;
  for(size_t ii = 0; ii < word.length(); ii++){
    if(find(aux.begin(), aux.end(), word[ii]) == aux.end()){
      aux.push_back(word[ii]);
      differentWords++;
    }
  }
  score = letterPoints + differentWords;
	if(score > maxScore){
		maxScore = score;
		maxScoreWords.push_back(vector<string>(NULL));
		maxScoreWords.back().push_back(word);
	}
	else if(score == maxScore){ 
		if(find(maxScoreWords.back().begin(), maxScoreWords.back().end(), word) == maxScoreWords.back().end()){
			maxScoreWords.back().push_back(word);
		}
	}
}

void findAllWords(int posx, int posy, string word, bool flag)
{
  vector<char> children = trie->getChildren(word);
  if(!children.empty()){
    visited[posx][posy] = true;
    for(int a1 = posx - 1; a1 < posx + 2; a1++){
      for(int a2 = posy - 1; a2 < posy + 2; a2++){
        if(!visited[a1][a2] && a1 >= 0 && a1<DIM && a2 >= 0 && a2<DIM){
					if(find(children.begin(), children.end(), board[a1][a2]) != children.end()){
						string auxword(word + board[a1][a2]);
            if(auxword.length() < 3) findAllWords(a1, a2, auxword, flag);
            else{
              unsigned int consult = trie->consultTrie(auxword);
              if(consult != 1) points(auxword);
              if(consult != 2) findAllWords(a1, a2, auxword, flag);
            }
					}
					else if(!flag){
						vector<string> finalWords = trie->check2ndGen(word,' ');
						for(size_t i = 0; i<finalWords.size(); i++)
							points(finalWords[i]);
						vector<string> incompleteWords = trie->check2ndGen(word, board[a1][a2]);
						for(size_t i = 0; i < incompleteWords.size(); i++)
							findAllWords(a1, a2, incompleteWords.at(i), 1);
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
  string boardstring, hash;
  getline(cin, boardstring);
  getline(cin, hash);
  trie->addDictionary();

  /* Charge the letters into the board */
  for(int ii = 0; ii < DIM; ii++){
    for(int jj = 0; jj < DIM; jj++){
      board[ii][jj] = boardstring[DIM * ii + jj];
      visited[ii][jj] = false;
    }
  }

  /* Find words in board */
  vector<string> incompleteWords;
  for(unsigned int ii = 0; ii < DIM; ii++){
    for(unsigned int jj = 0; jj < DIM; jj++){
      incompleteWords = trie->check2ndGen("", board[ii][jj]);
      for(size_t a = 0; a < incompleteWords.size(); a++)
        findAllWords(ii, jj, incompleteWords[a], 1);
      string boardLetter(1, board[ii][jj]);
      findAllWords(ii, jj, boardLetter, 0);
    }
  }

	/* Search combinations of the words with maximum score and hash creation */
  for(size_t i = 0; i < maxScoreWords.back().size(); i++){
    //cout << maxScoreWords.back().at(i) << " with " << maxScore << " points" << endl;
    if(mixWords(maxScoreWords.back().at(i), hash)) break;
  }

  cout << (clock()-start)/(float)(CLOCKS_PER_SEC) << endl;
  delete trie;
  return 0;
}
