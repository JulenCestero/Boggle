#include "stdafx.h"
#include "Classes.h"

Node* Node::findChild(char c)
{
    for (unsigned int i = 0; i < mChildren.size(); i++){
			Node* tmp = mChildren.at(i);
			if (tmp->content() == c) return tmp;
    }
    return NULL;
}

Trie::Trie()
{
   root = new Node();
}

Trie::~Trie()
{
   // Free memory
}

void Trie::addWord(string s)
{
  Node* current = root;
  for(unsigned int i = 0; i < s.length(); i++){        
    Node* child = current->findChild(s[i]);
    if (child != NULL){
      current = child;
    }else{
			Node* tmp = new Node();
			tmp->setContent(s[i]);
			current->appendChild(tmp);
			//tmp->setEndNode();
			current = tmp;
    }
    if (i == s.length() - 1) current->setWordMarker();
  }
}


int Trie::consultTrie(string s)
{
  Node* current = root;
  while (current != NULL){
    for (unsigned int i = 0; i < s.length(); i++) {
      Node* tmp = current->findChild(s[i]);
      if (tmp == NULL) return 0;
      current = tmp;
    }
    if (current->wordMarker()){
			string alphabet = "abcdefghijklmnopqrstuvwxyz";
			for(unsigned int i = 0; i < 26; i++){
				if(current->findChild(alphabet[i]) != NULL){ 
					// our string exists and it's a word, but there are longer words
					return 3;
				}
			}
			return 2;
		}
    else return 1;
  }
	return 0;
}

vector<char> Trie::getChildren(string s)
{
	vector<char> kids;
	Node* current = root;
	int cont = 0;
  for (unsigned int i = 0; i < s.length(); i++) {
    Node* tmp = current->findChild(s[i]);
		if(tmp == NULL){
			kids.push_back('\0');
			return kids;
		}
    current = tmp;
  }
	vector<Node*> childNodes = current->children();
	for(unsigned int i = 0; i<childNodes.size(); i++){
		kids.push_back(childNodes[i]->content());
	}
	return kids;
}

bool Trie::check2ndGen(string s, char sn)
{
	string root_ = "";
	Node* current = root;
	unsigned int cont = 0;
	while(cont < s.length()){
		root_ += s[cont];
		Node* tmp = current->findChild(s[cont]);
		current = tmp;
		cont++;
	}	// si tenemos string "helo", avanzamos en nodos hasta llegar al nodo "l". ahora miramos si la "o" esta 2 nodos por debajo
	vector<Node*> FirstNodes = current->children();
	for(unsigned int i = 0; i<FirstNodes.size(); i++){
		vector<Node*> SecondNodes = FirstNodes[i]->children();
		for(unsigned int j = 0; j<SecondNodes.size(); j++){
			if(SecondNodes[j]->content() == sn){		// if second node of our known letter from the string == our char
				string newstring = root_ + FirstNodes[i]->content() + sn;
				cout << newstring << endl;
			}
		}
	}
	return 0;
}