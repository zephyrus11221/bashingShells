test:main.c
	gcc main.c -o test
run:test
	./test
clean:clean
	rm test
	rm *~
	rm *.txt
