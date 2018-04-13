# CC ?=gcc
# CPPFLAGS ?=
# CFLAGS ?=-std=c99 -Wall -Wextra -pedantic -O2

# BINS=generateEDB1_6 generateEDB2_6 generateEDB1_7 generateEDB2_7 generateEDB1_8 generateEDB2_8 generateCDB testheuristic IDAstar

# all: $(BINS)

# generateEDB1_6 generateEDB2_6 generateEDB1_7 generateEDB2_7 generateEDB1_8 generateEDB2_8: generateEDB%: generateEDB.c moves.c edatabase.c mymath.c database.c
# 	$(CC) $(CPPFLAGS) -D HALF=$* -D TRACKED_EDGES=$* $(CFLAGS) $^ -o $@

# generateEDB1: generateEDB.c moves.c edatabase.c mymath.c database.c
# generateCDB: moves.c cdatabase.c edatabase.c mymath.c database.c
# testheuristic: searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c
# IDAstar:  searchmoves.c cdatabase.c edatabase.c IDAstar.c mymath.c do_search.c
# clean:
# 	@$(RM) -v $(BINS) $(BINS:=.d)

# .PHONY: all clean
# .SUFFIXES:
# .SUFFIXES: .c


CFLAGS ?=-std=c99 -mcmodel=medium -pedantic -O2

all: generateCDB testheuristic6 testheuristic7 testheuristic8 IDAstar6 generateEDB1_6 generateEDB2_6 generateEDB1_7 generateEDB2_7 generateEDB1_8 generateEDB2_8

generateEDB1_6: generateEDB.c moves.c edatabase.c mymath.c database.c
	gcc -D HALF=2 -D TRACKED_EDGES=6 generateEDB.c moves.c edatabase.c mymath.c database.c $(CFLAGS) -o $@

generateEDB1_7: generateEDB.c moves.c edatabase.c mymath.c database.c
	gcc -D HALF=2 -D TRACKED_EDGES=7 generateEDB.c moves.c edatabase.c mymath.c database.c $(CFLAGS) -o $@

generateEDB1_8: generateEDB.c moves.c edatabase.c mymath.c database.c
	gcc -D HALF=2 -D TRACKED_EDGES=8 generateEDB.c moves.c edatabase.c mymath.c database.c $(CFLAGS) -o $@

generateEDB2_6: generateEDB.c moves.c edatabase.c mymath.c database.c
	gcc -D HALF=2 -D TRACKED_EDGES=6 generateEDB.c moves.c edatabase.c mymath.c database.c $(CFLAGS) -o $@

generateEDB2_7: generateEDB.c moves.c edatabase.c mymath.c database.c
	gcc -D HALF=2 -D TRACKED_EDGES=7 generateEDB.c moves.c edatabase.c mymath.c database.c $(CFLAGS) -o $@

generateEDB2_8: generateEDB.c moves.c edatabase.c mymath.c database.c
	gcc -D HALF=2 -D TRACKED_EDGES=8 generateEDB.c moves.c edatabase.c mymath.c database.c $(CFLAGS) -o $@

generateCDB: generateCDB.c moves.c cdatabase.c mymath.c database.c
	gcc generateCDB.c moves.c cdatabase.c mymath.c database.c $(CFLAGS) -o $@

testheuristic6: testheuristic.c searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c
	gcc -D TRACKED_EDGES=6 testheuristic.c searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c $(CFLAGS) -o $@

testheuristic7: testheuristic.c searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c
	gcc -D TRACKED_EDGES=6 testheuristic.c searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c $(CFLAGS) -o $@

testheuristic8: testheuristic.c searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c
	gcc -D TRACKED_EDGES=6 testheuristic.c searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c $(CFLAGS) -o $@

IDAstar6: do_search.c searchmoves.c edatabase.c cdatabase.c mymath.c database.c IDAstar.c
	gcc -D TRACKED_EDGES=6 do_search.c searchmoves.c edatabase.c cdatabase.c mymath.c database.c IDAstar.c $(CFLAGS) -o $@

IDAstar7: do_search.c searchmoves.c edatabase.c cdatabase.c mymath.c database.c IDAstar.c
	gcc -D TRACKED_EDGES=7 do_search.c searchmoves.c edatabase.c cdatabase.c mymath.c database.c IDAstar.c $(CFLAGS) -o $@

IDAstar8: do_search.c searchmoves.c edatabase.c cdatabase.c mymath.c database.c IDAstar.c
	gcc -D TRACKED_EDGES=8 do_search.c searchmoves.c edatabase.c cdatabase.c mymath.c database.c IDAstar.c $(CFLAGS) -o $@

