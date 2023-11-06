# Philosopher - Philosphe problem with threads and mutexes

# Compile Instructions
NAME = 	philo
FLAGS =	-g -Wall -Wextra -Werror -pthread

# Directories
SRC_FOLDER =	src/
SRC_FILES =		main.c p_utils.c p_verifs.c p_init.c philo.c p_utils2.c
OBJS = $(addprefix $(SRC_FOLDER), $(SRC_FILES:%.c=%.o))

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
	@gcc $(FLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(DEFAULT)"

all: $(NAME)

clean:
	@rm -rf $(OBJS)
	@echo "$(RED)$(NAME) cleaned successfully!$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) executable files cleaned!$(DEFAULT)"
	@echo "$(RED)philosophers as cleaned!$(DEFAULT)"

re: fclean all
	@echo "$(GREEN)$(NAME) recompiled successfully!$(DEFAULT)"

norm:
	@norminette $(SRC_FOLDER) | grep -v Norme -B1 || true

.PHONY: all clean fclean re norm

