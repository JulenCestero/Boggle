// Boggle.cpp: define el punto de entrada de la aplicación de consola.
//
#include <cstdio>
#include "stdafx.h"
#include "Classes.h"


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
	vector<string> words;

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
