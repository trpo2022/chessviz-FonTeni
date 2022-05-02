CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD

CC = gcc
SR_MA = src/main/
SR_LI = src/libchessviz/

main.exe: obj/$(SR_LI)chessviz.o  obj/$(SR_MA)main.o
	$(CC) $(CFLAGS) -o bin/$@ $^

obj/$(SR_LI)chessviz.o: $(SR_LI)chessviz.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

obj/$(SR_MA)main.o: $(SR_MA)main.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

-include main.d hello.d

clean:
	rm obj/$(SR_MA)*.o obj/$(SR_LI)*.o bin/*.exe