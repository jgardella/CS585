NAME = dynamicarray
SRC = main.cpp dynamicarraytesting_simpletest.cpp dynamicarraytesting_constructors.cpp dynamicarraytesting_push.cpp dynamicarraytesting_modification.cpp dynamicarraytesting_memoryreallocation.cpp
OBJ = $(SRC:.cpp=.o)
RM = rm -f

all: $(OBJ)
	g++ $(OBJ) -o $(NAME)  -Wall -Werror -std=c++11 -g

clean:
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.core

fclean:	clean
	-$(RM) $(NAME)

re: fclean all
