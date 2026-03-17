NAME        = minishell

# --- FILES ---
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
SRC_MAIN    = minishell.c
SRC_UTILS   = signals.c visual_effects.c parse_token_utils.c parse_cmd_utils.c env_utils.c
SRC_VALID   = parse_tokens.c parse_cmd.c
SRC_PROCESS = here_doc_handler.c expanders.c expanders_utils.c execute_external.c execute_redirect.c \
				executor.c
SRC_ERRORS	= error_handler.c free_helper.c
SRC_BUILT_IN = cd.c echo.c env.c exit.c export.c pwd.c unset.c

INCLUDES    = -I includes -I$(LIBFT_DIR)

# Combine files with their folder prefixes
SRC_FILES   = $(addprefix main/,$(SRC_MAIN)) \
              $(addprefix utils/,$(SRC_UTILS)) \
              $(addprefix validation/,$(SRC_VALID)) \
			  $(addprefix process/,$(SRC_PROCESS)) \
			  $(addprefix errors/,$(SRC_ERRORS))	\
			  $(addprefix built_in/,$(SRC_BUILT_IN))

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
