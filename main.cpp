#include <iostream>
#include "MLL.h"
using namespace std;

int main() {
    ListPosisi L;
    createListPosisi(L);
    setupInitialData(L);

    int pilihan;
    do {
        showMenu();
        if (!(cin >> pilihan)) {
            cin.clear();
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        string namaP, namaPos, stat;
        int no;
        AddressPosisi P_Pos;
        AddressPemain P_Hapus;

        switch (pilihan) {
            case 1:
                cout << "Nama Posisi: "; getline(cin, namaPos);
                insertLastPosisi(L, createElmPosisi({namaPos}));
                break;
            case 2:
                cout << "Posisi Tujuan: "; getline(cin, namaPos);
                P_Pos = findPosisi(L, namaPos);
                if (P_Pos) {
                    cout << "Nama Pemain: "; getline(cin, namaP);
                    cout << "Nomor: "; cin >> no; clearInputBuffer();
                    cout << "Status: "; getline(cin, stat);
                    insertLastPemain(P_Pos, createElmPemain({namaP, no, stat}));
                } else {
                    cout << "[!] Posisi tidak ditemukan." << endl;
                }
                break;
            case 3:
                tampilkanSemuaData(L);
                break;
            case 4: {
                cout << "\n--- Cari Pemain ---" << endl;
                cout << "Nama Pemain yang dicari: ";
                getline(cin, namaP);

                AddressPosisi P_PosFound = nullptr;
                AddressPemain P_PemainFound = searchPemainGlobal(L, namaP, P_PosFound);

                if (P_PemainFound != nullptr) {
                    cout << "\n[RESULT] Pemain ditemukan!" << endl;
                    cout << "Nama        : " << P_PemainFound->info.nama << endl;
                    cout << "Posisi      : " << P_PosFound->info.namaPosisi << endl;
                    cout << "No Punggung : " << P_PemainFound->info.noPunggung << endl;
                    cout << "Status      : " << P_PemainFound->info.statusKontrak << endl;
                } else {
                    cout << "[!] Pemain '" << namaP << "' tidak ditemukan." << endl;
                }
                break;
            }
            case 5: {
                cout << "Posisi: "; getline(cin, namaPos);
                cout << "Nama: "; getline(cin, namaP);
                P_Hapus = nullptr;
                deletePemainDariPosisi(L, namaPos, namaP, P_Hapus);
                if (P_Hapus != nullptr) {
                    delete P_Hapus;
                    cout << "[INFO] Pemain berhasil dihapus." << endl;
                } else {
                    cout << "[!] Pemain tidak ditemukan di posisi tersebut." << endl;
                }
                break;
            }
            case 6:
                cout << "Hapus Posisi: "; getline(cin, namaPos);
                deletePosisi(L, namaPos);
                break;
        }
    } while (pilihan != 0);

    return 0;
}
