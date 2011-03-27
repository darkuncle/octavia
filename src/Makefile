# Need these for MacFUSE:
CFLAGS += -D__FreeBSD__=10 -D_FILE_OFFSET_BITS=64 -Wall -Wextra -O2 -Werror -ansi -pedantic -std=c99

LDFLAGS += -L/usr/local/ssl/lib -lcrypto -lfuse

SOURCES = octavia.c octavia-fuse.c util.c
HEADERS = minunit.h octavia.h util.h

8va: $(SOURCES) $(HEADERS)
	$(CC) -o $@ $(CFLAGS) $(SOURCES) $(LDFLAGS)

clean:
	-rm 8va *.pb.{cc,h}

