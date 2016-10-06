#include "stdafx.h"

class Node {
public:
    Node() { mContent = ' '; mMarker = false; }
    ~Node() {}
    char content() {return mContent;}
    void setContent(char c) {mContent = c;}
    bool wordMarker() {return mMarker;}
		//bool NodeEnd() {return endNode;}
    void setWordMarker() {mMarker = true;}
		//void setEndNode() {endNode = true;}
    Node* findChild(char c);
    void appendChild(Node* child) {
			mChildren.push_back(child); 
			//endNode = false;
		}
    vector<Node*> children() {return mChildren;}

private:
    char mContent;
    bool mMarker;
		//bool endNode;
    vector<Node*> mChildren;
};

class Trie {
public:
    Trie();
    ~Trie();
    void addWord(string s);
    int consultTrie(string s);
		bool check2ndGen(string s, char sn);
		vector<char> getChildren(string s);
private:
    Node* root;
};
