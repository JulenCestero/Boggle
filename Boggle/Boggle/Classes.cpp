#include "stdafx.h"
#include "Classes.h"

Node::Node(const char* letter)
{
  mContent = *letter;
  fill_n(mChildren,26,nullptr);
}

Node* Node::findChild(const char* c)
{
  if (mChildren[c[0] - 97] != NULL) return mChildren[c[0] - 97];
  else return NULL;
}

vector<Node*> Node::children(){
	vector<Node*> kids(26);
	for(size_t i = 0; i<26; ++i){
		kids[i] = mChildren[i];
	}
	return kids;
}

void Node::addWord(const char* word)
{
  auto aux = *word;
  const char idx = aux - 'a';
  if (aux != '\n') {  
    if (!mChildren[idx]) mChildren[idx] = new Node(word);
    mChildren[idx]->addWord(word + 1);
  }
  else mMarker = true;
}

void Trie::addDictionary()
{
  char buffer[80];
  char* result;
  while ((result = fgets(buffer, 80, stdin)) != NULL) {
    root->addWord(result);
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
  for (size_t i = 0; i < s->length(); ++i) {
    current = current->findChild(&s->at(i));
  }
	if(current != NULL){
		vector<Node*> childNodes = current->children();
		for (unsigned char i = 0; i < childNodes.size(); ++i) {
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
  for (size_t ii = 0; ii < s->length(); ++ii) {
    current = current->findChild(&s->at(ii));
  }

  vector<Node*> FirstSons = current->children(), SecondNodes;
  for (unsigned char i = 0; i < FirstSons.size(); ++i) {
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