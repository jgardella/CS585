NAME = final
TARBALL = jgardell-jphilli2-$(NAME).tar.gz
SRC = main.cpp sneakygraph.cpp loadFile.cpp program.cpp show.cpp safest_path.cpp bigjobcrew.cpp escape_routes.cpp
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

submit: fclean
	tar cvzf $(TARBALL) *
