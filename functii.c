/* FARCASIU Andrei - 311CB */
#include "lib.h"

// mai intai verific daca exista deja un fisier cu acelasi nume
// daca nu, caut nodul parinte al fisierului ce urmeaza sa fie creat, caruia ii adaug un copil
void touch(TArb dir, char* nume) {
    if (CautareDir(dir->directories, nume)) {
        printf("Directory %s already exists!\n", nume);
        return;
    }
    if (CautareFile(dir->fisier, nume)) {
        printf("File %s already exists!\n", nume);
        return;
    }

    if (!dir->fisier) {
        dir->fisier = ConstrFile(nume, dir);
    } 
    else {
        TCopac file = dir->fisier;
        file = verifFile(file, nume);
        if (strcmp(nume, file->nume) > 0)
            file->dr = ConstrFile(nume, dir);
        if (strcmp(nume, file->nume) < 0)
            file->st = ConstrFile(nume, dir);
    }     
}

// la fel ca la touch, doar ca pentru dir->directories, nu pentru dir->fisier
void mkdir(TArb dir, char* nume) {
    if (CautareDir(dir->directories, nume)) {
        printf("Directory %s already exists!\n", nume);
        return;
    }
    if (CautareFile(dir->fisier, nume)) {
        printf("File %s already exists!\n", nume);
        return;
    }

    if (!dir->directories) {
        dir->directories = ConstrDir(nume, dir);
    } 
    else {
        TArb file = dir->directories;
        file = verifDir(file, nume);
        if (strcmp(nume, file->nume) > 0)
            file->dr = ConstrDir(nume, dir);
        if (strcmp(nume, file->nume) < 0)
            file->st = ConstrDir(nume, dir);
    }    
}

// parcurgere SRD pe directoare, apoi pe fisiere, pentru a afisa toate nodurile
void ls(TArb dir) {
    SRDDir(dir->directories);
    SRDFile(dir->fisier);
    printf("\n");
}


TCopac rm(TCopac root, char* nume) {
    //fisierul nu exista
    if (!CautareFile(root, nume)) {
        printf("File %s doesn't exist!\n", nume);
        return root;
    }
    
    if (strcmp(nume, root->nume) < 0)
        root->st = rm(root->st, nume);
    else if (strcmp(nume, root->nume) > 0)
        root->dr = rm(root->dr, nume);
    // am gasit fisierul cautat
    else {
        // fisierul are doar un copil
        if (!root->st){
            TCopac aux = root->dr;
            free(root->nume);
            free(root);
            return aux;
        }
        else if (!root->dr){
            TCopac aux = root->st;
            free(root->nume);
            free(root);
            return aux;
        }
        // fisierul are 2 copii
        TCopac aux = MinFile(root->dr);
        strcpy(root->nume, aux->nume);
        root->dr = rm(root->dr, aux->nume);
    }
    return root;
}

TArb rmdir(TArb root, char* nume) {
    //fisierul nu exista
    if (!CautareDir(root, nume)) {
        printf("Directory %s doesn't exist!\n", nume);
        return root;
    }
    
    if (strcmp(nume, root->nume) < 0)
        root->st = rmdir(root->st, nume);
    else if (strcmp(nume, root->nume) > 0)
        root->dr = rmdir(root->dr, nume);
    // am gasit fisierul cautat
    else {
        // fisierul are doar un copil
        if (!root->st){
            TArb aux = root->dr;
            free(root->nume);
            distruge(root->directories);
            distrugeFis(root->fisier);
            free(root);
            return aux;
        }
        else if (!root->dr){
            TArb aux = root->st;
            free(root->nume);
            distruge(root->directories);
            distrugeFis(root->fisier);
            free(root);
            return aux;
        }
        // fisierul are 2 copii
        TArb aux = MinDir(root->dr);
        strcpy(root->nume, aux->nume);
        root->dr = rmdir(root->dr, aux->nume);
    }
    return root;
}


TArb cd(TArb dir, char* nume) {
    // cazul "..", cand functia intoarce directorul parinte
    if (strcmp(nume, "..") == 0) {
        if (!dir->parinte) 
            return dir;
        else return dir->parinte;
    }
    // se verifica daca exista directorul cautat
    if (!CautareDir(dir->directories, nume)) {
        printf("Directory not found!\n");
        return dir;
    }
    
    // cautam directorul cu functia CautareDir2 , apoi il returnam
    TArb file = dir->directories;
    file = CautareDir2(file, nume);
    return file;
}

// initializez un vector de stringuri, ale carui elemente sunt numele predecesorilor unui director, incepand cu parintele, pana la root
void pwd(TArb dir) {
    char** v = (char**)malloc(10 * sizeof(char*));
    for (int i = 0; i < 10; i++) 
        v[i] = (char*)malloc(50);
    int i = 1;
    TArb point = dir;
    strcpy(v[0], point->nume);
    while (point->parinte) {
        strcpy(v[i], point->parinte->nume);
        i++;
        point = point->parinte;
    }
    // se afiseaza succesorii in ordine inversa fata de cum erau stocati in vector
    for (int j=i-1; j>=0; j--) {
        printf("/%s", v[j]);
    }
    printf("\n");
    // se dezaloca memoria alocata pentru vectorul de stringuri
    for (i = 0; i < 10; i++) 
        free(v[i]);
    free(v);
}


void findDir(char* nume, TArb root, int* ok) {
    if (root == NULL || (*ok) == 1)
        return;
    // se ia rootul arborelui de directoare, se verifica daca este directorul cautat
    TArb aux = root->directories;

    // daca da, se afiseaza lucrurile cerute si ok devine 1, adica functia se incheie
    if (CautareDir2(aux, nume)) {
        (*ok) = 1;
        aux = CautareDir2(aux, nume);
        printf("Directory %s found!\n", nume);
        pwd(aux);
    }

    // daca nu, se reapeleaza functia pentru root->st, root->dr, root->directories
    findDir(nume, root->st, ok);
    findDir(nume, root->dr, ok);
    findDir(nume, root->directories, ok);
}

// la fel ca la findDir, doar ca pentru fisiere
void findFile(char* nume, TArb root, int* ok) {
    if (root == NULL || (*ok) == 1)
        return;

    TCopac aux = root->fisier;

    if (CautareFile2(aux, nume)) {
        (*ok) = 1;
        aux = CautareFile2(aux, nume);
        printf("File %s found!\n", nume);
        pwd(aux->parinte);
    }

    findFile(nume, root->st, ok);
    findFile(nume, root->dr, ok);
    findFile(nume, root->directories, ok);
}


