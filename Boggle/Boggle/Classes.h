#include "stdafx.h"

class Node {
public:
  Node() {mContent = ' '; mMarker = false;}
  ~Node(){;}

	void setContent(char c) {mContent = c;}
	void setMarker(bool m) {mMarker = m;}
	void setChildren(vector<Node*> kids){mChildren = kids;}

	char content() {return mContent;}
	bool wordMarker() {return mMarker;}
	vector<Node*> children() {return mChildren;}

	Node* findChild(char c);
	void appendChild(Node* child) {mChildren.push_back(child);}

private:
  char mContent;
  bool mMarker;
	vector<Node*> mChildren;	//optimizable, sabemos que como max tamaño = 26
	//array<Node*, 26> mChildren;
};

class Trie {
public:
	Trie(){root = new Node();}
	~Trie(){;}
	void addDictionary();
  int consultTrie(string s);
	vector<char> getChildren(string s);
	vector<string> check2ndGen(string s, char sn);

private:
    Node* root;
};
