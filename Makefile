NAME = dynamicarray
SRC = main.cpp dynamicarraytesting_simpletest.cpp dynamicarraytesting_constructors.cpp dynamicarraytesting_push.cpp dynamicarraytesting_modification.cpp
OBJ = $(SRC:.cpp=.o)
RM = rm -f

all: $(OBJ)
	gcc $(OBJ) -o $(NAME) -lstdc++

clean:
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.core

fclean:	clean
	-$(RM) $(NAME)

re: fclean all
