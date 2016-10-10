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

void Node::appendParent(Node* par)
{
	parent = new Node();
	parent = par;
}

Node* Node::getParent()
{
	return parent;
}

Trie::Trie()
{
	root = new Node(); 
	maxCommonNode = root;
	maxCommonChars = 0;
}

/*void Trie::addDictionary()
{
	string line, nextline;
	getline(cin,line);
	while(1){
		if(line.size() <= 2 || line.size() > DIM * DIM + 1){
			getline(cin,line);
			continue;
		}
		nextline = addWord(line);
		if(nextline != "") line = nextline;
		else break;
	} 
}*/

void Trie::addDictionary()
{
	string line;
	while(!cin.eof()){
		getline(cin,line);
		if(line.size() >= 3 && line.size() <= DIM*DIM + 1) addWord(line);
	}
}

void Trie::addWord(string s)
{
  Node* current = root;
  for (int i = 0; i < s.length(); i++){        
    Node* child = current->findChild(s[i]);
    if (child != NULL) current = child;
    else{
      Node* tmp = new Node();
      tmp->setContent(s[i]);
      current->appendChild(tmp);
      current = tmp;
    }
    if(i == s.length() - 1) current->setMarker(true);
}
}

/*
string Trie::addWord(string line)
{
	if(!cin.eof()){
		string nextline;
		int cont = 0, initialpos = maxCommonChars;
		Node* current = maxCommonNode;
		getline(cin, nextline);

		maxCommonNode = root;
		maxCommonChars = 0;
		while(1){
			if(line[cont] != nextline[cont]){
				maxCommonChars = cont;
				break;
			}
			cont++;
		}
		if(nextline.length()/2 < maxCommonChars && maxCommonChars < initialpos){	
			Node* aux = new Node();
			aux = current;
			for(int i = 0; i < initialpos - maxCommonChars; i++){
				if(aux == root) break;
				maxCommonNode = aux->getParent();
				aux = maxCommonNode;
			}
		}
		else{
			maxCommonNode = root;
			maxCommonChars = 0;
		}
		for(unsigned int i = initialpos; i < line.length(); i++){ 
			Node* child = current->findChild(line[i]);
			if(child != NULL) current = child; 
			else{
				Node* tmp = new Node();
				tmp->setContent(line[i]);
				current->appendChild(tmp);
				tmp->appendParent(current);
				current = tmp;
			}
			if(i + 1 == maxCommonChars) maxCommonNode = current;
		}
		current->setMarker(true);
		return nextline;
	}
	else{
		Node* current = root;		
		for(unsigned int i = maxCommonChars - 1; i < line.length(); i++){ 
			Node* child = current->findChild(line[i]);
			if(child != NULL) current = child; 
			else{
				Node* tmp = new Node();
				tmp->setContent(line[i]);
				current->appendChild(tmp);
				tmp->appendParent(current);
				current = tmp;
			}
		}
		current->setMarker(true);
		return "";
	} 
}*/


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