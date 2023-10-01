# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 17:15:50 by pdubois           #+#    #+#              #
#    Updated: 2023/08/06 17:15:50 by pdubois          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

NAME = ircserv

RM = rm -rf

SRCS_NAME =	main.cpp \
			Channel.cpp \
			Server.cpp \
			User.cpp \
			network.cpp \
			Command.cpp \
			parser.cpp \
			signals.cpp \
			Support.cpp \
			command/check_command.cpp \
			command/invite.cpp \
			command/join.cpp \
			command/kick.cpp \
			command/mode.cpp \
			command/msg.cpp \
			command/nick.cpp \
			command/part.cpp \
			command/pass.cpp \
			command/ping.cpp \
			command/privmsg.cpp \
			command/quit.cpp \
			command/topic.cpp \
			command/user.cpp
SRCS_PATH =	srcs
SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_NAME))

INCS_NAME =	irc.hpp \
			Channel.hpp \
			Server.hpp \
			User.hpp \
			Command.hpp \
			Support.hpp \
			rpl_err_command.hpp
INCS_PATH =	includes
INCS = $(addprefix $(INCS_PATH)/, $(INCS_NAME))

OBJS = ${SRCS:.cpp=.o}

all: ${NAME}

%.o : %.cpp ${INCS}
	${CC} ${CFLAGS} -I ${INCS_PATH} -c $< -o $@

${NAME}: ${OBJS} ${INCS}
	${CC} -o ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re