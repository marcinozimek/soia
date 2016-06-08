
all: wysylanie odbieranie prog
odbieranie: odbieranie.c
	gcc  -o odbieranie odbieranie.c 
wysylanie:	wysylanie.c
	gcc  -o wysylanie wysylanie.c 
prog: prog.c
	gcc -o prog prog.c
clean:
	rm -fr *~ odbieranie wysylanie prog