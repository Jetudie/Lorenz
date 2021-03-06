#include <stdio.h>
#include <stdlib.h>
#include "lorenz.h"

int main(int argc, char *argv[])
{
    Master *m;
    Slave *s;
    init_master(&m);
    init_slave(&s);
    float a[4];
    if (argc < 2)
        return 0;
    for (int i = 0; i < atoi(argv[1]); i++) {
        m->sync(m);
        a[0] = m->um;
        a[1] = m->x1m;
        a[2] = m->x2m;
        a[3] = m->x3m;
        s->sync(s, (void *) &a[0]);
        printf("%d %f %f %f ", i, s->e1, s->e2, s->e3);
        printf("%f %f %f\n", m->x1m, m->x2m, m->x3m);
    }

    return 0;
}