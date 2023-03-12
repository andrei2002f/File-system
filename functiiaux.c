/* FARCASIU Andrei - 311CB */
#include "lib.h"

TArb ConstrDir(char* x, TArb parinte)     /* -> adresa frunza dir cu informatia x, sau NULL daca nu exista spatiu */
{
	TArb aux = (TArb)malloc (sizeof(TDir));  
	if (!aux) return NULL;
    aux->nume = malloc(50);
    strcpy(aux->nume, x);
    aux->st = aux->dr = NULL;
    aux->parinte = parinte;
    aux->fisier = NULL;
    aux->directories = NULL;

	return aux;
}

TCopac ConstrFile(char* x, TArb parinte)     /* -> adresa frunza file cu informatia x, sau NULL daca nu exista spatiu */
{
	TCopac aux = (TCopac)malloc (sizeof(TFile));
	if (!aux) return NULL;
    aux->nume = malloc(50);
    strcpy(aux->nume, x);
	aux->st = aux->dr = NULL;
    aux->parinte = parinte;

	return aux;
}

// cauta un fisier intr-un arbore de fisiere
int CautareFile(TCopac root, char* nume) {
    if (root == NULL) 
        return 0;
    if (strcmp(root->nume, nume) == 0) 
        return 1;
    else if (strcmp(root->nume, nume) < 0)
        return CautareFile(root->dr, nume);
    else return CautareFile(root->st, nume);
}

// cauta un director intr-un arbore de directoare
int CautareDir(TArb root, char* nume) {
    if (root == NULL) 
        return 0;
    if (strcmp(root->nume, nume) == 0) 
        return 1;
    else if (strcmp(root->nume, nume) < 0)
        return CautareDir(root->dr, nume);
    else return CautareDir(root->st, nume);
}

// parcurgere SRD pe arbore de fisiere
void SRDFile(TCopac root) {
    if (root == NULL)
        return;
    else {
        SRDFile(root->st);
        printf("%s ", root->nume);
        SRDFile(root->dr);
    }
}

// parcurgere SRD pe arbore de directoare
void SRDDir(TArb root) {
    if (root == NULL)
        return;
    else {
        SRDDir(root->st);
        printf("%s ", root->nume);
        SRDDir(root->dr);
    }
}

// returneaza cea mai mica valoare dintr-un arbore de fisiere
TCopac MinFile(TCopac root) {
    TCopac aux = root;
    while (aux && aux->st)
        aux = aux->st;
    return aux;
}

// returneaza cea mai mica valoare dintr-un arbore de directoare
TArb MinDir(TArb root) {
    TArb aux = root;
    while (aux && aux->st)
        aux = aux->st;
    return aux;
}

// cauta un fisier intr-un arbore de fisiere, il returneaza daca este gasit
TCopac CautareFile2(TCopac root, char* nume) {
    if (root == NULL) 
        return NULL;
    if (strcmp(root->nume, nume) == 0) 
        return root;
    else if (strcmp(root->nume, nume) < 0)
        return CautareFile2(root->dr, nume);
    else return CautareFile2(root->st, nume);
}

// cauta un director intr-un arbore de directoare, il returneaza daca este gasit
TArb CautareDir2(TArb root, char* nume) {
    if (root == NULL) 
        return NULL;
    if (strcmp(root->nume, nume) == 0) 
        return root;
    else if (strcmp(root->nume, nume) < 0)
        return CautareDir2(root->dr, nume);
    else return CautareDir2(root->st, nume);
}

// eliberarea memoriei unui arbore de fisiere
void distrugeFis(TCopac fis) {
    if (!fis) return;
    free(fis->nume);
    distrugeFis(fis->dr);
    distrugeFis(fis->st);
    
    free(fis);
}

void distruge(TArb r) 	/* functie auxiliara - distruge toate nodurile */
{
	if (!r) return;
    free(r->nume);
	distruge (r->st);     /* distruge subarborele stang */
	distruge (r->dr);     /* distruge subarborele drept */
    distruge (r->directories);
    distrugeFis (r->fisier);
    
	free (r);             /* distruge nodul radacina */
}

void DistrArb(TArb *a) /* distruge toate nodurile arborelui de la adresa a */
{
	if (!(*a)) return;       /* arbore deja vid */
	distruge (*a);           /* distruge toate nodurile */
	*a = NULL;               /* arborele este vid */
}

// cauta parintele pentru directorul ce trebuie creat
TArb verifDir(TArb root, char* nume) {
    if (!root)
        return root;
    if (!root->dr && !root->st)
        return root;
    else if (strcmp(root->nume, nume) < 0) {
        if (root->dr)
            return verifDir(root->dr, nume);
        else return root;
    } 
    else {
        if (root->st)
            return verifDir(root->st, nume);
        else return root;
    }
}

// cauta parintele pentru fisierul ce trebuie creat
TCopac verifFile(TCopac root, char* nume) {
    if (!root)
        return root;
    if (!root->dr && !root->st)
        return root;
    else if (strcmp(root->nume, nume) < 0) {
        if (root->dr)
            return verifFile(root->dr, nume);
        else return root;
    } 
    else {
        if (root->st)
            return verifFile(root->st, nume);
        else return root;
    }
}