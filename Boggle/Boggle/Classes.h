#include "stdafx.h"

class Node {
public:
    Node() {mContent = ' '; mMarker = false;}
    ~Node(){;}

		void setContent(char c) {mContent = c;}
		void setMarker(bool m) {mMarker = m;}
		void setChildren(vector<Node*> kids){mChildren = kids;}
		void setParent(Node* par){parent = par;}

		char content() {return mContent;}
		bool wordMarker() {return mMarker;}

    Node* findChild(char c);
    void appendChild(Node* child) {mChildren.push_back(child);}
		void appendParent(Node* par);
		Node* getParent();
    vector<Node*> children() {return mChildren;}

private:
    char mContent;
    bool mMarker;
		vector<Node*> mChildren;
		Node* parent;
};

class Trie {
public:
		Trie();
		~Trie(){;}
		void addDictionary();
    string addWord(string s);
    int consultTrie(string s);
		vector<char> getChildren(string s);
		bool check2ndGen(string s, char sn);
private:
    Node* root;
		Node* maxCommonNode;
		int maxCommonChars;
};
