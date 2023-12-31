# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/01 11:14:25 by gacorrei          #+#    #+#              #
#    Updated: 2023/12/06 20:01:30 by joao-per         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ircserv
SRCDIR	= src
OBJDIR	= objs
SRCS	= 	$(SRCDIR)/main.cpp \
			$(SRCDIR)/Server.cpp \
			$(SRCDIR)/ServerConnection.cpp \
			$(SRCDIR)/ServerCommands.cpp \
			$(SRCDIR)/ServerUtils.cpp \
			$(SRCDIR)/Client.cpp \
			$(SRCDIR)/Channel.cpp \
			$(SRCDIR)/Bot.cpp

# Colors

DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
CURSIVE	= \e[33;3m

CXX		= c++
CXXFLAGS = -Wall -Wextra -Werror -Wshadow -std=c++98 -I includes -g #-fsanitize=address
# FOR DEBUGGER TO SHOW STD::STRING
CFLAGSD	= -Wall -Wextra -Werror -pedantic -Wshadow -g -fno-limit-debug-info -std=c++98 -fsanitize=address,undefined
OBJS	= $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Commands
RM		= rm -rf


all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(MAGENTA)- Compiling $(NAME)... $(DEFAULT)"
	@$(CXX) $(OBJS) $(CXXFLAGS) -o  $(NAME)
	@printf "$(GREEN)- ircserv Compiled!$(DEFAULT)"

%.o: %.cpp
	@echo "$(CURSIVE)$(YELLOW)- Compiling $<... $(DEFAULT)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJDIR)
	@echo "$(RED)- OBJS Removed.$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)- ircserv Removed.$(DEFAULT)"

re:			fclean all

debug:		$(SRC)
			$(CC) $(CFLAGSD) $(^) -o $(NAME)

valgrind:	$(NAME)
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(NAME) 6697 pass

.PHONY:		all clean re fclean