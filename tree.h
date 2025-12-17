#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct HorseNode {
    string nama;
    int tahunLahir;
    string keluarga;
    HorseNode* firstChild;   
    HorseNode* nextSibling;  
    HorseNode* parent;       
};

string toLower(string str);

HorseNode* createNode(const string& nama, int tahun, const string& keluarga);
void addChild(HorseNode* parent, HorseNode* child);
HorseNode* findHorse(HorseNode* root, const string& nama);
void printTree(HorseNode* root, int level = 0);

void updateHorse(HorseNode* node, string nama, int tahun);
void deleteHorse(HorseNode* &root, string nama);

HorseNode* crossBreed(HorseNode* p1, HorseNode* p2, string namaAnak, int tahunAnak, string namaKeluargaBaru);

void preOrder(HorseNode* root);
void inOrder(HorseNode* root);
void postOrder(HorseNode* root);

void showHighestNode(HorseNode* root);
void showLowestNode(HorseNode* root);

#endif