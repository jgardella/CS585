NAME = test
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix bin/,$(notdir $(CPP_FILES:.cpp=.o)))
RM = rm -f

all: $(OBJ_FILES)
	g++ $(OBJ_FILES) -o $(NAME)

bin/%.o: src/%.cpp
	g++ -Iinclude $(CC_FLAGS) -c -o $@ $<
clean:
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.core

fclean:	clean
	-$(RM) $(NAME)

re: fclean all
