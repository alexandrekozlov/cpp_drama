#include "cpp_destr.hpp"


class Detail {
public:
    Detail();
    ~Detail();

    int get_value();

private:
    void cleanup();

    int value;
};

Detail::Detail() 
    : value(42) {
}

Detail::~Detail() {
    cleanup();
}

int Detail::get_value() { 
    return value; 
}

void Detail::cleanup() {
    value = 0;
}

Interface::Interface() 
    : detail(new Detail()) {
}



Interface::~Interface() {
    delete detail;   // Detail destructor will be called
}



int Interface::get_value() {
    return detail->get_value();
}
