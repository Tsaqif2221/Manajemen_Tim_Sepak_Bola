#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED

#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct InfoPemain {
    string nama;
    int noPunggung;
    string statusKontrak;
};

typedef struct ElmPemain* AddressPemain;
struct ElmPemain {
    InfoPemain info;
    AddressPemain next;
};

struct InfoPosisi {
    string namaPosisi;
};

typedef struct ElmPosisi* AddressPosisi;
struct ElmPosisi {
    InfoPosisi info;
    AddressPosisi next;
    AddressPemain firstPemain;
};

struct ListPosisi {
    AddressPosisi first;
};

void createListPosisi(ListPosisi &L);
AddressPosisi createElmPosisi(InfoPosisi X);
AddressPemain createElmPemain(InfoPemain X);
void insertLastPosisi(ListPosisi &L, AddressPosisi P);
AddressPosisi findPosisi(ListPosisi L, string namaPosisi);
void deletePosisi(ListPosisi &L, string namaPosisi);
void insertLastPemain(AddressPosisi P_Posisi, AddressPemain P_Pemain);
void deletePemainDariPosisi(ListPosisi &L, string namaPosisi, string namaPemain, AddressPemain &P_Pemain_Terhapus);
AddressPemain findPemain(AddressPosisi P_Posisi, string namaPemain);
AddressPemain searchPemainGlobal(ListPosisi L, string namaPemain, AddressPosisi &P_PosisiFound);
void tampilkanSemuaData(ListPosisi L);

void clearInputBuffer();
void showMenu();
void setupInitialData(ListPosisi &L);


#endif // MLL_H_INCLUDED
