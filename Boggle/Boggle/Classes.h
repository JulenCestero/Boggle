#include "stdafx.h"

class Node {
public:
	Node(const char* letter);
  ~Node(){;}

	void setContent(char c) {mContent = c;}
	void setMarker(bool m) {mMarker = m;}
	void setChildren(vector<Node*> kids){mChildren = kids;}

	char content() {return mContent;}
	bool wordMarker() {return mMarker;}
	vector<Node*> children() {return mChildren;}

	Node* findChild(const char* c);
	//void appendChild(Node* child) {mChildren.push_back(child);}
	void appendChild(Node* child) {mChildren[child->content()-97] = child;}

private:
  char mContent;
  bool mMarker;
	vector<Node*> mChildren;	//optimizable, sabemos que como max tamaño = 26
};

class Trie {
public:
	Trie(){root = new Node(&mTmp);}
	~Trie(){;}
	void addDictionary();
  int consultTrie(const string* s);
	vector<char> getChildren(const string* s);
	vector<string> check2ndGen(const string* s, const char* sn);

private:
    Node* root;
    char mTmp = ' ';
};
