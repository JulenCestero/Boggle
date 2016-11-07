#include "stdafx.h"

class Node {
public:
	Node();
  ~Node(){;}

	void addWord(const char* word);

	void setContent(char c) {mContent = c;}
	void setMarker(bool m) {mMarker = m;}

	char content() {return mContent;}
	bool wordMarker() {return mMarker;}
	vector<Node*> children();
	vector<char> charkids();
	Node* findChild(const char* c);

private:
  char mContent;
  bool mMarker;
	Node* mChildren[26];

};

class Trie {
public:
	Trie(){char a = ' '; root = new Node();}
	~Trie(){;}

	Node* getRoot(){return root;}
	void addDictionary();
  int consultTrie(const string* s);
	int consultTrie2(Node* node);
	vector<char> getChildren(const string* s);
	vector<string> check2ndGen(const string* s, const char* sn);

private:
    Node* root;
};
