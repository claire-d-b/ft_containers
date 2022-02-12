# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbertran <cbertran@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/08 23:26:34 by cbertran          #+#    #+#              #
#    Updated: 2021/08/13 13:38:40 by cbertran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX 		:=	clang++
NAME		:= 	TestContainers
SRCS		:=	main.cpp
OBJS		:=	$(SRCS:.cpp=.o) $(LIBRARY)
RM			:=	rm -f
LIBRARY		?=	-I ./ -I ../ -I ../includes/
CXXFLAGS	?=  -Wall -Wextra -Werror -std=c++98 $(LIBRARY)

$(NAME): $(OBJS)
	$(CXX) -o $(NAME) $(OBJS)

all: $(NAME)

fclean:
	$(RM) $(OBJS)
	$(RM) $(NAME)

clean:
	$(RM) $(OBJS)

re: fclean
	$(MAKE) all

test: fclean
	$(MAKE) all
	./$(NAME)