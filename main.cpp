#include <iostream>
#include "tree.h"

using namespace std;

const int MAX_TREES = 10; 

int main() {
    HorseNode* trees[MAX_TREES];
    for(int i=0; i<MAX_TREES; i++) trees[i] = nullptr;

    int menu;
    string nama, keluarga, akun, password;
    int tahun;
    string p1Name, p2Name, parentName;
    HorseNode *tempNode, *parent1, *parent2;

    //LOGIN
    do {
        cout << "\n=== LOGIN SISTEM PACUAN KUDA ===\n";
        cout << "1. Login\n2. Register\nPilihan: ";
        cin >> menu; cin.ignore();
        
        if (menu == 1) {
            cout << "Username: "; getline(cin, akun);
            cout << "Password: "; getline(cin, password);
            if(password == "123") cout << "Login Berhasil!\n";
            else cout << "Password Salah!\n";
        } else if (menu == 2) {
            cout << "Register User: "; getline(cin, akun);
            cout << "Set Password : "; getline(cin, password);
            password = "123"; 
            cout << "Akun dibuat. Masuk ke sistem...\n";
        }
    } while (password != "123");

    //MENU
    do {
        cout << "\n=== MANAJEMEN SILSILAH KUDA (MULTI-FAMILY) ===\n";
        cout << "1. Tambah Keluarga Baru\n";
        cout << "2. Tambah Anak Kuda\n";
        cout << "3. PERKAWINAN SILANG\n";
        cout << "4. Tampilkan Visual Semua Tree\n";
        cout << "5. Cari Data Kuda\n";
        cout << "6. Update Data Kuda\n";
        cout << "7. Hapus Kuda \n";
        cout << "8. Traversal \n";
        cout << "9. Lihat Node Tertinggi & Terendah \n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> menu; cin.ignore();

        switch(menu) {
            case 1:
                {
                    int slot = -1;
                    for(int i=0; i<MAX_TREES; i++) {
                        if(trees[i] == nullptr) { slot = i; break; }
                    }
                    if (slot != -1) {
                        cout << "Tree Slot " << slot+1 << " Kosong, Jadi Data Akan Dimasukan Pada Tree Tersebut!\n";
                        cout << "Nama Induk: "; getline(cin, nama);
                        int tahun;
                        while (true) {
                            cout << "Tahun Lahir : ";
                            cin >> tahun;

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cout << "Jangan masukkan huruf!" << endl;
                            } else {
                                cin.ignore();
                                break;
                            }
                        }
                        cout << "Keluarga: "; getline(cin, keluarga);
                        trees[slot] = createNode(nama, tahun, keluarga);
                    } else cout << "Slot Tree Penuh!\n";
                }
                break;

            case 2:
                cout << "Nama Induk : "; getline(cin, parentName);
                tempNode = nullptr;
                for(int i=0; i<MAX_TREES; i++) {
                    if(trees[i]) {
                        tempNode = findHorse(trees[i], parentName);
                        if(tempNode) break;
                    }
                }
                if (tempNode) {
                    cout << "Induk ditemukan: " << tempNode->nama << endl;
                    cout << "Nama Anak: "; getline(cin, nama);
                    cout << "Tahun Lahir : "; cin >> tahun; cin.ignore();
                    addChild(tempNode, createNode(nama, tahun, tempNode->keluarga));
                    cout << "Anak berhasil ditambahkan.\n";
                } else cout << "Induk tidak ditemukan.\n";
                break;

            case 3:
                cout << "Nama Kuda 1: "; getline(cin, p1Name);
                cout << "Nama Kuda 2: "; getline(cin, p2Name);
                parent1 = nullptr; parent2 = nullptr;

                for(int i=0; i<MAX_TREES; i++) {
                    if(trees[i]) {
                        if(!parent1) parent1 = findHorse(trees[i], p1Name);
                        if(!parent2) parent2 = findHorse(trees[i], p2Name);
                    }
                }

                if(parent1 && parent2) {
                    int slot = -1;
                    for(int i=0; i<MAX_TREES; i++) if(!trees[i]) { slot = i; break; }

                    if(slot != -1) {
                        cout << "Pasangan Valid.\n";
                        cout << "Nama Anak: "; getline(cin, nama);
                        cout << "Tahun Lahir : "; cin >> tahun; cin.ignore();
                        cout << "Nama Keluarga Baru : "; getline(cin, keluarga);
                        
                        trees[slot] = crossBreed(parent1, parent2, nama, tahun, keluarga);
                    } else cout << "Slot Tree Penuh. Hapus dulu yang lama.\n";
                } else cout << "Salah satu kuda tidak ditemukan.\n";
                break;

            case 4:
                for(int i=0; i<MAX_TREES; i++) {
                    if(trees[i]) {
                        cout << "\n--- Tree " << i+1 << ": Keluarga " << trees[i]->keluarga << " ---\n";
                        printTree(trees[i]);
                    }
                }
                break;

            case 5:
                cout << "Cari Nama Kuda : "; getline(cin, nama);
                tempNode = nullptr;
                for(int i=0; i<MAX_TREES; i++) {
                    if(trees[i]) {
                        tempNode = findHorse(trees[i], nama);
                        if(tempNode) {
                            cout << "Ditemukan Pada Tree " << i+1 << " (" << trees[i]->keluarga << ")\n";
                            cout << "Nama: " << tempNode->nama << " | Tahun Lahir: " << tempNode->tahunLahir << endl;
                            break;
                        }
                    }
                }
                if(!tempNode) cout << "Kuda tidak ditemukan.\n";
                break;

            case 6:
                cout << "Nama kuda yang diedit: "; getline(cin, nama);
                tempNode = nullptr;
                for(int i=0; i<MAX_TREES; i++) {
                    if(trees[i]) {
                        tempNode = findHorse(trees[i], nama);
                        if(tempNode) break;
                    }
                }
                if(tempNode) {
                    cout << "--- Edit Data (Keluarga Tetap) ---\n";
                    cout << "Nama : "; getline(cin, nama);
                    cout << "Tahun Lahir : "; cin >> tahun; cin.ignore();
                    updateHorse(tempNode, nama, tahun); 
                } else cout << "Kuda tidak ditemukan.\n";
                break;

            case 7:
                cout << "Nama kuda dihapus: "; getline(cin, nama);
                {
                    bool deleted = false;
                    for(int i=0; i<MAX_TREES; i++) {
                        if(trees[i]) {
                            if(toLower(trees[i]->nama) == toLower(nama)) {
                                deleteHorse(trees[i], nama); 
                                deleted = true; break;
                            } 
                            else if(findHorse(trees[i], nama)) {
                                deleteHorse(trees[i], nama);
                                deleted = true; break;
                            }
                        }
                    }
                    if(!deleted) cout << "Kuda tidak ditemukan.\n";
                }
                break;

            case 8:
                cout << "\n--- PILIH TREE UNTUK TRAVERSAL ---\n";
                {
                    bool exist = false;
                    for(int i=0; i<MAX_TREES; i++) {
                        if(trees[i]) {
                            cout << i+1 << ". Keluarga " << trees[i]->keluarga << endl;
                            exist = true;
                        }
                    }
                    if(exist) {
                        int p;
                        cout << "Pilih Nomor: "; cin >> p;
                        if(p > 0 && p <= MAX_TREES && trees[p-1] != nullptr) {
                            cout << "Pre-Order  : "; preOrder(trees[p-1]); cout << endl;
                            cout << "In-Order   : "; inOrder(trees[p-1]); cout << endl;
                            cout << "Post-Order : "; postOrder(trees[p-1]); cout << endl;
                        } else cout << "Pilihan salah.\n";
                    } else cout << "Tree kosong.\n";
                }
                break;

            case 9:
                cout << "\n--- ANALISIS GENERASI (TERTINGGI & TERENDAH) ---\n";
                {
                    bool exist = false;
                    for(int i=0; i<MAX_TREES; i++) {
                        if(trees[i]) {
                            cout << i+1 << ". Keluarga " << trees[i]->keluarga << endl;
                            exist = true;
                        }
                    }
                    if(exist) {
                        int p;
                        cout << "Ketik Nomor Keluarga Yang Ingin Dipilih : "; cin >> p;
                        if(p > 0 && p <= MAX_TREES && trees[p-1] != nullptr) {
                            cout << endl;
                            showHighestNode(trees[p-1]);
                            cout << endl;
                            showLowestNode(trees[p-1]);
                        } else cout << "Pilihan salah.\n";
                    } else cout << "Belum ada data keluarga.\n";
                }
                break;

            case 0:
                cout << "Keluar Program.\n";
                break;
            default:
                cout << "Input salah.\n";
        }

    } while(menu != 0);

    return 0;
}