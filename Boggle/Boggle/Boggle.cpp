// Boggle.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "Classes.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Trie* trie = new Trie();
  trie->addWord("Hello");
  trie->addWord("Balloon");
  trie->addWord("Ball");

  if (trie->searchWord("Hell"))
     cout << "Found Hell" << endl;

  if (trie->searchWord("Hello"))
      cout << "Found Hello" << endl;

  if (trie->searchWord("Helloo"))
      cout << "Found Helloo" << endl;

  if (trie->searchWord("Ball"))
      cout << "Found Ball" << endl;

  if (trie->searchWord("Balloon"))
      cout << "Found Balloon" << endl;

  delete trie;
	return 0;
}

