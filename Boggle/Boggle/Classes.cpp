#include "stdafx.h"
#include "Classes.h"

Node::Node(char letter)
{
	mContent = letter; 
	mMarker = false; 
	Node* arr[26] = {NULL};
	mChildren.assign(arr,arr+26);
}

Node* Node::findChild(const char* c)
{
	if (mChildren[c[0] - 97] != NULL) return mChildren[c[0] - 97];
	else return NULL;
  /*for(size_t i = 0; i < mChildren.size(); i++)
		if(mChildren.at(i)->content() == c) 
			return mChildren.at(i);
  return NULL;*/
}

void Trie::addDictionary()
{
	string line;
  vector<string> dictionary;
	while(getline(cin,line)){
		int len = line.length();
		if(len >= 3 && len <= DIM*DIM + 1){
			Node* current = root;
			for(int i = 0; i < len; i++){        
				Node* child = current->findChild(&line[i]);
				if(child != NULL) current = child;
				else{
					Node* tmp = new Node(line[i]);
					current->appendChild(tmp);
					current = tmp;
				}
			}
			current->setMarker(true);
		}
	}
}

int Trie::consultTrie(const string* s)
{
  Node* current = root;
  for(size_t i = 0; i < s->length(); i++)
    current = current->findChild(&s->at(i));
  
  if(current->wordMarker()){
		if(!current->children().empty()) return 3;
		else return 2;
	} 
  else return 1;
}

vector<char> Trie::getChildren(const string* s)
{
	vector<char> kids;
	kids.resize(26);
  Node* current = root;
  for(size_t i = 0; i < s->length(); i++){
    current = current->findChild(&s->at(i));
	}
  vector<Node*> childNodes = current->children();
  for(size_t i = 0; i < childNodes.size(); i++){
		if(childNodes[i] != NULL){
			kids[i] = i + 97;
		}
	}
	return kids;
}

vector<string> Trie::check2ndGen(const string* s, const char* sn)
{
	Node* current = root;
	vector<string> incompleteWords;
	for(size_t ii = 0; ii < s->length(); ii++){
		current = current->findChild(&s->at(ii));
	}

	vector<Node*> FirstSons = current->children(), SecondNodes;
	for(size_t i = 0; i < FirstSons.size(); i++){
		if( FirstSons[i] != NULL){
			char aux = i + 97;
			if(sn[0] != ' '){
				SecondNodes = FirstSons[i]->children();
				/*for(size_t j = 0; j < SecondNodes.size(); j++){					// optimizable ??????????????????
					if(SecondNodes[j]->content() == sn){
						incompleteWords.push_back(s + FirstSons[i]->content() + sn);
					}
				}*/
				if(SecondNodes[sn[0] - 97] != NULL) incompleteWords.push_back(s[0] + aux + sn[0]);
			}
			else if(FirstSons[i]->wordMarker()) incompleteWords.push_back(s[0] + aux);
		}
	}

	return incompleteWords;
}