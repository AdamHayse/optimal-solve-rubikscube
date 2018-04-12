CC ?=gcc
CPPFLAGS ?=
CFLAGS ?=-std=c99 -Wall -Wextra -pedantic -O2 -g

BINS=generateEDB1_6 generateEDB2_6 generateEDB1_7 generateEDB2_7 generateEDB1_8 generateEDB2_8 generateCDB testheuristic IDAstar

all: $(BINS)

generateEDB1 generateEDB2: generateEDB%: generateEDB.c moves.c edatabase.c mymath.c database.c
	$(CC) $(CPPFLAGS) -D HALF=$* $(CFLAGS) $^ -o $@

generateEDB1: generateEDB.c moves.c edatabase.c mymath.c database.c
generateCDB: moves.c cdatabase.c edatabase.c mymath.c database.c
testheuristic: searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c
IDAstar:  searchmoves.c cdatabase.c edatabase.c IDAstar.c mymath.c do_search.c
clean:
	@$(RM) -v $(BINS) $(BINS:=.d)

.PHONY: all clean
.SUFFIXES:
.SUFFIXES: .c
