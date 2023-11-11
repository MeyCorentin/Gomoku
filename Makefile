##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## It's my Makefile
##

PP = g++
src = main.cpp

NAME = pbrain-gomoku-ai
OBJ = ${src:.cpp=.o}

${NAME}: ${OBJ}
	@g++ -o ${NAME} ${src} -I include -std=c++20 -Wall -g3
	@echo 'Files compiled'

all : ${NAME}

clean :
	@rm -rf ${OBJ}
	@echo 'Temporary files deleted'
fclean : clean
	@rm -rf ${NAME}
	@rm -rf unit_tests
	@echo 'Executable deleted'

re : fclean all

tests_run:
	@g++ ${src} \
	tests/*.cpp -W -Iinclude -o unit_tests \
	--coverage -lcriterion
	@./unit_tests

test:
	@mr_clean
	@clear
	@g++ ${src} \
	tests/*.cpp -W -Iinclude -o unit_tests \
	--coverage -lcriterion
	@./unit_tests
	@gcovr --exclude tests/
	@gcovr --exclude tests/ --branche
	@mr_clean

.PHONY: re fclean clean all