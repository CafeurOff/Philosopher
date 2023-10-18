# Philosopher - Philosphe problem with threads and mutexes

# Compile Instructions
NAME = 	philo
SANIFLAG = 	-g
FLAGS =	-g -Wall -Wextra -Werror -pthread

# Directories
SRC_FOLDER =	src/
SRC_FILES =		main.c p_utils.c p_verifs.c p_init.c philo.c
OBJS = $(addprefix $(SRC_FOLDER), $(SRC_FILES:%.c=%.o))

# Other lib includes
LIBFT_PATH =	inc/libft/
LIBFT_LIB =		$(LIBFT_PATH)libft.a
# Some colors
DEFAULT		=	\033[0;39m
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m

# Variables for progress tracking
TOTAL := $(words $(OBJS))
PROGRESS := 0

# Function to print progress
define print_progress
	$(eval PROGRESS := $(shell expr $(PROGRESS) + 1))
	$(eval PERCENT := $(shell echo "$$(($(PROGRESS) * 100 / $(TOTAL)))"))
	@printf "[%3d%%] Compiling $1...\n" $(PERCENT)
endef

# Rules
%.o: %.c
	@$(call print_progress,$<)
	@gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@make -C $(LIBFT_PATH) --no-print-directory -s
	@gcc $(FLAGS) $(OBJS) $(LIBFT_LIB) $(PRINTF_LIB) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(DEFAULT)"

all: $(NAME)

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT_PATH) --no-print-directory -s
	@echo "$(RED)$(NAME) cleaned successfully!$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH) --no-print-directory -s
	@echo "$(RED)$(NAME) executable files cleaned!$(DEFAULT)"
	@echo "$(RED)philosophers as cleaned!$(DEFAULT)"

re: fclean all
	@echo "$(GREEN)$(NAME) recompiled successfully!$(DEFAULT)"

norm:
	@norminette $(SRC_FOLDER) $(LIBFT_PATH) | grep -v Norme -B1 || true

.PHONY: all clean fclean re norm

