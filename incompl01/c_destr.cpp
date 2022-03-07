#include "c_destr.h"
#include <stdlib.h>

struct Detail {
    int value;
};







// Forward declaration
void Detail_cleanup(struct Detail *thisptr);

void Detail_ctor(struct Detail *thisptr) {
    thisptr->value = 42;
}

void Detail_dtor(struct Detail *thisptr) {
    Detail_cleanup(thisptr);
}

int Detail_get_value(struct Detail *thisptr) {
    return thisptr->value;
}

void Detail_cleanup(struct Detail *thisptr) {
    thisptr->value = 0;
}

void Interface_ctor(struct Interface *thisptr)
{
    thisptr->detail = (struct Detail *)malloc(sizeof(struct Detail));
    Detail_ctor(thisptr->detail);
}

void Interface_dtor(struct Interface *thisptr)
{
    Detail_dtor(thisptr->detail);
    free(thisptr->detail);
}

int Interface_get_value(struct Interface *thisptr) {
    return Detail_get_value(thisptr->detail);
}
