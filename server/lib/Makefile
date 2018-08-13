NAME = libft.a
CFLAGS += -Wall -Werror -Wextra
INCLUDES = -I inc/
CC = gcc

################################################################################
# Source directories identifiers                                               #
################################################################################

SRCDIR = src/
SRCDIR_IO = ft_io/
SRCDIR_IO_FTPRINTF = ft_printf/
SRCDIR_IO_GNL = gnl/
SRCDIR_IO_GETOPT = ft_getopts/
SRCDIR_LIST = ft_list/
SRCDIR_LIST_DBLIST = ft_dblist/
#SRCDIR_LIST_PQUEUE = ft_pqueue/
SRCDIR_LIST_QUEUE = ft_queue/
SRCDIR_LIST_SNGLIST = ft_snglist/
#SRCDIR_LIST_STACK = ft_stack/
SRCDIR_MEM = ft_memory/
SRCDIR_NUM = ft_num/
SRCDIR_STR = ft_string/

OBJSRC = $(patsubst %, %.o, $(addprefix \
		 $(addprefix $(SRCDIR), $(SRCDIR_IO)), \
		 $(SRC_IO)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), \
		  $(addprefix $(SRCDIR_IO), $(SRCDIR_IO_FTPRINTF))), \
		  $(SRC_IO_FTPRINTF)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), \
		  $(addprefix $(SRCDIR_IO), $(SRCDIR_IO_GNL))), \
		  $(SRC_IO_GNL)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), \
		  $(addprefix $(SRCDIR_IO), $(SRCDIR_IO_GETOPT))), \
		  $(SRC_IO_GETOPT)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), \
		  $(addprefix $(SRCDIR_LIST), $(SRCDIR_LIST_DBLIST))), \
		  $(SRC_LIST_DBLIST)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), \
		  $(addprefix $(SRCDIR_LIST), $(SRCDIR_LIST_QUEUE))), \
		  $(SRC_LIST_QUEUE)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), \
		  $(addprefix $(SRCDIR_LIST), $(SRCDIR_LIST_SNGLIST))), \
		  $(SRC_LIST_SNGLIST)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_MEM)), \
		  $(SRC_MEM)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_NUM)), \
		  $(SRC_NUM)))
OBJSRC += $(patsubst %, %.o, $(addprefix \
		  $(addprefix $(SRCDIR), $(SRCDIR_STR)), \
		  $(SRC_STR)))

################################################################################
# COLOR                                                                        #
################################################################################

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RES = \033[0m

################################################################################
# IO SOURCE FILES                                                              #
################################################################################

# AUTOCOMPLETE
SRC_IO =	\
     		 ft_putchar \
     		 ft_putchar_fd \
     		 ft_putendl \
     		 ft_putendl_fd \
     		 ft_putnbr \
     		 ft_putnbr_fd \
     		 ft_putstr \
     		 ft_putstr_fd

SRC_IO_FTPRINTF =	\
        	conversion_diou \
        	conversion_sc \
        	conversion_xp \
        	dispatcher \
        	misc \
        	printflags \
        	storeflags \
        	ulitobase

SRC_IO_GNL =	\
	        get_next_line

SRC_IO_GETOPT =	\
			ft_getopts

################################################################################
# LIST SOURCE FILES                                                            #
################################################################################

SRC_LIST_DBLIST =	\
	        ft_dblistnew \
			ft_dblistinsert \
	        ft_dblistpop \
			ft_dblistcritpop \
	        ft_dblmergesort

SRC_LIST_QUEUE =	\
        	ft_enqueue \
			ft_penqueue \
        	ft_popfirst \
        	ft_poplast \
        	ft_pushfirst \
        	ft_pushlast \
        	ft_queue_postmsort \
        	ft_queuedel \
			ft_middel

SRC_LIST_SNGLIST =	\
        	ft_listadd \
        	ft_listcritpop \
        	ft_listnew \
        	ft_sublistpop

################################################################################
# MEM SOURCE FILES                                                             #
################################################################################

SRC_MEM =	\
			ft_bzero \
			ft_memalloc \
			ft_memccpy \
			ft_memchr \
			ft_memcmp \
			ft_memcpy \
			ft_memdel \
			ft_memmove \
			ft_memset

################################################################################
# NUM SOURCE FILES                                                             #
################################################################################

SRC_NUM =	\
			ft_atoi \
			ft_atoi_base \
			ft_atol \
			ft_atol_base \
			ft_itoa \
			ft_numlen \
			ft_itoa_base \
			ft_uitoa_base \
			ft_nuitoa_base

################################################################################
# NUM SOURCE FILES                                                             #
################################################################################

SRC_STR =	\
			ft_nlookup \
			ft_nnlookup \
			ft_strcat \
			ft_strchr \
			ft_strclr \
			ft_strcmp \
			ft_strcpy \
			ft_strdel \
			ft_strdup \
			ft_strequ \
			ft_striter \
			ft_striteri \
			ft_strjoin \
			ft_strlcat \
			ft_strlen \
			ft_strmap \
			ft_strmapi \
			ft_strfreecat \
			ft_rstrfreecat \
			ft_strchr \
			ft_strcmp \
			ft_strcpy \
			ft_strnequ \
			ft_strnew \
			ft_strnstr \
			ft_strrchr \
			ft_strsplit \
			ft_strstr \
			ft_strsub \
        	ft_strncat \
        	ft_strnchr \
        	ft_strncmp \
        	ft_strncpy \
			ft_strtrim

################################################################################
# RULES                                                                        #
################################################################################

all: $(NAME)

debug: CFLAGS += -g -fsanitize=address -fsanitize=null -DDEBUG
debug: $(NAME)

$(NAME): $(OBJSRC)
	@ echo "$(CYAN)Building library$(RES)"
	ar -rc $@ $(OBJSRC)
	@ echo "$(GREEN)Library Made$(RES)"

%.o: %.c
	@ echo "$(CYAN)Compiling $<...$(RES)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@ echo "$(RED)Cleaning folders of object files...$(RES)"
	rm -f $(OBJSRC)

fclean: clean
	@ echo "$(RED)Removing library...$(RES)"
	rm -f $(NAME)

re: fclean all
	@ echo "$(GREEN)Library Remade$(RES)"
