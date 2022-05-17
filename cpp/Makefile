CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -Wshadow -I include
CXX = g++

SRC = src/args.cpp \
      src/file_dir_infos.cpp \
			src/displayer.cpp \
      src/main.cpp \
			src/size_unit.cpp \
      src/tree.cpp

OBJ = $(SRC:src%.cpp=obj%.o)

OUT_DIR = bin

NAME = tree++

.PHONY: all clean fclean re

all: $(OUT_DIR)/$(NAME)

$(OUT_DIR)/$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/$(NAME) $(OBJ)

$(OBJ): obj/%.o: src/%.cpp include/%.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
