#include "types.h"
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "sha2.h"

enum {
	SHA256rounds =  64,
	SHA512rounds =  80,
};

uint sha256const[] = {
0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};

uint sha224h0[] = {
0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939, 0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4,
};
uint sha256h0[] = {
0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19,
};


uvlong sha512const[] = {
0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
0xd807aa98a3030242ULL, 0x12835b0145706fbeULL, 0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL, 0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
0xd192e819d6ef5218ULL, 0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL, 0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
0xca273eceea26619cULL, 0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL, 0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL,
};

uvlong sha384h0[] = {
0xcbbb9d5dc1059ed8ULL, 0x629a292a367cd507ULL, 0x9159015a3070dd17ULL, 0x152fecd8f70e5939ULL,
0x67332667ffc00b31ULL, 0x8eb44a8768581511ULL, 0xdb0c2e0d64f98fa7ULL, 0x47b5481dbefa4fa4ULL,
};
uvlong sha512h0[] = {
0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL, 0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL,
0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL, 0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL,
};

#define CH(x,y,z)	((x&y) ^ (~x&z))
#define MAJ(x,y,z)	((x&y) ^ (x&z) ^ (y&z))
#define ROTR32(n, v)	((v>>n) | (v<<(32-n)))
#define ROTR64(n, v)	((v>>n) | (v<<(64-n)))
#define SHR(n, x)	(x>>n)

#define SIGMA0a(x)	(ROTR32(2, x)^ROTR32(13, x)^ROTR32(22, x))
#define SIGMA1a(x)	(ROTR32(6, x)^ROTR32(11, x)^ROTR32(25, x))
#define sigma0a(x)	(ROTR32(7, x)^ROTR32(18, x)^SHR(3, x))
#define sigma1a(x)	(ROTR32(17, x)^ROTR32(19, x)^SHR(10, x))

#define SIGMA0b(x)	(ROTR64(28, x)^ROTR64(34, x)^ROTR64(39, x))
#define SIGMA1b(x)	(ROTR64(14, x)^ROTR64(18, x)^ROTR64(41, x))
#define sigma0b(x)	(ROTR64(1, x)^ROTR64(8, x)^SHR(7, x))
#define sigma1b(x)	(ROTR64(19, x)^ROTR64(61, x)^SHR(6, x))

/* for use in _sha*() */
#define A	v[0]
#define B	v[1]
#define C	v[2]
#define D	v[3]
#define E	v[4]
#define F	v[5]
#define G	v[6]
#define H	v[7]

void
sha256init(SHA256state *st, int sha224)
{
	uint *h0;

	st->nb = 0;
	h0 = sha256h0;
	if(sha224)
		h0 = sha224h0;
	memmove(st->h, h0, sizeof sha224h0);
	st->nbuf = 0;
	st->smaller = sha224;
}

void
_sha256(SHA256state *st, uchar *buf)
{
	uint w[2*SHA256bsize/4];
	int i, t;
	uint t1, t2;
	uint v[8];

	for(t = 0; t < nelem(w)/2; t++) {
		if(t < 16) {
			w[t] = g32(buf);
			buf += 4;
		}
	}

	memmove(v, st->h, sizeof st->h);

	for(t = 0; t < SHA256rounds; t++) {
		if(t >= 16)
			w[t&31] = sigma1a(w[(t-2)&31]) + w[(t-7)&31] + sigma0a(w[(t-15)&31]) + w[(t-16)&31];
		t1 = H + SIGMA1a(E) + CH(E,F,G) + sha256const[t] + w[t&31];
		t2 = SIGMA0a(A) + MAJ(A,B,C);
		H = G;
		G = F;
		F = E;
		E = D+t1;
		D = C;
		C = B;
		B = A;
		A = t1+t2;
	}

	for(i = 0; i < nelem(v); i++)
		st->h[i] += v[i];

	st->nb += SHA256bsize;
}

void
sha256(SHA256state *st, uchar *p, int n)
{
	uint take;

	if(st->nbuf > 0 && st->nbuf+n >= SHA256bsize) {
		take = SHA256bsize-st->nbuf;
		memmove(st->buf+st->nbuf, p, take);
		p += take;
		n -= take;
		_sha256(st, st->buf);
		st->nbuf = 0;
		memset(st->buf, 0, sizeof st->buf);
	}
	while(n >= SHA256bsize) {
		_sha256(st, p);
		p += SHA256bsize;
		n -= SHA256bsize;
	}
	if(n > 0) {
		memmove(st->buf+st->nbuf, p, n);
		st->nbuf += n;
	}
}

void
sha256finish(SHA256state *st, uchar *buf)
{
	int i;
	uchar end[SHA256bsize+8];
	uint nzero, nb;

	nzero = (2*SHA256bsize - st->nbuf - 1 - 8) % SHA256bsize;
	end[0] = 0x80;
	memset(end+1, 0, nzero);
	nb = 8*(st->nb+st->nbuf);
	p64(nb, end+1+nzero);
	sha256(st, end, 1+nzero+8);

	nb = SHA256dlen/4;
	if(st->smaller)
		nb = SHA224dlen/4;
	for(i = 0; i < nb; i++, buf += 4)
		p32(st->h[i], buf);
}


void
sha512init(SHA512state *st, int sha384)
{
	uvlong *h0;

	st->nb.hi = st->nb.lo = 0;
	h0 = sha512h0;
	if(sha384)
		h0 = sha384h0;
	memmove(st->h, h0, sizeof sha512h0);
	st->nbuf = 0;
	st->smaller = sha384;
}

void
_sha512(SHA512state *st, uchar *buf)
{
	uvlong w[2*SHA512bsize/8];
	int i, t;
	uvlong t1, t2, v[8];

	for(t = 0; t < nelem(w)/2; t++) {
		if(t < 16) {
			w[t] = g64(buf);
			buf += 8;
		}
	}

	memmove(v, st->h, sizeof st->h);

	for(t = 0; t < SHA512rounds; t++) {
		if(t >= 16)
			w[t&31] = sigma1b(w[(t-2)&31]) + w[(t-7)&31] + sigma0b(w[(t-15)&31]) + w[(t-16)&31];
		t1 = H + SIGMA1b(E) + CH(E,F,G) + sha512const[t] + w[t&31];
		t2 = SIGMA0b(A) + MAJ(A,B,C);
		H = G;
		G = F;
		F = E;
		E = D+t1;
		D = C;
		C = B;
		B = A;
		A = t1+t2;
	}

	for(i = 0; i < nelem(v); i++)
		st->h[i] += v[i];

	uvvadd(&st->nb, SHA512bsize);
}

void
sha512(SHA512state *st, uchar *p, int n)
{
	uint take;

	if(st->nbuf > 0 && st->nbuf+n >= SHA512bsize) {
		take = SHA512bsize-st->nbuf;
		memmove(st->buf+st->nbuf, p, take);
		p += take;
		n -= take;
		_sha512(st, st->buf);
		st->nbuf = 0;
		memset(st->buf, 0, sizeof st->buf);
	}
	while(n >= SHA512bsize) {
		_sha512(st, p);
		p += SHA512bsize;
		n -= SHA512bsize;
	}
	if(n > 0) {
		memmove(st->buf+st->nbuf, p, n);
		st->nbuf += n;
	}
}

void
sha512finish(SHA512state *st, uchar *buf)
{
	int i;
	uchar end[SHA512bsize+16];
	uint nzero, n;
	Uvvlong nb;

	nzero = (2*SHA512bsize - st->nbuf - 1 - 16) % SHA512bsize;
	end[0] = 0x80;
	memset(end+1, 0, nzero);
	nb = st->nb;
	uvvadd(&nb, st->nbuf);
	uvvmult8(&nb);
	p128(nb, end+1+nzero);
	sha512(st, end, 1+nzero+16);

	n = SHA512dlen/8;
	if(st->smaller)
		n = SHA384dlen/8;
	for(i = 0; i < n; i++, buf += 8)
		p64(st->h[i], buf);
}
