enum {
	SHA224dlen =	224/8,
	SHA256dlen =	256/8,
	SHA256bsize =	512/8,

	SHA384dlen =	384/8,
	SHA512dlen =	512/8,
	SHA512bsize =	1024/8,
};

struct SHA256state {
	uchar	smaller;
	uvlong	nb;
	uint	h[8];
	uchar	buf[SHA256bsize];
	uvlong	nbuf;
};

struct SHA512state {
	uchar	smaller;
	Uvvlong	nb;
	uvlong	h[8];
	uchar	buf[SHA512bsize];
	uint	nbuf;
};

typedef struct SHA256state SHA256state;
typedef struct SHA512state SHA512state;

void sha256init(SHA256state *st, int sha224);
void sha256(SHA256state *st, uchar *buf, int n);
void sha256finish(SHA256state *st, uchar *buf);

void sha512init(SHA512state *st, int sha384);
void sha512(SHA512state *st, uchar *buf, int n);
void sha512finish(SHA512state *st, uchar *buf);
