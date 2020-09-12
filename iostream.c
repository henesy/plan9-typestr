#include <u.h>
#include <libc.h>

// Fron: http://www.9paste.net/qrstuv/iostream.c

typedef enum {
	IOfd,
	IOchar,
	IOint,
} IOtype;

typestr struct _iostream {
	IOtype	type;
	union {
		int	fd;
		char	c;
		int	i;
	};
} IOstream;

char *iofmtstr[] = {
	[IOfd]	= "%d",
	[IOchar]	= "%c",
	[IOint]	= "%d",
};

IOstream
_i_iostream_(int i)
{
	IOstream io;

	io.type = IOint;
	io.i = i;
	return io;
}

IOstream
_iostream_ashl_(IOstream s, IOstream x)
{
	assert(s.type == IOfd);
	fprint(s.fd, iofmtstr[x.type], x.i);
	return s;
}

IOstream
mkiostream(int fd)
{
	IOstream io;

	io.type = IOfd;
	io.fd = fd;
	return io;
}

IOstream
iochar(char c)
{
	IOstream io;

	io.type = IOchar;
	io.c = c;
	return io;
}

void
main(int, char **)
{
	IOstream cout, nl;

	cout = mkiostream(1);
	nl = iochar('\n');

	cout << (IOstream)4 << nl;

	exits(nil);
}

