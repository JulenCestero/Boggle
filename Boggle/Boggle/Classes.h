#include "stdafx.h"

class Node {
public:
	Node(const char* letter);
  ~Node(){;}

	void addWord(const char* word);

	void setContent(char c) {mContent = c;}
	void setMarker(bool m) {mMarker = m;}

	char content() {return mContent;}
	bool wordMarker() {return mMarker;}
	vector<Node*> children();

	Node* findChild(const char* c);
	void appendChild(Node* child) {mChildren[child->content()-97] = child;}

private:
  char mContent;
  bool mMarker;
	//vector<Node*> mChildren;	//optimizable, sabemos que como max tamaño = 26
	Node* mChildren[26];

};

class Trie {
public:
	Trie(){char a = ' '; root = new Node(&a);}
	~Trie(){;}

	Node* getRoot(){return root;}
	void addDictionary();
  int consultTrie(const string* s);
	vector<char> getChildren(const string* s);
	vector<string> check2ndGen(const string* s, const char* sn);

private:
    Node* root;
};
