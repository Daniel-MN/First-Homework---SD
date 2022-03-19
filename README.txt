/* Musuroi Daniel-Nicusor - 313CB */



			Tema 1 – Structuri de date (seria CB)
					Tabele hash

	
	Tema 1 a fost implementata folosind o tabela Hash ce contine M liste
dublu inlantuite circulare generice (fara santinela), in care au fost puse 
elemente ce contin un camp key si un camp value. Pentru realizarea temei am 
folosit diferite functii pe langa cele speciale pentru efectuarea 
operatiilor date (put, get, remove, find, print, print_bucket):
	-IniTH -> initializeaza o tabela Hash.
	-DistrTH -> elibereaza spatiul ocupat de o tabela Hash.
	-codHash -> functia tabelei Hash, prin care poti ajunge la lista
		corespunzatoare unui element.
	-InitTLDG -> initializeaza o celula dintr-o lista dublu inlantuita
		circulara (fara santinela) cu un element primit ca parametru
	-InitElement -> initializeaza un element dintr-o lista, element ce 
		contine un camp key si un camp value.
	-DistrugeElement -> elibereaza memoria ocupata de un element.
	-InsDupa -> insereaza un element intr-o lista nevida dupa o celula 
		data.
	-GasesteKey_gt_Keyel -> intoarce prima celula dintr-o lista care 
		contine un element x ce trebuie sa apara in lista imediat
		dupa un element dat ca parametru. Practic, functia gaseste 
		elementul inaintea caruia trebuie sa introduc un element nou
		in lista.
	-Elim -> elimina o celula dintr-o lista, se aplica doar listelor
		cu cel putin doua elemente.

		Functiile ce descriu operatiile necesare pentru rezolvarea 
	temei:
	
	-put -> realizeaza operatia put. Pentru a face acest lucru se iau 
		in calcul mai multe situatii:
		->Cazul in care lista e vida: se initializeaza lista cu 
		elementul dat.
		->Cazul in care elementul trebuie introdus la sfarsitul
		listei: elementul va fi introdus inaintea primului element
		(fiind o lista circulara).
		->Cazul in care mai exista in lista un element, cu acelasi
		key: nu se va mai introduce noul element.
		->Cazul in care elementul trebuie introdus ca prim element
		din lista: se va introduce inaintea primul element si se va
		modifica inceputul listei.
		->Cazul in care elementul trebuie introdus la jumatatea 
		listei: se face inserarea elementului nou inaintea 
		elementului obtinut din functia GasesteKey_gt_Keyel.
	-get_function -> realizeaza operatia get. Functia face o parcurgere
		a listei corespunzatoare verificand daca exista elementul 
		cautat. In cazul in care exista, se va intoarce valoarea 
		acestuia, iar in cazul in care nu exista se va intoarce 
		stringul "NULL".
	-remove_function -> realizeaza operatia remove. Functia analizeaza 
		mai multe cazuri:
		->Cazul in care lista este vida: Functia nu face nimic. :))
		->Cazul in care lista contine un element si acesta este 
		chiar cel ce trebuie eliminat, caz in care distruge lista.
		->Cazul in care lista contine cel putin doua element: Se 
		face o parcurgere a listei si se cauta elementul cu key-ul
		dat. Daca se gaseste se va folosi functia Elim.
	-find -> realizeaza operatia find. Functia verifica daca lista e 
		vida si daca nu, face o parcurgere prin lista cautand 
		elementul cu key-ul dat. Daca il gaseste va intoarce "True",
		iar daca nu il gaseste va intoarce "False".
	-print -> realizeaza operatia print. Functia ia fiecare lista din
		tabelaH si verifica daca este vida. In cazul in care nu este
		vida, se va face o parcurgere a listei si se va afisa 
		valoarea fiecarui element.
	-print_bucket -> realizeaza operatia print_bucket. Functia verifica
		mai intai daca indexul dat este valid. In caz afirmativ, 
		se va verifica daca lista este vida. Daca lista este vida,
		se va afisa "VIDA", iar in cazul in care lista nu este vida,
		se va face o parcurgere prin aceasta si se va afisa valoarea
		fiecarui element.

	In cazuri exceptionale am afisat diferite mesaje de eroare, care nu
ar trebui sa apara daca tema este rulata cum trebuie si daca memoria este 
alocata corect.