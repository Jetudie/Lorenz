#include <stdlib.h>
#include "lorenz.h"

/* range: 
 *      0 < alpha < 1
 *      |0.99 - 0.01c| < 1  
*/
#define common_alpha 0.5
#define common_c 49

#define master_x1m 0.1
#define master_x2m -0.1
#define master_x3m 0.4

#define slave_x1s 0.2
#define slave_x2s -0.5
#define slave_x3s 0.2

/**
 * @brief Lorenz synchronization function for master
 * @param self Lorenz master
 * @return Init status, 0 if succeed
 */
static int SyncLorenzMaster(Master* self)
{
    float x1, x2, x3;

    self->um = ((self->alpha-0.01)*self->c+0.028)*self->x1m + (0.01*self->c+self->alpha-0.001)*self->x2m - 0.001*self->x1m*self->x3m;
    x1 = 0.990*self->x1m + 0.01*self->x2m;
	x2 = 0.028*self->x1m + 0.999*self->x2m - 0.001*self->x1m*self->x3m;
	x3 = 0.997*self->x3m + 0.001*self->x1m*self->x2m;

	self->x1m = x1;
	self->x2m = x2;
	self->x3m = x3;
    return 0;
}

/**
 * @brief Lorenz synchronization function for slave
 * @param self Lorenz slave
 * @param m Message address received from master
 * @return Init status, 0 if succeed
 */
static int SyncLorenzSlave(Slave* self, void* m)
{
    float um = *((float*)m);
    float x1m = *((float*)m+1);
    float x2m = *((float*)m+2);
    float x3m = *((float*)m+3);
    float x1, x2, x3;

	self->us = ((0.01-self->alpha)*self->c-0.028)*self->x1s - (0.01*self->c+self->alpha-0.001)*self->x2s;
    self->u = self->us + um;
	x1 = 0.99*self->x1s + 0.01*self->x2s;
	x2 = 0.028*self->x1s + 0.999*self->x2s + self->u;
	x3 = 0.997*self->x3s + 0.001*self->x1s*self->x2s;

    self->e1 = x1 - x1m;
	self->e2 = x2 - x2m;
	self->e3 = x3 - x3m;

	self->x1s = x1;
	self->x2s = x2;
	self->x3s = x3;
    
    return 0;
}

/**
 * @brief Initialize Lorenz master
 * @param self Lorenz master
 * @return Init status, -1 if failed, otherwise 0.
 */
int init_master(Master **self)
{
    if (NULL == (*self = malloc(sizeof(Master)))) return -1;
    (*self)->xm_init[0] = master_x1m;
    (*self)->xm_init[1] = master_x2m;
    (*self)->xm_init[2] = master_x3m;
    (*self)->x1m = (*self)->xm_init[0]; 
    (*self)->x2m = (*self)->xm_init[1]; 
    (*self)->x3m = (*self)->xm_init[2];
    (*self)->um = 0;
    (*self)->alpha = common_alpha;
    (*self)->c = common_c;
    (*self)->sync = SyncLorenzMaster;
    return 0;
}

/**
 * @brief Initialize Lorenz slave
 * @param self Lorenz slave
 * @return Init status, -1 if failed, otherwise 0.
 */
int init_slave(Slave **self)
{
    if (NULL == (*self = malloc(sizeof(Slave)))) return -1;
    (*self)->x1s = slave_x1s; 
    (*self)->x2s = slave_x2s; 
    (*self)->x3s = slave_x3s;
    (*self)->e1 = 0;
    (*self)->e2 = 0;
    (*self)->e3 = 0;
    (*self)->u = 0; 
    (*self)->us = 0; 
    (*self)->alpha = common_alpha;
    (*self)->c = common_c;
    (*self)->sync = SyncLorenzSlave;
    return 0;
}