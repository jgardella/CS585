NAME = dynamicarray
SRC = main.cpp dynamicarray_constructors.cpp dynamicarray_modification.cpp dynamicarray_add.cpp dynamicarray_reallocate.cpp dynamicarray_length.cpp
OBJ = $(SRC:.cpp=.o)
RM = rm -f

all: $(OBJ)
	g++ $(OBJ) -o $(NAME)

clean:
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.core

fclean:	clean
	-$(RM) $(NAME)

re: fclean all
