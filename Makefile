main: main.c node.o binary_search_tree.o array_vector_string.h string.o vector_string.o
	gcc -Wall -std=c99 -ggdb node.o binary_search_tree.o array_vector_string.h string.o vector_string.o main.c -o main
string.o: string.c string.h
	gcc -Wall -std=c99 -ggdb string.c string.h -c
vector_string.o: vector_string.h vector_string.c
	gcc -Wall -std=c99 -ggdb vector_string.h vector_string.c -c
binary_search_tree.o: binary_search_tree.c binary_search_tree.h
	gcc -Wall -std=c99 -ggdb binary_search_tree.c binary_search_tree.h -c
node.o: node.c node.h
	gcc -Wall -std=c99 -ggdb node.h node.c -c

