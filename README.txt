/* FARCASIU Andrei - 311CB */
Main
	Incep prin initializarea directorului root, radacina intregului sistem de fisiere ce urmeaza a fi construit. Mai apoi declar variabilele pe care le voi folosi si fac citirea de la tastatura, afland functiile ce trebuie apelate si parametrii acestora folosind strtok. Importanta mai este variabila crt, care retine directorul in care ma aflu si care este data ca parametru in majorritatea functiilor. La sfarsit eliberez memoria cu ajutorul functiei distrArb, care primeste ca parametru directorul radacina.

Touch/Mkdir 
	Mai intai verific daca mai exista un fisier/director cu acelasi nume in directoul curent, caz in care se opreste functia si se afiseaza un mesaj de eroare. Daca nu, folosind functia verifFile/verifDir caut parintele nodului ce trebuie creat, apoi ii adaug un copil folosinf functiile de constructie.

Ls
	Se face parcurgerea SRD pe directoare si pe fisiere, functii ce afiseaza toate nodurile in ordine lexicografica.

Rm/Rmdir
	Mai intai verific daca exista nodul ce trebuie sters din arbore(daca nu -> eroare), apoi, daca exista, eliminarea se face pe 3 cazuri: cand nodul in discutie nu are copii, are doar 1 copil sau are 2 copii. In toate cele 3 variante eliminarea se face tinand cont de pastrarea arborelui binar de cautare si eliberarea memoriei.

Cd 
	Mai intai iau in considerare cazul "cd ..", cand returnez parintele directoului curent. In rest, verific daca exista directorul cu numele dat ca parametru (daca nu -> eroare), iar daca exista, il caut si returnez cu functia CautareDir2.

Pwd
	Initializez un vector de stringuri, apoi parcurg arborele trecand prin toti predecesorii directorului curent pana ajung in root, ale caror nume le stochez in vector. Apoi afisez elementele vectorului in ordine inversa, obtinand calea catre directorul curent. La sfarsit eliberez memoria alocata vectorului si elementelor lui.

Find
	Folosind CautareDir2/CautareFile2 caut si returnez nodul cautat. Daca outputul este diferit de NULL ok devine 1 si se iese din functie. Daca nu, se reapeleaza functia pentru root->st, root->dr, root->directories.

Punctaj: 135/135 + 20/20 bonus


