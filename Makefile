FLAGS = -std=c++20 -c -Wall -Werror -Wextra -I include

.PHONY: clean real-clean

tree: main.o tree.o utils.o # args.o
	g++ -o $@ $^
	make clean

main.o: src/main.cpp
	g++ $(FLAGS) $<

# args.o: src/args.cpp
# 	g++ $(FLAGS) $<

tree.o: src/tree.cpp
	g++ $(FLAGS) $<

utils.o: src/utils.cpp
	g++ $(FLAGS) $<

clean:
	rm -f *.o

real-clean:
	rm -f *.o
	rm -f tree
