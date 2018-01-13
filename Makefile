main_test: main_test.o linked_list.o
	gcc -g -m32 -o main_test main_test.o linked_list.o 

linked_list.o: linked_list.c linked_list.h 
	gcc -g -m32 -c linked_list.c

clean:
	rm -f *.o main_test
