#include <stdio.h>
#include <stdlib.h>
#include "lorenz.h"

int main(int argc, char* argv[])
{
    Master *m;
    Slave *s;
    init_master(&m);
    init_slave(&s);
    float a[3];
    if(argc < 2)
        return 0;
    for(int i = 0; i < atoi(argv[1]); i++){
        m->sync(m);
        a[0] = m->x1m;
        a[1] = m->x2m;
        a[2] = m->x3m;
        s->sync(s, (void*)&a[0]);
        //printf("%d %f %f %f\n", i, m->x1m, m->x2m, m->x3m);
        printf("%d %f %f %f\n", i, s->e1, s->e2, s->e3);
        //printf("%d %f\n", i, s->s);
    }

    return 0;
}