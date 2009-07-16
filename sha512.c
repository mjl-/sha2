#include "types.h"
#include <errno.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "util.h"
#include "sha2.h"

void
usage(void)
{
	fprintf(stderr, "usage: sha512 [-o]\n");
	exit(1);
}

int
main(int argc, char *argv[])
{
	SHA512state st;
	uchar buf[32*1024];
	int n;
	uchar hash[SHA512dlen];
	char shash[2*SHA512dlen+1];
	int sha384;
	int c;

	sha384 = 0;
	while((c = getopt(argc, argv, "o")) != -1)
		switch(c) {
		case 'o':
			sha384 = 1;
			break;
		default:
			usage();
		}
	argc -= optind;
	if(argc != 0)
		usage();

	sha512init(&st, sha384);
	for(;;) {
		n = read(0, buf, sizeof buf);
		if(n < 0) {
			fprintf(stderr, "read: %s", strerror(errno));
			exit(1);
		}
		if(n == 0)
			break;
		sha512(&st, buf, n);
	}
	sha512finish(&st, hash);
	n = sha384 ? SHA384dlen : SHA512dlen;
	hex(hash, n, shash);
	printf("%s\n", shash);
	exit(0);
}
