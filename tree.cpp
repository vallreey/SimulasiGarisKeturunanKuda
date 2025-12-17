#include "tree.h"

string toLower(string str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

HorseNode* createNode(const string& nama, int tahun, const string& keluarga) {
    HorseNode* newNode = new HorseNode;
    newNode->nama = nama;
    newNode->tahunLahir = tahun;
    newNode->keluarga = keluarga;
    newNode->firstChild = nullptr;
    newNode->nextSibling = nullptr;
    newNode->parent = nullptr;
    return newNode;
}

void addChild(HorseNode* parent, HorseNode* child) {
    if (parent == nullptr || child == nullptr) return;

    child->parent = parent;
    if (parent->firstChild == nullptr) {
        parent->firstChild = child;
    } else {
        HorseNode* temp = parent->firstChild;
        while (temp->nextSibling != nullptr) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
    }
}

HorseNode* findHorse(HorseNode* root, const string& nama) {
    if (root == nullptr) return nullptr;
    
    if (toLower(root->nama) == toLower(nama)) return root;

    HorseNode* found = findHorse(root->firstChild, nama);
    if (found != nullptr) return found;

    return findHorse(root->nextSibling, nama);
}

void printTree(HorseNode* root, int level) {
    if (root == nullptr) return;
    for (int i = 0; i < level; i++) cout << "    ";
    cout << "|- " << root->nama << " (" << root->tahunLahir << ")" << endl;

    printTree(root->firstChild, level + 1);
    printTree(root->nextSibling, level);
}

void updateHorse(HorseNode* node, string nama, int tahun) {
    if (node != nullptr) {
        node->nama = nama;
        node->tahunLahir = tahun;
        cout << "Data kuda berhasil diperbarui!\n";
    }
}

void deleteNodeRecursive(HorseNode* node) {
    if (node == nullptr) return;
    deleteNodeRecursive(node->firstChild); 
    deleteNodeRecursive(node->nextSibling);
    delete node;
}

void deleteHorse(HorseNode* &root, string nama) {
    if (root == nullptr) return;

    if (toLower(root->nama) == toLower(nama)) {
        HorseNode* temp = root;
        root = nullptr; 
        temp->nextSibling = nullptr; 
        deleteNodeRecursive(temp);
        cout << "Root silsilah berhasil dihapus.\n";
        return;
    }

    HorseNode* target = findHorse(root, nama);
    if (target == nullptr) {
        cout << "Kuda tidak ditemukan di tree ini.\n";
        return;
    }

    HorseNode* parent = target->parent;

    if (parent != nullptr) {
        if (parent->firstChild == target) {
            parent->firstChild = target->nextSibling;
        } else {
            HorseNode* temp = parent->firstChild;
            while (temp != nullptr && temp->nextSibling != target) {
                temp = temp->nextSibling;
            }
            if (temp != nullptr) {
                temp->nextSibling = target->nextSibling;
            }
        }
    }

    target->nextSibling = nullptr; 
    target->parent = nullptr;

    deleteNodeRecursive(target);
    cout << "Kuda " << nama << " dan keturunannya berhasil dihapus.\n";
}

HorseNode* crossBreed(HorseNode* p1, HorseNode* p2, string namaAnak, int tahunAnak, string namaKeluargaBaru) {
    if (p1 == nullptr || p2 == nullptr) return nullptr;

    HorseNode* newLineage = createNode(namaAnak, tahunAnak, namaKeluargaBaru);
    cout << "Perkawinan silang sukses! Tree baru terbentuk: " << namaKeluargaBaru << endl;
    return newLineage;
}

void preOrder(HorseNode* root) {
    if (root == nullptr) return;
    cout << root->nama << " ";
    preOrder(root->firstChild);
    preOrder(root->nextSibling);
}

void inOrder(HorseNode* root) {
    if (root == nullptr) return;
    inOrder(root->firstChild);
    cout << root->nama << " ";
    inOrder(root->nextSibling);
}

void postOrder(HorseNode* root) {
    if (root == nullptr) return;
    postOrder(root->firstChild);
    postOrder(root->nextSibling);
    cout << root->nama << " ";
}

void showHighestNode(HorseNode* root) {
    if (root == nullptr) {
        cout << "Tree kosong, tidak ada leluhur.\n";
        return;
    }
    cout << "=== NODE TERTINGGI (Leluhur) ===\n";
    cout << "Nama       : " << root->nama << endl;
    cout << "Tahun      : " << root->tahunLahir << endl;
    cout << "Posisi     : Generasi Awal\n";
    cout << "Penjelasan : Ini adalah kuda pertama yang memulai silsilah keluarga " << root->keluarga << ".\n";
    cout << "--------------------------------\n";
}

void findDeepestNode(HorseNode* node, int level, int* maxLevel, HorseNode** deepestNode) {
    if (node == nullptr) return;

    if (level > *maxLevel) {
        *maxLevel = level;
        *deepestNode = node;
    }

    findDeepestNode(node->firstChild, level + 1, maxLevel, deepestNode);
    findDeepestNode(node->nextSibling, level, maxLevel, deepestNode);
}

void showLowestNode(HorseNode* root) {
    if (root == nullptr) return;

    int maxLevel = -1;
    HorseNode* deepestNode = nullptr;

    findDeepestNode(root, 0, &maxLevel, &deepestNode);

    if (deepestNode != nullptr) {
        cout << "=== NODE TERENDAH (Keturunan Terjauh) ===\n";
        cout << "Nama       : " << deepestNode->nama << endl;
        cout << "Tahun      : " << deepestNode->tahunLahir << endl;
        cout << "Posisi     : Generasi ke-" << maxLevel << endl;
        cout << "Penjelasan : Kuda ini berada pada lapisan terbawah tree, memiliki jarak " 
             << maxLevel << " turunan dari leluhur utama.\n";
        cout << "--------------------------------\n";
    }
}