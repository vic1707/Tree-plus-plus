CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -Wshadow -I inc -O3
# CXX = /usr/local/opt/gcc@11/bin/g++-11 # `brew install gcc` MacOS

SRC = src/args.cpp \
			src/displayer.cpp \
      src/file_dir_infos.cpp \
      src/main.cpp \
			src/size_unit.cpp

OBJ = $(SRC:src%.cpp=obj%.o)

OUT_DIR := $(or $(OUT_DIR),bin/)

NAME = $(OUT_DIR)tree++

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) -lfmt

$(OBJ): obj/%.o: src/%.cpp inc/%.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
