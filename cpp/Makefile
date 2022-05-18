CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -Wshadow -I include -O3

SRC = src/args.cpp \
      src/file_dir_infos.cpp \
			src/displayer.cpp \
      src/main.cpp \
			src/size_unit.cpp \
      src/tree.cpp \
			src/utils.cpp

OBJ = $(SRC:src%.cpp=obj%.o)

OUT_DIR = bin/

NAME = $(OUT_DIR)tree++

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

$(OBJ): obj/%.o: src/%.cpp include/%.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
