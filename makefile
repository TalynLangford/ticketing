CC=g++
CFLAGS=g++ -std=c++17 -Wall -Wextra -pedantic-errors -I
DEPS = IService.h Server.h Testing.h TicketingSystem.h
OBJ = Server.o Startup.o Testing.o TicketingSystem.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

startup: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)