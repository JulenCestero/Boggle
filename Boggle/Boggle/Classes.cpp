#include "stdafx.h"
#include "Classes.h"

Node::Node(const char* letter)
{
  mContent = *letter;
  //Node* arr[26] = {NULL};
	mChildren.resize(26);
  //mChildren.assign(arr, arr + 26);
}

Node* Node::findChild(const char* c)
{
  if (mChildren[c[0] - 97] != NULL) return mChildren[c[0] - 97];
  else return NULL;
}

void Node::addWord(const char* word)
{
	const char idx = *word - 'a';
	if(!mChildren[idx]) mChildren[idx] = new Node(word);
	if(strlen(word) > 1) mChildren[idx]->addWord(word + 1);
	else mChildren[idx]->setMarker(true);
}

void Trie::addDictionary()
{
	string line;
	while(getline(cin, line)) {
		if(line.length() >= 3 && line.length() <= DIM*DIM + 1) 
			root->addWord(line.c_str());
  }
}


int Trie::consultTrie(const string* s)
{
  Node* current = root;
  for (size_t i = 0; i < s->length(); i++)
    current = current->findChild(&s->at(i));

  if (current->wordMarker()) {
    if (!current->children().empty()) return 3;
    else return 2;
  }
  else return 1;
}

vector<char> Trie::getChildren(const string* s)
{
  vector<char> kids;
  kids.resize(26);
  Node* current = root;
  for (size_t i = 0; i < s->length(); i++) {
    current = current->findChild(&s->at(i));
  }
	if(current != NULL){
		vector<Node*> childNodes = current->children();
		for (unsigned char i = 0; i < childNodes.size(); i++) {
			if (childNodes[i] != NULL) {
				kids[i] = i + 97;
			}
		}
	}
	else kids[0] = 'N';
	return kids;
}

vector<string> Trie::check2ndGen(const string* s, const char* sn)
{
  Node* current = root;
  vector<string> incompleteWords;
  for (size_t ii = 0; ii < s->length(); ii++) {
    current = current->findChild(&s->at(ii));
  }

  vector<Node*> FirstSons = current->children(), SecondNodes;
  for (unsigned char i = 0; i < FirstSons.size(); i++) {
    if (FirstSons[i] != NULL) {
      char aux = i + 97;
      if (sn[0] != ' ') {
        SecondNodes = FirstSons[i]->children();
        if (SecondNodes[sn[0] - 97] != NULL) incompleteWords.push_back(s[0] + aux + sn[0]);
      }
      else if (FirstSons[i]->wordMarker()) incompleteWords.push_back(s[0] + aux);
    }
  }

  return incompleteWords;
}