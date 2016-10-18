#include "stdafx.h"
#include "Classes.h"

Node* Node::findChild(char c)
{
  for(size_t i = 0; i < mChildren.size(); i++)
		if(mChildren.at(i)->content() == c) 
			return mChildren.at(i);
  return NULL;
}

void Trie::addDictionary(void)
{
	string line;
	Node* current;
	Node* child;
	Node* tmp;
	while(getline(cin,line)){
		if(line.size() >= 3 && line.size() <= DIM*DIM + 1){
			current = root;
			for(size_t i = 0; i < line.length(); i++){        
				child = current->findChild(line[i]);
				if(child != NULL) current = child;
				else{
					tmp = new Node();
					tmp->setContent(line[i]);
					current->appendChild(tmp);
					current = tmp;
				}
			}
			current->setMarker(true);
		}
	}
}

int Trie::consultTrie(string s)
{
  Node* current = root;
  for(size_t i = 0; i < s.length(); i++)
    current = current->findChild(s[i]);
  
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
  for(size_t i = 0; i < s.length(); i++)
    current = current->findChild(s[i]);
  
  vector<Node*> childNodes = current->children();
  for(size_t i = 0; i < childNodes.size(); i++)
		kids.push_back(childNodes[i]->content());

	return kids;
}

vector<string> Trie::check2ndGen(string s, char sn)
{
	Node* current = root;
	vector<string> incompleteWords;
	for(size_t ii = 0; ii < s.length(); ii++)
		current = current->findChild(s[ii]);

	vector<Node*> FirstSons = current->children(), SecondNodes;
	for(size_t i = 0; i < FirstSons.size(); i++){
		if(sn != ' '){
			SecondNodes = FirstSons[i]->children();
			for(size_t j = 0; j < SecondNodes.size(); j++)
				if(SecondNodes[j]->content() == sn) 
					incompleteWords.push_back(s + FirstSons[i]->content() + sn);
		}
		else if(FirstSons[i]->wordMarker()) incompleteWords.push_back(s + FirstSons[i]->content());
	}

	return incompleteWords;
}