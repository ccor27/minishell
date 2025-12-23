# NAME = minishell
# #LIBFT
# #AR
# INCLUDES = -I includes

# SRC_MAIN	=	minishell.c
# SRC_UTILS	=	signals.c
# #SRC_ERROR =
# #SRC_PROCESS =
# SRC_VALIDATION =	parse.c
# SRC_FILES = $(addprefix main/,$(SRC_MAIN))	\
# 			$(addprefix utils/,$(SRC_UTILS))	\
# 			$(addprefix validation/,$(SRC_VALIDATION))

# SRC = $(addprefix src/,$(SRC_FILES))
# OBJ_DIR= obj
# OBJ= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# CC  = gcc
# CFLAGS = -Wall -Wextra -Werror

# define LOADING_BAR_COMP
# 	@printf "\033[0;32mCompiling minishell: ["
# 	@for i in `seq 1 20`; do \
# 		printf "█"; \
# 		sleep 0.05; \
# 	done; \
# 	printf "] ✔️\033[0m\n\n"
# endef

# define LOADING_BAR_CLEAN
# 	@printf "\033[0;31mCleaning objects: ["
# 	@for i in `seq 1 20`; do \
# 		printf "█"; \
# 		sleep 0.05; \
# 	done; \
# 	printf "] ✔️\033[0m\n\n"
# endef

# all: $(NAME)

# $(NAME): $(OBJ)
# 	$(call  LOADING_BAR_COMP)
# 	@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

# # THE CRITICAL PART: The indentation below MUST be a TAB
# $(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# clean:
# 	@rm -rf $(OBJ_DIR)
# 	$(call LOADING_BAR_CLEAN)

# fclean: clean
# 	@rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re

NAME        = minishell

# --- FILES ---
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
SRC_MAIN    = minishell.c
SRC_UTILS   = signals.c visual_effects.c parse_utils.c
SRC_VALID   = parse_tokens.c

INCLUDES    = -I includes -I$(LIBFT_DIR)

# Combine files with their folder prefixes
SRC_FILES   = $(addprefix main/,$(SRC_MAIN)) \
              $(addprefix utils/,$(SRC_UTILS)) \
              $(addprefix validation/,$(SRC_VALID))

# Add 'src/' prefix to everything
SRC         = $(addprefix src/,$(SRC_FILES))

# --- OBJECTS ---
OBJ_DIR     = obj
OBJ         = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# --- COMPILER ---
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror

# --- LOADING BAR ---
define LOADING_BAR_COMP
	@printf "\033[0;32mCompiling minishell: ["
	@for i in `seq 1 20`; do \
		printf "█"; \
		sleep 0.05; \
	done; \
	printf "] ✔️\033[0m\n\n"
endef

define LOADING_BAR_CLEAN
	@printf "\033[0;31mCleaning objects: ["
	@for i in `seq 1 20`; do \
		printf "█"; \
		sleep 0.05; \
	done; \
	printf "] ✔️\033[0m\n\n"
endef

# --- RULES ---
all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) --silent
	$(call LOADING_BAR_COMP)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# THE CRITICAL PART: The indentation below MUST be a TAB
$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --silent
	$(call LOADING_BAR_CLEAN)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent

re: fclean all

.PHONY: all clean fclean re
