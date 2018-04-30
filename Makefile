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


CFLAGS ?=-std=c99 -Wall -Wextra -pedantic -O2

all: testscrambles6 testscrambles7 testscrambles8 generateCDB generateEDB1_6 generateEDB2_6 generateEDB1_7 generateEDB2_7 generateEDB1_8 generateEDB2_8 IDAstar6 IDAstar7 IDAstar8

# testbijective6 testbijective7 testbijective8

testscrambles6: testscrambles.c testheuristic.c searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c
	gcc -D TRACKED_EDGES=6 testscrambles.c testheuristic.c searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c $(CFLAGS) -o $@

testscrambles7: testscrambles.c testheuristic.c searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c
	gcc -D TRACKED_EDGES=7 testscrambles.c testheuristic.c searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c $(CFLAGS) -o $@

testscrambles8: testscrambles.c testheuristic.c searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c
	gcc -D TRACKED_EDGES=8 testscrambles.c testheuristic.c searchmoves.c cdatabase.c edatabase.c mymath.c database.c IDAstar.c $(CFLAGS) -o $@

generateCDB: generateCDB.c moves.c cdatabase.c mymath.c database.c
	gcc generateCDB.c moves.c cdatabase.c mymath.c database.c $(CFLAGS) -o $@

generateEDB1_6: generateEDB.c moves.c edatabase.c mymath.c database.c
	gcc -D HALF=1 -D TRACKED_EDGES=6 generateEDB.c moves.c edatabase.c mymath.c database.c $(CFLAGS) -o $@

generateEDB2_6: generateEDB.c moves.c edatabase.c mymath.c database.c
	gcc -D HALF=2 -D TRACKED_EDGES=6 generateEDB.c moves.c edatabase.c mymath.c database.c $(CFLAGS) -o $@

generateEDB1_7: generateEDB.c moves.c edatabase.c mymath.c database.c
	gcc -D HALF=1 -D TRACKED_EDGES=7 generateEDB.c moves.c edatabase.c mymath.c database.c $(CFLAGS) -o $@

generateEDB2_7: generateEDB.c moves.c edatabase.c mymath.c database.c
	gcc -D HALF=2 -D TRACKED_EDGES=7 generateEDB.c moves.c edatabase.c mymath.c database.c $(CFLAGS) -o $@

generateEDB1_8: generateEDB.c moves.c edatabase.c mymath.c database.c
	gcc -D HALF=1 -D TRACKED_EDGES=8 generateEDB.c moves.c edatabase.c mymath.c database.c $(CFLAGS) -o $@

generateEDB2_8: generateEDB.c moves.c edatabase.c mymath.c database.c
	gcc -D HALF=2 -D TRACKED_EDGES=8 generateEDB.c moves.c edatabase.c mymath.c database.c $(CFLAGS) -o $@

IDAstar6: do_search.c searchmoves.c edatabase.c cdatabase.c mymath.c database.c IDAstar.c
	gcc -D TRACKED_EDGES=6 do_search.c searchmoves.c edatabase.c cdatabase.c mymath.c database.c IDAstar.c $(CFLAGS) -o $@

IDAstar7: do_search.c searchmoves.c edatabase.c cdatabase.c mymath.c database.c IDAstar.c
	gcc -D TRACKED_EDGES=7 do_search.c searchmoves.c edatabase.c cdatabase.c mymath.c database.c IDAstar.c $(CFLAGS) -o $@

IDAstar8: do_search.c searchmoves.c edatabase.c cdatabase.c mymath.c database.c IDAstar.c
	gcc -D TRACKED_EDGES=8 do_search.c searchmoves.c edatabase.c cdatabase.c mymath.c database.c IDAstar.c $(CFLAGS) -o $@

# testbijective6: testbijective.c edatabase.c cdatabase.c mymath.c
# 	gcc -D TRACKED_EDGES=6 testbijective.c edatabase.c cdatabase.c mymath.c $(CFLAGS) -o $@

# testbijective7: testbijective.c edatabase.c cdatabase.c mymath.c
# 	gcc -D TRACKED_EDGES=7 testbijective.c edatabase.c cdatabase.c mymath.c $(CFLAGS) -o $@

# testbijective8: testbijective.c edatabase.c cdatabase.c mymath.c
# 	gcc -D TRACKED_EDGES=8 testbijective.c edatabase.c cdatabase.c mymath.c $(CFLAGS) -o $@

