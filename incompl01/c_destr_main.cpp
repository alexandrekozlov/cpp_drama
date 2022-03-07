#include "c_destr.h"
#include <stdlib.h>

int main() {
    struct Interface interface;
    Interface_ctor(&interface);

    int value = Interface_get_value(&interface);

    // Somewhere past here the Interface will be destructed.
    Interface_dtor(&interface);


    return 0;
}
