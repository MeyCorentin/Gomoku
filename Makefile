##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## It's my Makefile
##

ifeq ($(OS),Windows_NT)
	CXX = x86_64-w64-mingw32-g++
	EXE = .exe
	CXXFLAGS = -std=c++20
	RM = del
else
	CXX = g++
	EXE =
	CXXFLAGS = -std=c++20
	RM = rm -rf
endif

src = main.cpp \
      bitboard/src/bitboard.cpp \
      brain/src/brain.cpp \
      min_max/src/MinMax.cpp \
      parser/src/parser.cpp \
      parser/src/commandes/board.cpp \
      parser/src/commandes/start.cpp \
      parser/src/commandes/turn.cpp \
      parser/src/commandes/begin.cpp \
      parser/src/commandes/error.cpp \
      min_max/src/MinMaxEvaluation.cpp 


NAME = pbrain-gomoku-ai$(EXE)
OBJ = ${src:.cpp=.o}

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(src) -I include $(CXXFLAGS) -Wall -g3
	@echo 'Files compiled'

all: $(NAME)

clean:
	$(RM) $(OBJ)
	@echo 'Temporary files deleted'

fclean: clean
	$(RM) $(NAME)
	$(RM) unit_tests
	@echo 'Executable deleted'

re: fclean all

tests_run:
	$(CXX) $(src) \
	tests/*.cpp -W -Iinclude -o unit_tests \
	--coverage -lcriterion
	@./unit_tests

test: mr_clean
	clear
	$(CXX) $(src) \
	tests/*.cpp -W -Iinclude -o unit_tests \
	--coverage -lcriterion
	@./unit_tests
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches
	mr_clean

.PHONY: re fclean clean all
