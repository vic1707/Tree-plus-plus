CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -Wshadow -I include
CC = g++

SRC = src/main.cpp \
      src/args.cpp \
      src/tree.cpp \
      src/utils.cpp

OBJ = $(SRC:.cpp=.o)

NAME = tree++

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
