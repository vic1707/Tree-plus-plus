FLAGS = -std=c++20 -c -Wall -Werror -Wextra

.PHONY: clean real-clean

tree: main.o tree.o utils.o # args.o
	g++ -o $@ $^
	make clean

main.o: src/main.cpp inc/tree.hpp
	g++ $(FLAGS) $<

# args.o: src/args.cpp inc/args.hpp
# 	g++ $(FLAGS) $<

tree.o: src/tree.cpp inc/tree.hpp inc/utils.hpp
	g++ $(FLAGS) $<

utils.o: src/utils.cpp inc/utils.hpp
	g++ $(FLAGS) $<

clean:
	rm -f *.o

real-clean:
	rm -f *.o
	rm tree