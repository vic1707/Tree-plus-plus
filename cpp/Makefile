CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -Wshadow -I include
CXX = g++

SRC = src/args.cpp \
      src/main.cpp \
      src/tree.cpp \
      src/utils.cpp

OBJ = $(SRC:src%.cpp=obj%.o)

OUT_DIR = bin

NAME = tree++

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/$(NAME) $(SRC)

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
