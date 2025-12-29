#include "MLL.h"
void createListPosisi(ListPosisi &L) {
    L.first = nullptr;
}

AddressPosisi createElmPosisi(InfoPosisi X) {
    AddressPosisi P = new ElmPosisi;
    P->info = X;
    P->next = nullptr;
    P->firstPemain = nullptr;
    return P;
}

AddressPemain createElmPemain(InfoPemain X) {
    AddressPemain P = new ElmPemain;
    P->info = X;
    P->next = nullptr;
    return P;
}

void insertLastPosisi(ListPosisi &L, AddressPosisi P) {
    if (L.first == nullptr) {
        L.first = P;
    } else {
        AddressPosisi Q = L.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

AddressPosisi findPosisi(ListPosisi L, string namaPosisi) {
    AddressPosisi P = L.first;
    while (P != nullptr) {
        if (P->info.namaPosisi == namaPosisi) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

void deletePosisi(ListPosisi &L, string namaPosisi) {
    AddressPosisi P_Hapus = findPosisi(L, namaPosisi);
    if (P_Hapus == nullptr) {
        cout << "[!] Posisi " << namaPosisi << " tidak ditemukan." << endl;
        return;
    }

    AddressPemain P_Pemain = P_Hapus->firstPemain;
    while (P_Pemain != nullptr) {
        AddressPemain temp = P_Pemain;
        P_Pemain = P_Pemain->next;
        delete temp;
    }
    P_Hapus->firstPemain = nullptr;

    if (P_Hapus == L.first) {
        L.first = P_Hapus->next;
    } else {
        AddressPosisi Prec = L.first;
        while (Prec->next != P_Hapus) {
            Prec = Prec->next;
        }
        Prec->next = P_Hapus->next;
    }

    delete P_Hapus;
    cout << "Posisi '" << namaPosisi << "' dan semua pemain di dalamnya berhasil dihapus." << endl;
}

void insertLastPemain(AddressPosisi P_Posisi, AddressPemain P_Pemain) {
    if (P_Posisi == nullptr) {
        cout << "Error: Posisi tidak valid." << endl;
        delete P_Pemain;
        return;
    }

    if (P_Posisi->firstPemain == nullptr) {
        P_Posisi->firstPemain = P_Pemain;
    } else {
        AddressPemain Q = P_Posisi->firstPemain;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P_Pemain;
    }
}

AddressPemain findPemain(AddressPosisi P_Posisi, string namaPemain) {
    if (P_Posisi == nullptr) return nullptr;
    AddressPemain P = P_Posisi->firstPemain;
    while (P != nullptr) {
        if (P->info.nama == namaPemain) return P;
        P = P->next;
    }
    return nullptr;
}

void deletePemainDariPosisi(ListPosisi &L, string namaPosisi, string namaPemain, AddressPemain &P_Pemain_Terhapus) {
    AddressPosisi P_Posisi = findPosisi(L, namaPosisi);
    P_Pemain_Terhapus = nullptr;

    if (P_Posisi == nullptr) return;

    AddressPemain P_Hapus = P_Posisi->firstPemain;
    AddressPemain Prec = nullptr;

    while (P_Hapus != nullptr && P_Hapus->info.nama != namaPemain) {
        Prec = P_Hapus;
        P_Hapus = P_Hapus->next;
    }

    if (P_Hapus == nullptr) return;

    P_Pemain_Terhapus = P_Hapus;
    if (Prec == nullptr) {
        P_Posisi->firstPemain = P_Hapus->next;
    } else {
        Prec->next = P_Hapus->next;
    }
    P_Pemain_Terhapus->next = nullptr;
}

AddressPemain searchPemainGlobal(ListPosisi L, string namaPemain, AddressPosisi &P_PosisiFound) {
    AddressPosisi P = L.first;

    while (P != nullptr) {
        AddressPemain Q = P->firstPemain;
        while (Q != nullptr) {
            if (Q->info.nama == namaPemain) {
                P_PosisiFound = P;
                return Q;
            }
            Q = Q->next;
        }
        P = P->next;
    }
    P_PosisiFound = nullptr;
    return nullptr;
}

void tampilkanSemuaData(ListPosisi L) {
    AddressPosisi P = L.first;
    if (P == nullptr) {
        cout << "\n[!] Daftar Posisi kosong." << endl;
        return;
    }

    while (P != nullptr) {
        cout << "\nPOSISI: " << P->info.namaPosisi << endl;
        AddressPemain Q = P->firstPemain;
        if (Q == nullptr) {
            cout << "  (Tidak ada pemain)" << endl;
        } else {
            while (Q != nullptr) {
                cout << "  - " << Q->info.nama << " (" << Q->info.noPunggung << ") [" << Q->info.statusKontrak << "]" << endl;
                Q = Q->next;
            }
        }
        P = P->next;
    }
}

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void showMenu() {
    cout << "\n=======================================================" << endl;
    cout << "   MANAJEMEN TIM SEPAK BOLA (MULTI LINKED LIST) - MENU   " << endl;
    cout << "=======================================================" << endl;
    cout << "1. Tambah Posisi Baru" << endl;
    cout << "2. Tambah Pemain ke Posisi" << endl;
    cout << "3. Tampilkan Semua Data" << endl;
    cout << "4. Cari Pemain" << endl;
    cout << "5. Hapus Pemain dari Posisi" << endl;
    cout << "6. Hapus Posisi" << endl;
    cout << "0. Keluar" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "Pilih menu: ";
}

void setupInitialData(ListPosisi &L) {
    insertLastPosisi(L, createElmPosisi({"Goalkeeper"}));
    insertLastPosisi(L, createElmPosisi({"Defender"}));
    insertLastPosisi(L, createElmPosisi({"Midfielder"}));
    insertLastPosisi(L, createElmPosisi({"Forward"}));

    AddressPosisi GK = findPosisi(L, "Goalkeeper");
    insertLastPemain(GK, createElmPemain({"Rudi Garcia", 1, "Aktif"}));

    AddressPosisi DEF1 = findPosisi(L, "Defender");
    insertLastPemain(DEF1, createElmPemain({"Arif Rahman", 5, "Aktif"}));
    AddressPosisi DEF2 = findPosisi(L, "Defender");
    insertLastPemain(DEF2, createElmPemain({"Dedi Kusn.", 8, "Aktif"}));

    AddressPosisi MF = findPosisi(L,"Midfielder");
    insertLastPemain(MF,createElmPemain({"Faisal Amir", 10, "Aktif"}));

    cout << "[INFO] Data awal berhasil dimuat." << endl;
}
