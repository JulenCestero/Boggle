#include "stdafx.h"
#include "Classes.h"

Node::Node()
{
  fill_n(mChildren,26,nullptr);
}

Node* Node::findChild(const char* c)
{
  return mChildren[c[0] - 97];
}

vector<Node*> Node::children(){
	vector<Node*> kids(26);
	for(size_t i = 0; i<26; ++i){
		kids[i] = mChildren[i];
	}
	return kids;
}

vector<char> Node::charkids(){
	vector<char> kids(26);
	for(size_t i = 0; i<26; ++i){
		if(mChildren[i] != NULL)
			kids[i] = i + 'a';
	}
	return kids;
}

void Node::addWord(const char* word)
{
  auto aux = *word;
  const char idx = aux - 'a';
  if(aux != '\n'){  
    if(!mChildren[idx]) mChildren[idx] = new Node();
    mChildren[idx]->addWord(word + 1);
  }
  else mMarker = true;
}

Node* Trie::getLastNode(const string* s){
	Node* current = root;
  for(size_t i = 0; i < s->length(); i++){
    current = current->findChild(&s->at(i));
	}
	return current;
}

int Trie::consultTrie(Node* current)
{
  if(current->wordMarker()){
    if(!current->children().empty()) return 3;
    else return 2;
  }
  else return 1;
}

vector<char> Trie::getChildren(Node* current)
{
  vector<char> kids(26);
	if(current != NULL){
		vector<Node*> childNodes = current->children();
		for(unsigned char i = 0; i < childNodes.size(); ++i){
			if(childNodes[i] != NULL){
				kids[i] = i + 97;
			}
		}
	}
	else kids[0] = 'N';
	return kids;
}

vector<string> Trie::check2ndGen(Node* current, const string* s, const char* sn)
{
  vector<string> incompleteWords;
  vector<Node*> FirstSons = current->children(), SecondNodes;
	char aux;
  for(size_t i = 0; i < FirstSons.size(); ++i){
    if(FirstSons[i] != NULL){
      aux = i + 97;
      if(sn[0] != ' '){
        SecondNodes = FirstSons[i]->children();
        if(SecondNodes[sn[0] - 97] != NULL) incompleteWords.push_back(s[0] + aux + sn[0]);
      }
      else if(FirstSons[i]->wordMarker()) incompleteWords.push_back(s[0] + aux);
    }
  }
  return incompleteWords;
}