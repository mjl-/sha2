/* big endian */
uint	g32(uchar *p);
uvlong	g64(uchar *p);
void	p32(uint v, uchar *p);
void	p64(uvlong v, uchar *p);
void	p128(Uvvlong v, uchar *p);

void	uvvadd(Uvvlong *v, int n);
void	uvvmult8(Uvvlong *v);

char	*unhex(char *s, uchar *p, int n);
char	*hex(uchar *src, int n, char *dst);
void	printhex(char *s, uchar *k, int n);
