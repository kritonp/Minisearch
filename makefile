OBJS = main.o trie.o postingList.o utils.o
SOURCE = main.c trie.c postingList.c utils.c
HEADER = trie.h postingList.h utils.h
OUT = minisearch
CC = gcc
FLAGS = -g3 -c
LIB 	= -lm

all: $(OBJS)
	$(CC) -Wall -Werror -g $(OBJS) $(LIB) -o $(OUT)

main.o: main.c
	$(CC) $(FLAGS) main.c

trie.o: trie.c
	$(CC) $(FLAGS) trie.c

postingList.o: postingList.c
	$(CC) $(FLAGS) postingList.c

utils.o: utils.c
	$(CC) $(FLAGS) utils.c

# clean up
clean:
	rm -f $(OBJS) $(OUT)
