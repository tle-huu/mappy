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

SRCDIR_SRV = src/server/

OBJSRC_SRV = $(patsubst %, %.o, $(addprefix $(SRCDIR_SRV), $(SRC_SRV)))
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

SRC_SRV =	\
	smain \
	srv_sets1 \
	srv_sets2 \
	process_incoming \
	create_board \
	client \
	srv_toclient \
	player \
	error
#	ublock_dispatch \
#	client_init \
#	msg_splits \
#	server_commands1 \
#	server_commands2 \
#	configurator \
#	server_client_comm \
#	channel_manager

all: $(LIB) $(SRV)

debug: CFLAGS += -g -fsanitize=address -fsanitize=null -DDEBUG
debug: $(LIBDEBUG)
debug: $(SRV)

$(SRV): $(OBJSRC_SRV)
	@ echo "$(CYAN)Compiling binary$(RES)"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJSRC_SRV) $(LINK) -o $(SRV)
	@ echo "$(GREEN)$(SRV) Made$(RES)"

$(LIB):
	make -C lib/

$(LIBDEBUG):
	make debug -C lib/

%.o: %.c
	@ echo "$(YELLOW)Compiling $<...$(RES)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJSRC_SRV)
	make clean -C lib/
	@ echo "$(RED)Cleaning folders of object files...$(RES)"

fclean: clean
	rm -f $(SRV)
	rm -f lib/$(LIB)
	@ echo "$(RED)Removing program...$(RES)"

re: fclean all
	@ echo "$(GREEN)Program Remade$(RES)"
