#include "c_inl_destr.h"
#include <stdlib.h>

int main() {
    struct Interface interface;
    Interface_ctor(&interface);

    int value = Interface_get_value(&interface);

    // Somewhere past here the Interface will be destructed.
    Detail_dtor(interface.detail);
    free(interface.detail);

    return 0;
}

// The compilation fails at Line 11 because Detail implementation
// is not publicly available.
//
// The important point here is this:
// Since Interface destructor is inlined, the calling code
// needs to know details of Detail type, which under normal
// circumstances is private implementation detail.
