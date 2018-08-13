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

SRCDIR = src/
SRCDIR_COM = communication/
SRCDIR_EVS = events/
SRCDIR_EVS_VHC = vehicle/
SRCDIR_GFX = graphic/
SRCDIR_TRS = transmit/
SRCDIR_SRV = server/
SRCDIR_VHC = vehicle/

OBJSRC = $(patsubst %, %.o, $(addprefix $(SRCDIR), $(SRC)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_COM)), \
		  $(SRC_COM)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_EVS)), \
		  $(SRC_EVS)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), \
		  $(addprefix $(SRCDIR_EVS), $(SRCDIR_EVS_VHC))), \
		  $(SRC_EVS_VHC)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_GFX)), \
		  $(SRC_GFX)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_TRS)), \
		  $(SRC_TRS)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_SRV)), \
		  $(SRC_SRV)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_VHC)), \
		  $(SRC_VHC)))

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

SRC_COM = \
	communication

SRC_EVS = \
	events \
	pool \
	queue

SRC_EVS_VHC = \
	commands

SRC_GFX = \
	graphic

SRC_TRS = \
	transmit \
	tiles \
	vehicles \

SRC_SRV = \
	server \
	opts \

SRC_VHC = \
	place \
	vehicle \
	pool \

SRC = \
	board \
	client \
	main \
	socket \
	time

################################################################################
# SOURCE FILES                                                                 #
################################################################################

all: $(LIB) $(SRV)

libft: $(LIB)

debug: CFLAGS += -g -fsanitize=address -fsanitize=null -DDEBUG
debug: $(SRV)

ldebug: $(LIBDEBUG)

$(SRV): $(OBJSRC)
	@ echo "$(CYAN)Compiling binary$(RES)"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJSRC) $(LINK) -o $(SRV)
	@ echo "$(GREEN)$(SRV) Made$(RES)"

$(LIB):
	@ git submodule init
	@ git submodule update
	make -C lib/

$(LIBDEBUG):
	make debug -C lib/

%.o: %.c
	@ echo "$(YELLOW)Compiling $<...$(RES)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@ echo "$(RED)Cleaning folders of object files...$(RES)"
	rm -f $(OBJSRC)

lclean:
	make clean -C lib/

lfclean:
	rm -f lib/$(LIB)

fclean: clean
	@ echo "$(RED)Removing program...$(RES)"
	rm -f $(SRV)

re: fclean all
	@ echo "$(GREEN)Program Remade$(RES)"
