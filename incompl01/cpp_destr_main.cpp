#include "cpp_destr.hpp"


int main() {
    Interface interface;

    
    int value = interface.get_value();

    // Somewhere past here the Interface will be destructed.



    return 0;
}
