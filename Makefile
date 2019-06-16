practice6: practice6.c
	gcc -Wall -g3 -o $@ $^

clean:
	find -type f -executable -delete
	find -type f -name *.o -delete
