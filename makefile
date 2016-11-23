wao:main.c
	gcc main.c -o test
run:test
	./test
clear:clean
	rm test
	rm *~
