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
SRCDIR_BRD = board/
SRCDIR_CLN = client/
SRCDIR_COM = communication/
SRCDIR_DTH = death/
SRCDIR_EGG = egg/
SRCDIR_EVS = events/
SRCDIR_EVS_GFX = graphic/
SRCDIR_EVS_VHC = vehicle/
SRCDIR_EVS_SRV = server/
SRCDIR_GFX = graphic/
SRCDIR_GFX_TRS = transmit/
SRCDIR_INV = inventory/
SRCDIR_PLR = vehicle/
SRCDIR_SRV = server/
SRCDIR_TEM = team/
SRCDIR_TIM = time/

OBJSRC = $(patsubst %, %.o, $(addprefix $(SRCDIR), $(SRC)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		 $(addprefix $(SRCDIR), $(SRCDIR_BRD)), \
		 $(SRC_BRD)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_CLN)), \
		  $(SRC_CLN)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_COM)), \
		  $(SRC_COM)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_DTH)), \
		  $(SRC_DTH)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_EVS)), \
		  $(SRC_EVS)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), \
		  $(addprefix $(SRCDIR_EVS), $(SRCDIR_EVS_GFX))), \
		  $(SRC_EVS_GFX)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), \
		  $(addprefix $(SRCDIR_EVS), $(SRCDIR_EVS_VHC))), \
		  $(SRC_EVS_VHC)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), \
		  $(addprefix $(SRCDIR_EVS), $(SRCDIR_EVS_SRV))), \
		  $(SRC_EVS_SRV)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_GFX)), \
		  $(SRC_GFX)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), \
		  $(addprefix $(SRCDIR_GFX), $(SRCDIR_GFX_TRS))), \
		  $(SRC_GFX_TRS)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_INV)), \
		  $(SRC_INV)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_PLR)), \
		  $(SRC_VHC)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_SRV)), \
		  $(SRC_SRV)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_TEM)), \
		  $(SRC_TEM)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_TIM)), \
		  $(SRC_TIM)))

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

SRC_BRD = \
	board \

SRC_CLN = \
	client

SRC_COM = \
	communication

SRC_ERR = \
	error

SRC_EVS = \
	events \
	pool \
	queue

SRC_EVS_VHC = \
	commands

SRC_GFX = \
	graphic

SRC_GFX_TRS = \
	transmit \
	tiles \
	vehicles \

SRC_VHC = \
	place \
	vehicle \
	pool \

SRC_SRV = \
	server \
	opts \

SRC_TIM = \
	time

SRC = \
	main

################################################################################
# SOURCE FILES                                                                 #
################################################################################

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
