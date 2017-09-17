NAME=a.out
CC=gcc
LIBS=-lm
OPTS=-std=c11 -g 

SRCs= *.[ch]

all:  
	$(CC) $(LIBS) $(OPTS) $(SRCs) -o $(NAME)



.PHONY clean:
	rm *.o *.gch $(NAME)

