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
	fprintf(stderr, "usage: sha256 [-o]\n");
	exit(1);
}

int
main(int argc, char *argv[])
{
	SHA256state st;
	uchar buf[32*1024];
	int n;
	uchar hash[SHA256dlen];
	char shash[2*SHA256dlen+1];
	int sha224;
	int c;

	sha224 = 0;
	while((c = getopt(argc, argv, "o")) != -1)
		switch(c) {
		case 'o':
			sha224 = 1;
			break;
		default:
			usage();
		}
	argc -= optind;
	if(argc != 0)
		usage();

	sha256init(&st, sha224);
	for(;;) {
		n = read(0, buf, sizeof buf);
		if(n < 0) {
			fprintf(stderr, "read: %s\n", strerror(errno));
			exit(1);
		}
		if(n == 0)
			break;
		sha256(&st, buf, n);
	}
	sha256finish(&st, hash);
	n = sha224 ? SHA224dlen : SHA256dlen;
	hex(hash, n, shash);
	printf("%s\n", shash);
	exit(0);
}
