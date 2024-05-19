# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: geymat <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/02 18:15:25 by geymat            #+#    #+#              #
#    Updated: 2024/05/15 06:18:05 by geymat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Wextra -Werror

HEADER = -I. 

DEPS =	average_header.h \
	struct_fork.h \
	struct_philo.h \
	struct_rules.h

SRCS =	fork.c \
	fork_utils.c \
	main.c \
	meal.c \
	philo.c \
	philo_utils.c \
	rules.c \
	table.c

OBJS_DIR = objs

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

-include $(OBJS:.o=.d)
$(OBJS_DIR)/%.o: srcs/%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -MMD -MP $(HEADER) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
