NAMEC := client
NAMES := server
LIB := minitalk.h
CFILESC := ft_atoi.c client.c ft_memset.c
CFILESS :=  ft_atoi.c server.c ft_memset.c ft_calloc.c
OFILESC := $(CFILESC:%.c=%.o)
OFILESS := $(CFILESS:%.c=%.o)
CFLAGS := -Wall -Wextra -Werror -I ft_printf
CC := cc
PRINTF := ft_printf/libftprintf.a
all: $(NAMES) $(NAMEC)
$(NAMES): $(OFILESS) 
	$(MAKE) -C ft_printf
	$(CC) $(OFILESS) $(PRINTF) -o server $(CFLAGS)
$(NAMEC): $(OFILESC)
	$(MAKE) -C ft_printf
	$(CC) $(OFILESC) $(PRINTF) -o client $(CFLAGS)
%.o: %.c $(LIB)
	$(CC) -Wall -Wextra -Werror $< -c
clean:
	$(MAKE) -C ft_printf clean
	rm -rf $(OFILESS) $(OFILESC)
fclean: clean
	$(MAKE) -C ft_printf fclean
	rm -rf  $(NAMES) $(NAMEC)
re: fclean all

.PHONY:	clean fclean re all