build:
	gcc -Wall -g tema2.c -o quadtree -std=c99

clean:
	rm quadtree

memcheck: build
	valgrind --leak-check=full --show-leak-kinds=all --log-file=val.out --track-origins=yes --verbose ./quadtree -c 0 test15.ppm out.ppm