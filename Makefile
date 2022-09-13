## Name of Project

NAME = data_sender

## Color for compilating (pink)

COLOR = \0033[1;35m

## List of Directories

INC_DIR = inc
OBJ_DIR = obj
SRC_DIR = src

# Add dirs here
WRITE_FILES_DIR = write_files

## Compilating Utilities
# FAST = -Ofast
DEBUG = -g -fsanitize=address
WARNINGS = -Wall -Wextra# -Werror
FLAGS = $(WARNINGS) $(FAST) $(DEBUG)# -D_REENTRANT

#OS X, the math library is part of libSystem
#Warning for -lm flag is normal on OS X
INC = $(INC_DIR:%=-I./%) -lm 

# CC = clang $(FLAGS) $(INC)
CC = gcc $(FLAGS) $(INC)

## List of Headers and C files 

INC_H = sender

WRITE_FILES_FT = write_json

SRC_FT = main

## List of Utilities

SRC = $(SRC_FT:%=$(SRC_DIR)/%.c) \
	$(WRITE_FILES_FT:%=$(SRC_DIR)/$(WRITE_FILES_DIR)/%.c)

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

OBJ_DIRS = $(OBJ_DIR) \
	$(WRITE_FILES_DIR:%=$(OBJ_DIR)/%)

INCLUDES = $(INC_H:%=./$(INC_DIR)/%.h)

## Rules of Makefile

all: $(NAME)
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;30m[All OK]\0033[1;37m"

$(OBJ_DIRS):
	@mkdir -p $@
	@echo "$(COLOR)$@ \033[100D\033[40C\0033[1;32m[Created]\0033[1;37m"
	@#@echo "$(COLOR)Creating :\t\0033[0;32m$@\0033[1;37m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@$(CC) -c $< -o $@
	@echo "$(COLOR)$@ \033[100D\033[40C\0033[1;32m[Compiled]\0033[1;37m"

$(NAME): $(OBJ_DIRS) $(SRC) $(INCLUDES)
	@make -C ./Space_MIDI
	@$(MAKE) -s -j $(OBJ)
	@echo "$(COLOR)Objects \033[100D\033[40C\0033[1;32m[Created]\0033[1;37m"
	@$(CC) $(OBJ) -o $@
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;32m[Created]\0033[1;37m"

clean:
	@make clean -C ./Space_MIDI
	@rm -rf $(OBJ_DIR)
	@echo "$(COLOR)Objects \033[100D\033[40C\0033[1;31m[Removed]\0033[1;37m"

fclean: clean
	@make fclean -C ./Space_MIDI
	@rm -f $(NAME)
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;31m[Removed]\0033[1;37m"

re: fclean all

run: coffee
	@echo ""
	@echo "$(COLOR)\"$(NAME)\" \033[100D\033[40C\0033[1;32m[Launched]\0033[1;37m"
	@./$(NAME)

define print_aligned_coffee
	@t=$(NAME); \
	l=$${#t};\
	i=$$((8 - l / 2));\
	echo "\0033[1;32m\033[3C\033[$${i}CAnd Your Program \"$(NAME)\" \0033[1;37m"
endef

coffee: all clean
	@echo ""
	@echo "                    {"
	@echo "                 {   }"
	@echo "                  }\0033[1;34m_\0033[1;37m{ \0033[1;34m__\0033[1;37m{"
	@echo "               \0033[1;34m.-\0033[1;37m{   }   }\0033[1;34m-."
	@echo "              \0033[1;34m(   \0033[1;37m}     {   \0033[1;34m)"
	@echo "              \0033[1;34m| -.._____..- |"
	@echo "              |             ;--."
	@echo "              |            (__  \ "
	@echo "              |             | )  )"
	@echo "              |   \0033[1;96mCOFFEE \0033[1;34m   |/  / "
	@echo "              |             /  / "
	@echo "              |            (  / "
	@echo "              \             | "
	@echo "                -.._____..- "
	@echo ""
	@echo ""
	@echo "\0033[1;32m\033[3C          Take Your Coffee"
	$(call print_aligned_coffee)

help:
	@echo "$(COLOR)Options :\0033[1;37m"
	@echo "\033[100D\033[5C\0033[1;32mmake\033[100D\033[10C \033[100D\033[40C\0033[1;31mCreate executable program\0033[1;37m"
	@echo "\033[100D\033[5C\0033[1;32mmake\033[100D\033[10Cclean\033[100D\033[40C\0033[1;31mClean program objects\0033[1;37m"
	@echo "\033[100D\033[5C\0033[1;32mmake\033[100D\033[10Cfclean\033[100D\033[40C\0033[1;31mCall \"clean\" and remove executable\0033[1;37m"
	@echo "\033[100D\033[5C\0033[1;32mmake\033[100D\033[10Cre\033[100D\033[40C\0033[1;31mCall \"fclean\" and make\0033[1;37m"
	@echo "\033[100D\033[5C\0033[1;32mmake\033[100D\033[10Ccoffee\033[100D\033[40C\0033[1;31mCall make and \"clean\"\0033[1;37m"


.PHONY: all clean fclean re run play auto rmmidi coffee
