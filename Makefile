clean:
	rm -rf a.out util.o libutil.a main io iofork
obj:
	gcc -c util.c -o util.o
lib:
	ar rcs libutil.a util.o
io: obj lib
	gcc -static io.c -L. -I. -lutil -o io
iofork: obj lib
		gcc -static iofork.c -L. -I. -lutil -o iofork
