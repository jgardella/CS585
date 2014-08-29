<<<<<<< HEAD
NAME = final
TARBALL = jgardell-jphilli2-$(NAME).tar.gz
SRC = main.cpp sneakygraph.cpp loadFile.cpp program.cpp show.cpp safest_path.cpp bigjobcrew.cpp escape_routes.cpp
=======
NAME = jtest
SRC = main.cpp jtest.cpp
>>>>>>> 05b5df9
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
<<<<<<< HEAD

submit: fclean
	tar cvzf $(TARBALL) *
=======
>>>>>>> 05b5df9
