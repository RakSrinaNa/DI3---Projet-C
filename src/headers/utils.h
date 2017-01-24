#ifndef UTILS
#define UTILS

#define MMIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define UNUSED(x) (void)(x)

#define MALLOC(t, n) (t *) malloc((n) * sizeof(t))
#define MCHECK(x, m) if(!x){perror("MALLOC ERROR"); if(m)perror(m); exit(EXIT_FAILURE);}

#define REALLOC(t, p, n) (t *) realloc(p, (n) * sizeof(t))
#define RCHECK(x, m) if(!x){perror("REALLOC ERROR"); if(m)perror(m); exit(EXIT_FAILURE);}

#define MMALLOC(p, t, n, m) p = MALLOC(t, n); MCHECK(p, m);
#define RREALLOC(p, t, n, m) p = REALLOC(t, p, n); RCHECK(p, m);

#endif
