NAME = test
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix bin/,$(notdir $(CPP_FILES:.cpp=.o)))
RM = rm -f
CXXFLAGS = -Iinclude -Wall -Werror

debug: CXXFLAGS += -DDEBUG

all: $(OBJ_FILES)
	g++ -std=c++11 $(CXXFLAGS) $(OBJ_FILES) -o $(NAME)

debug: all

bin/%.o: src/%.cpp
	g++ $(CXXFLAGS) -c -o $@ $<
clean:
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.core

fclean:	clean
	-$(RM) $(NAME)

re: fclean all
