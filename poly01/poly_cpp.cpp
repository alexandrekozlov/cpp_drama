#include <iostream>

struct BaseClass
{
	virtual void A() { std::cout << "BaseClass::A" << std::endl; }
	virtual void B() { std::cout << "BaseClass::B" << std::endl; }

	void C() { std::cout << "BaseClass::C" << std::endl; }
	void D() { std::cout << "BaseClass::D" << std::endl; }
};

struct SubclassX : BaseClass
{
	void B() override    // Overrides BaseClass::B
		{ std::cout << "SubclassX::B" << std::endl; }

	void C()             // Hides BaseClass::C
		{ std::cout << "SubclassX::C" << std::endl; }

	void E()             // Introduces E
		{ std::cout << "SubclassX::E" << std::endl; }

	virtual void F()     // Introduces F
		{ std::cout << "SubclassX::F" << std::endl; }
};

struct SubclassY : SubclassX
{
	void A() override    // Overrides BaseClass::A
		{ std::cout << "SubclassY::A" << std::endl; }

	void B() override    // Overrides SubclassX::B
		{ std::cout << "SubclassY::B" << std::endl; }

	void C()             // Hides SubclassX::C
		{ std::cout << "SubclassY::C" << std::endl; }

	void F() override    // Overrides SubclassX::F
		{ std::cout << "SubclassY::F" << std::endl; }

	void G()             // Introduces G
		{ std::cout << "SubclassY::G" << std::endl; }
};

int main() 
{
        std::cout << "\nBaseClass base" << std::endl;
	BaseClass base;

	base.A();        // BaseClass::A
	base.B();        // BaseClass::B
	base.C();        // BaseClass::C
	base.D();        // BaseClass::D


        std::cout << "\nSubclassX x" << std::endl;
	SubclassX x;

	x.A();           // BaseClass::A
	x.B();           // SubclassX::B
	x.C();           // SubclassX::C
	x.D();           // BaseClass::D
	x.E();           // SubclassX::E
	x.F();           // SubclassX::F


        std::cout << "\nBaseClass *x_as_b = &x" << std::endl;
	BaseClass *x_as_b = &x;

	x_as_b->A();     // BaseClass::A
	x_as_b->B();     // SubclassX::B
	x_as_b->C();     // BaseClass::C
	x_as_b->D();     // BaseClass::D
	// x_as_b->E();  // E is unknown for BaseClass
	// x_as_b->F();  // F is unknown for BaseClass


        std::cout << "\nSubclassY y" << std::endl;
	SubclassY y;

	y.A();           // SubclassY::A
	y.B();           // SubclassY::B
	y.C();           // SubclassY::C
	y.D();           // BaseClass::D
	y.E();           // SubclassX::E
	y.F();           // SubclassY::F
	y.G();           // SubclassY::G


        std::cout << "\nSubclassX *y_as_x = &y" << std::endl;
	SubclassX *y_as_x = &y;

	y_as_x->A();     // SubclassY::A
	y_as_x->B();     // SubclassY::B
	y_as_x->C();     // SubclassX::C
	y_as_x->D();     // BaseClass::D
	y_as_x->E();     // SubclassX::E
	y_as_x->F();     // SubclassY::F
	// y_as_x->G();  // G is unknown for SubclassX


        std::cout << "\nBaseClass *y_as_b = &y" << std::endl;
	BaseClass *y_as_b = &y;

	y_as_b->A();     // SubclassY::A
	y_as_b->B();     // SubclassY::B
	y_as_b->C();     // BaseClass::C
	y_as_b->D();     // BaseClass::D
	// y_as_b->E();  // G is unknown for BaseClass
	// y_as_b->F();  // G is unknown for BaseClass
	// y_as_b->G();  // G is unknown for BaseClass

	return 0;
}
