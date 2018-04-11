CC ?=gcc
CPPFLAGS ?=
CFLAGS ?=-std=c99 -Wall -Wextra -pedantic -O2

BINS=generateEDB1 generateEDB2 generateCDB testheuristic IDAstar

all: $(BINS)

generateEDB1 generateEDB2: generateEDB%: generateEDB.c moves.c edatabase.c mymath.c database.c
	$(CC) $(CPPFLAGS) -D HALF=$* $(CFLAGS) $^ -o $@
generateCDB: moves.c cdatabase.c edatabase.c mymath.c database.c
testheuristic: moves.c cdatabase.c edatabase.c mymath.c database.c
IDAstar:  searchmoves.c cdatabase.c edatabase.c IDAstar.c mymath.c 
clean:
	@$(RM) -v $(BINS) $(BINS:=.d)

.PHONY: all clean
.SUFFIXES:
.SUFFIXES: .c
