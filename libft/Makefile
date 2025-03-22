.PHONY = all clean fclean re
CC = cc
FLAGS = -Wall -Wextra -Werror -MMD -MP  -Iincludes
NAME = libft.a
SRC_DIR = srcs/
SRC_FILES = ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_strchr ft_strdup ft_strlcat ft_strlcpy ft_strlen ft_strncmp ft_strnstr ft_strrchr ft_substr ft_tolower ft_toupper ft_substr ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi  ft_striteri ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_lstadd_back_bonus ft_lstadd_front_bonus ft_lstnew_bonus ft_lstsize_bonus  \
ft_lstlast_bonus ft_lstdelone_bonus ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus
SRC_FILES += ft_print_hexa ft_printf_format ft_printf
SRC_FILES += get_next_line_utils get_next_line
OBJ_DIR = objs/

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

${NAME}: $(OBJ_DIR) ${OBJ} 
	ar rcs ${NAME}	${OBJ}

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -c $< -o $@
-include $(DEPS)

all: ${NAME} 
clean:
	rm -rf ${OBJ_DIR} 
fclean:
	${MAKE} clean 
	rm -f ${NAME}
re: 
	${MAKE} fclean 
	${MAKE} all	