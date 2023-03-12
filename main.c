/* FARCASIU Andrei - 311CB */
#include "lib.h"

int main() {
    TArb root = (TArb)malloc(sizeof(TDir));
    root->nume = malloc(50);
    strcpy(root->nume, "root");
    root->directories = NULL;
    root->fisier = NULL;
    root->parinte = NULL;
    root->st = NULL;
    root->dr = NULL;

    size_t len = 0;
    char *functie, *line = NULL, *nume, *dsauf;
    TArb crt = root;

    // citirea, determinarea functiilor si a parametrilor cu strtok
    while(getline(&line, &len, stdin) != -1) {
        functie = strtok(line, " \n");
        
        if (strcmp(functie, "touch") == 0) {
            nume = strtok(NULL, "\n");
            touch(crt, nume);
        }
        
        else if (strcmp(functie, "mkdir") == 0) {
            nume = strtok(NULL, "\n");
            mkdir(crt, nume);
        }

        else if (strcmp(functie, "ls") == 0) {
            ls(crt);
        }

        else if (strcmp(functie, "rm") == 0) {
            nume = strtok(NULL, "\n");
            crt->fisier = rm(crt->fisier, nume);
        }

        else if (strcmp(functie, "rmdir") == 0) {
            nume = strtok(NULL, "\n");
            crt->directories = rmdir(crt->directories, nume);
        }

        else if (strcmp(functie, "cd") == 0) {
            nume = strtok(NULL, "\n");
            crt = cd(crt, nume);
        }

        else if (strcmp(functie, "pwd") == 0) {
            pwd(crt);
        }

        else if (strcmp(functie, "find") == 0) {
            dsauf = strtok(NULL, " ");
            nume = strtok(NULL, "\n");
            if (strcmp(dsauf, "-d") == 0) {
                int ok = 0;
                findDir(nume, root, &ok);
                if (!ok) {
                    printf("Directory %s not found!\n", nume);
                }
            }
            else {    
                int ok = 0;
                findFile(nume, root, &ok);
                if (!ok) {
                    printf("File %s not found!\n", nume);
                }
            }
        }

        // eliberrarea memoriei
        else if (strcmp(functie, "quit") == 0) {
            DistrArb(&root);
            free(line);
            root = NULL;
            break;
        }
    }

    return 0;
}