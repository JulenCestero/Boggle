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
    else
      return 1;
  }
}

bool Trie::checkSecondNode(string s){
	string root_ = "";
	Node* current = root;
	int cont = -1;
	while(cont < s.length() - 1){
		root_ += s[cont];
		Node* tmp = current->findChild(s[cont]);
		current = tmp;
		cont++;
	}	// si tenemos string "helo", avanzamos en nodos hasta llegar al nodo "l". ahora miramos si la "o" esta 2 nodos por debajo
	vector<Node*> FirstNodes = current->children();
	for(unsigned int i = 0; i<FirstNodes.size(); i++){
		vector<Node*> SecondNodes = FirstNodes[i]->children();
		for(unsigned int j = 0; j<SecondNodes.size(); j++){
			if(SecondNodes[j]->content() == s[s.length() - 1]){		// if second node of our known letter from the string == our last letter
				string newstring = root_ + FirstNodes[i]->content() + s[s.length() - 1];
				cout << newstring << endl;
			}
		}
	}
	return 0;
}