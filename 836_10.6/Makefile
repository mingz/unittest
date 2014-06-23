EXE  = ucGO
OBJS = main.o
OBJS += PREM-8497/suite.o
LIBS = -lcunit -lcurses
CC = gcc

%.o: %.c
	$(CC) -c -o $@ -I/usr/local/include/CUnit $<

ucGO: $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

clean:
	-rm -f ucGO
	-rm -f *.o
	-rm -f PREM-8497/*.o

