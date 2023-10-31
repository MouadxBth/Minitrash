NAMEC := client
NAMES := server
BNAMEC := client_bonus
BNAMES := server_bonus
LIB := minitalk.h
CFILESC := ft_atoi.c client.c ft_memset.c
CFILESS :=  ft_atoi.c server.c ft_memset.c
BONUSC := ft_atoi.c client_bonus.c ft_memset.c
BONUSS := ft_atoi.c server_bonus.c ft_memset.c
OFILESC := $(CFILESC:%.c=%.o)
OFILESS := $(CFILESS:%.c=%.o)
BFILESC := $(BONUSC:%.c=%.o)
BFILESS := $(BONUSS:%.c=%.o)
CFLAGS := -Wall -Wextra -Werror
CC := cc
PRINTF := ft_printf/libftprintf.a
all: $(NAMES) $(NAMEC)
$(NAMES): $(OFILESS) 
	$(MAKE) -C ft_printf
	$(CC) $(OFILESS) $(PRINTF) -o server $(CFLAGS)
$(NAMEC): $(OFILESC)
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

bonus: $(BNAMEC) $(BNAMES)

$(BNAMES): $(BFILESS) 
	$(MAKE) -C ft_printf
	$(CC) $(BFILESS) $(PRINTF) -o server_bonus $(CFLAGS)
$(BNAMEC): $(BFILESC)
	$(CC) $(BFILESC) $(PRINTF) -o client_bonus $(CFLAGS)

.PHONY:	clean fclean re all