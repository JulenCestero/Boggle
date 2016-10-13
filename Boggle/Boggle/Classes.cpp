#include "stdafx.h"
#include "Classes.h"

Node* Node::findChild(char c)
{
    for(size_t i = 0; i < mChildren.size(); i++){
			Node* tmp = mChildren.at(i);
			if(tmp->content() == c) return tmp;
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
	//maxCommonNode = root;
	//maxCommonChars = 0;
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
  for(size_t i = 0; i < s.length(); i++){        
    Node* child = current->findChild(s[i]);
    if(child != NULL) current = child;
    else{
			Node* tmp = new Node();
      tmp->setContent(s[i]);
      current->appendChild(tmp);
      current = tmp;
    }
	}
	current->setMarker(true);
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
  Node* tmp;
  for(size_t i = 0; i < s.length(); i++){
    tmp = current->findChild(s[i]);
    current = tmp;
  }
  if(current->wordMarker()){
		vector<Node*> children = current->children();
		if(children.size() != 0) return 3;
		else return 2;
	} 
  else return 1;
}

vector<char> Trie::getChildren(string s)
{
  vector<char> kids;
  Node* current = root;
  for(size_t i = 0; i < s.length(); i++) {
    Node* tmp = current->findChild(s[i]);
    current = tmp;
  }
  vector<Node*> childNodes = current->children();
  for(size_t i = 0; i < childNodes.size(); i++){
		kids.push_back(childNodes[i]->content());
	}
	return kids;
}

vector<string> Trie::check2ndGen(string s, char sn)
{
	Node* tmp;
	Node* current = root;
	vector<string> incompleteWords;
	for(size_t ii = 0; ii < s.length(); ii++){
		tmp = current->findChild(s[ii]);					// se puede poner current = current->findChild(s[ii]);	???????????????????????????
		current = tmp;
	}
	vector<Node*> FirstSons = current->children(), SecondNodes;
	for(size_t i = 0; i < FirstSons.size(); i++){
		SecondNodes = FirstSons[i]->children();
		for(size_t j = 0; j < SecondNodes.size(); j++)
			if(SecondNodes[j]->content() == sn) 
				incompleteWords.push_back(s + FirstSons[i]->content() + sn);
	}
	return incompleteWords;
}