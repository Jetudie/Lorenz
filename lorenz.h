#ifndef LORENZ_H_
#define LORENZ_H_

typedef struct master Master;
typedef struct slave Slave;

typedef int (*func_master)(Master *);
typedef int (*func_slave)(Slave *, void *);

int init_master(Master **self);
int init_slave(Slave **self);

static int SyncLorenzMaster(Master *);
static int SyncLorenzSlave(Slave *, void *);

/**
 * @struct master lorenz.h "lorenz.h"
 * @brief The master of Lorenz system
 */
struct master{
	float xm_init[3];
    float x1m; /**< State variable */
    float x2m; /**< State variable */
    float x3m; /**< State variable */
    float um;  /**< Controller */
    float alpha; /**< The head of the linked list */
    int c; /**< The head of the linked list */
    func_master sync; /**< Synchronize function */
};

/**
 * @struct slave lorenz.h "lorenz.h"
 * @brief The slave of Lorenz system
 */
struct slave{
    float x1s; /**< State variable */
    float x2s; /**< State variable */
    float x3s; /**< State variable */
    float e1; /**< Error value */
    float e2; /**< Error value */
    float e3; /**< Error value */
	float u; /**< Controller */ 
    float us; /**< Controller */
    float alpha; /**< Determine sync time */
    int c; /**< Controller parameter */
    func_slave sync; /**< Synchronize function */
};

#endif