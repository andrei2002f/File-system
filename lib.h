/* FARCASIU Andrei - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct dir {
    char *nume;
    struct dir *parinte;
    struct file *fisier;
    struct dir *directories;
    struct dir *st, *dr;
} TDir, *TArb, **AArb;

typedef struct file {
    char *nume;
    struct dir *parinte;
    struct file *st, *dr;
} TFile, *TCopac, **ACopac;

//functiiaux
TArb ConstrDir(char* x, TArb parinte);
TCopac ConstrFile(char* x, TArb parinte);
int CautareFile(TCopac root, char* nume);
int CautareDir(TArb root, char* nume);
void SRDFile(TCopac root);
void SRDDir(TArb root);
TCopac MinFile(TCopac root);
TArb MinDir(TArb root);
TCopac cauta(TCopac root, char* nume);
TCopac CautareFile2(TCopac root, char* nume);
TArb CautareDir2(TArb root, char* nume);
void distruge(TArb r);
void DistrArb(TArb *a);
void distrugeFis(TCopac fis);
TArb verifDir(TArb root, char* nume);
TCopac verifFile(TCopac root, char* nume);


//functii
void touch(TArb dir, char* nume);
void mkdir(TArb dir, char* nume);
void ls(TArb dir);
TCopac rm (TCopac file, char* nume);
TArb rmdir(TArb root, char* nume);
TArb cd(TArb dir, char* nume);
void pwd(TArb dir);
void findFile(char* nume, TArb root, int *ok);
void findDir(char* nume, TArb root, int* ok);