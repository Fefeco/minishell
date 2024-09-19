# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davifer2 <davifer2@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 13:06:50 by davifer2          #+#    #+#              #
#    Updated: 2024/06/26 16:33:43 by fcarranz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEL_LINE =		\033[2K
ITALIC =		\033[3m
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m

NAME = libft.a

CC = gcc -Iinc
CFLAGS = -Wall -Werror -Wextra -MMD -g

GNL_DIR = src/gnl
PRINTF_DIR = src/printf

SRC_PATH = src/
OBJS_PATH = objects/
DEPS_PATH = deps/

SOURCES_LIBFT = src/ft_atoi.c \
				src/ft_bzero.c \
				src/ft_calloc.c \
				src/ft_itoa.c \
				src/ft_isalnum.c \
				src/ft_isalpha.c \
				src/ft_isascii.c \
				src/ft_isdigit.c \
				src/ft_isprint.c \
				src/ft_memchr.c \
				src/ft_memcmp.c \
				src/ft_memcpy.c \
				src/ft_memmove.c \
				src/ft_memset.c \
				src/ft_putchar_fd.c \
				src/ft_putendl_fd.c \
				src/ft_putnbr_fd.c \
				src/ft_putstr_fd.c \
				src/ft_split.c \
				src/ft_strchr.c \
				src/ft_strdup.c \
				src/ft_striteri.c \
				src/ft_strlcat.c \
				src/ft_strlcpy.c \
				src/ft_strlen.c \
				src/ft_strmapi.c \
				src/ft_strncmp.c \
				src/ft_strnstr.c \
				src/ft_strrchr.c \
				src/ft_strtrim.c \
				src/ft_substr.c \
				src/ft_tolower.c \
				src/ft_toupper.c \
				src/ft_lstnew_bonus.c \
				src/ft_lstsize_bonus.c \
				src/ft_lstadd_back_bonus.c \
				src/ft_lstadd_front_bonus.c	\
				src/ft_lstlast_bonus.c \
				src/ft_lstdelone_bonus.c \
				src/ft_lstclear_bonus.c \
				src/ft_lstiter_bonus.c \
				src/ft_lstmap_bonus.c

SOURCES_GNL = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

SOURCES_PRINTF = $(PRINTF_DIR)/ft_printf.c $(PRINTF_DIR)/ft_hexlen.c \
	$(PRINTF_DIR)/ft_nbrlen.c $(PRINTF_DIR)/ft_nbrunsiglen.c \
	$(PRINTF_DIR)/ft_printchar_fd.c $(PRINTF_DIR)/ft_printhex_fd.c \
	$(PRINTF_DIR)/ft_printnbr_fd.c $(PRINTF_DIR)/ft_printnbrunsig_fd.c \
	$(PRINTF_DIR)/ft_printstr_fd.c

SOURCES = $(SOURCES_LIBFT) $(SOURCES_GNL) $(SOURCES_PRINTF)
OBJS = $(addprefix $(OBJS_PATH), $(SOURCES:.c=.o))
DEPS = ${addprefix $(DEPS_PATH), $(SOURCES:.c=.d)}

all: $(NAME)

$(NAME): $(OBJS) inc/libft.h Makefile
	@echo "\n"
	@echo "$(YELLOW)Compiling libft...\n"
	@echo "$(DEF_COLOR)"
	ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)\n"
	@echo "	===============	"
	@echo "	 libft created	"
	@echo "	===============	"
	@echo "\n"
	@echo "$(DEF_COLOR)"

$(OBJS_PATH)%.o: %.c inc/libft.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(DEF_COLOR)$(GREEN)Creating object $(DEF_COLOR)- $(BLUE)$@"
	@mkdir -p $(subst $(OBJS_PATH),$(DEPS_PATH),$(@D))
	@mv $(patsubst %.o,%.d,$@) $(subst $(OBJS_PATH),$(DEPS_PATH),$(@D))/

clean:
	@rm -rf $(OBJS_PATH) $(DEPS_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all
	
-include $(DEPS)

.PHONY: all clean fclean re
