#ifndef INCOMPLETE01_DESTR_HPP_
#define INCOMPLETE01_DESTR_HPP_

class Detail;

class Interface {
public:
    Interface();
    ~Interface();

    int get_value();

private:
    Detail *detail;
};

#endif
