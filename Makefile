SRV = server
LIB = libft.a
LIBDEBUG = ""
CFLAGS += -Wall -Werror -Wextra
INCLUDES = -I inc/ -I lib/inc/
LINK = -L lib/ -l ft
CC = gcc

################################################################################
# Source directories identifiers                                               #
################################################################################

SRCDIR_BRD = src/board/
SRCDIR_CLN = src/client/
SRCDIR_CMD = src/commands/
SRCDIR_CQU = src/commandqueue/
SRCDIR_COM = src/communication/
SRCDIR_INV = src/inventory/
SRCDIR_PLR = src/player/
SRCDIR_SRV = src/server/
SRCDIR_TEM = src/team/

OBJSRC = $(patsubst %, %.o, $(addprefix $(SRCDIR_BRD), $(SRC_BRD)))
OBJSRC += $(patsubst %, %.o, $(addprefix $(SRCDIR_CLN), $(SRC_CLN)))
OBJSRC += $(patsubst %, %.o, $(addprefix $(SRCDIR_CQU), $(SRC_CQU)))
OBJSRC += $(patsubst %, %.o, $(addprefix $(SRCDIR_COM), $(SRC_COM)))
OBJSRC += $(patsubst %, %.o, $(addprefix $(SRCDIR_INV), $(SRC_INV)))
OBJSRC += $(patsubst %, %.o, $(addprefix $(SRCDIR_PLR), $(SRC_PLR)))
OBJSRC += $(patsubst %, %.o, $(addprefix $(SRCDIR_SRV), $(SRC_SRV)))
OBJSRC += $(patsubst %, %.o, $(addprefix $(SRCDIR_TEM), $(SRC_TEM)))

#OBJSRC = $(patsubst %, %.o, $(addprefix \
#		 $(addprefix $(SRCDIR), $(SRCDIR_IO)), \
#		 $(SRC_IO)))
#OBJSRC += $(patsubst %, %.o, $(addprefix \
#		  $(addprefix $(SRCDIR), \
#		  $(addprefix $(SRCDIR_IO), $(SRCDIR_IO_FTPRINTF))), \
#		  $(SRC_IO_FTPRINTF)))

################################################################################
# COLOR                                                                        #
################################################################################

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RES = \033[0m

################################################################################
# SOURCE FILES                                                                 #
################################################################################

SRC_BRD =	\
	board		

SRC_CLN =	\
	client

SRC_CQU =	\
	commandqueue

SRC_COM =	\
	comms

SRC_INV =	\
	inventory

SRC_PLR =	\
	player

SRC_SRV =	\
	error \
	io \
	smain \
	srv_sets1 \
	srv_sets2 \
	time

SRC_TEM =	\
	team

all: $(LIB) $(SRV)

debug: CFLAGS += -g -fsanitize=address -fsanitize=null -DDEBUG
debug: $(LIBDEBUG)
debug: $(SRV)

$(SRV): $(OBJSRC)
	@ echo "$(CYAN)Compiling binary$(RES)"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJSRC) $(LINK) -o $(SRV)
	@ echo "$(GREEN)$(SRV) Made$(RES)"

$(LIB):
	make -C lib/

$(LIBDEBUG):
	make debug -C lib/

%.o: %.c
	@ echo "$(YELLOW)Compiling $<...$(RES)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJSRC)
	make clean -C lib/
	@ echo "$(RED)Cleaning folders of object files...$(RES)"

fclean: clean
	rm -f $(SRV)
	rm -f lib/$(LIB)
	@ echo "$(RED)Removing program...$(RES)"

re: fclean all
	@ echo "$(GREEN)Program Remade$(RES)"
