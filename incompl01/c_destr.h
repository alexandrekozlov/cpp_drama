#ifndef INCOMPLETE01_DESTR_H_
#define INCOMPLETE01_DESTR_H_

struct Detail;

struct Interface {
    struct Detail *detail;
};

void Interface_ctor(struct Interface *thisptr);
void Interface_dtor(struct Interface *thisptr);
int Interface_get_value(struct Interface *thisptr);

#endif
