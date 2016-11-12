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
	Node* getLastNode(const string* s);
  int consultTrie(Node* current);
	vector<char> getChildren(Node* current);
	vector<string> check2ndGen(Node* current, const string* s, const char* sn);

private:
    Node* root;
};
