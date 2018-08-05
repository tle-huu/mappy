# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/25 09:04:20 by tle-huu-          #+#    #+#              #
#    Updated: 2018/08/05 14:11:56 by tle-huu-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = execlient

SRCS = 	srcs/CommunicationSocket.cpp \
		srcs/Datagram.cpp
		lol.cpp

INCLUDES = includes/
OBJS = $(SRCS:.cpp=.o)

CXX = clang++
CXXFLAGS += -Wall -Wextra -Werror -std=c++11
# LDFLAGS +=  -Wall -Wextra -Werror -fsanitize=address

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) -I $(INCLUDES) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean all
