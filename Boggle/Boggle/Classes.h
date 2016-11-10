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
	Trie(){root = new Node();}
	~Trie(){;}

	Node* getRoot(){return root;}
	int consultTrie(Node* current);
	vector<char> getChildren(Node* current);
	vector<string> Trie::check2ndGen(Node* current, const string* s, const char* sn);
	Node* getLastNode(const string* s);

private:
	Node* root;
};
