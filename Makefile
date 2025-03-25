.PHONY = all clean fclean re bonus
CC = cc 
FLAGS = -Wall -Wextra -Werror -MMD -MP  -I$(LIBFT_DIR)/includes -Iincludes
FLAGLIBFT = -L$(LIBFT_DIR) -lft
NAME = pipex
NAME_BONUS = pipex_bonus
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
SRC_DIR = srcs/
SRC_BONUS_DIR = bonus/
SRC_FILES = main execve_first execve_last free parsing messages execve_middle exec_env
OBJ_DIR = objs/

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
SRC_BONUS = $(addprefix $(SRC_BONUS_DIR), $(addsuffix _bonus.c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJ_BONUS = $(addprefix $(OBJ_DIR), $(addsuffix _bonus.o, $(SRC_FILES)))
DEPS = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

all: $(NAME)

$(NAME): includes/pipex.h $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(FLAGLIBFT)

bonus: $(NAME_BONUS)

$(NAME_BONUS): includes/pipex.h $(LIBFT) $(OBJ_DIR) $(OBJ_BONUS)
	$(CC) $(FLAGS) $(OBJ_BONUS) -o $(NAME_BONUS) $(FLAGLIBFT)

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

FORCE:

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -c $< -o $@
    
$(OBJ_DIR)%_bonus.o: $(SRC_BONUS_DIR)%_bonus.c
	$(CC) $(FLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	rm -f $(LIBFT)

re: fclean all