#include <stdio.h>

// BaseClass
//===================================
struct BaseClass_vtbl
{
	void (*A_ptr)(struct BaseClass *);
	void (*B_ptr)(struct BaseClass *);
};

struct BaseClass
{
	struct BaseClass_vtbl *vtbl;
};

void BaseClass_A(struct BaseClass *_this) {
	printf("BaseClass::A\n");
}

void BaseClass_B(struct BaseClass *_this) {
	printf("BaseClass::B\n");
}

void BaseClass_C(struct BaseClass *_this) {
	printf("BaseClass::C\n");
}

void BaseClass_D(struct BaseClass *_this) {
	printf("BaseClass::D\n");
}

struct BaseClass_vtbl BaseClass_vtbl_init = {
	&BaseClass_A,
	&BaseClass_B
};


// SubclassX
//===================================
struct SubclassX_vtbl
{
	void (*A_ptr)(struct BaseClass *);
	void (*B_ptr)(struct SubclassX *);
	void (*F_ptr)(struct SubclassX *);
};

struct SubclassX
{
	struct SubclassX_vtbl *vtbl;
};

// Overrides BaseClass::B
void SubclassX_B(struct SubclassX *_this) {
	printf("SubclassX::B\n");
}

// Hides BaseClass::C
void SubclassX_C(struct SubclassX *_this) {
	printf("SubclassX::C\n");
}

// Introduces E
void SubclassX_E(struct SubclassX *_this) {
	printf("SubclassX::E\n");
}

// Introduces F
void SubclassX_F(struct SubclassX *_this) {
	printf("SubclassX::F\n");
}

struct SubclassX_vtbl SubclassX_vtbl_init = {
	&BaseClass_A,
	&SubclassX_B,
	&SubclassX_F
};



// SubclassY
//===================================
struct SubclassY_vtbl
{
	void (*A_ptr)(struct SubclassY *);
	void (*B_ptr)(struct SubclassY *);
	void (*F_ptr)(struct SubclassY *);
};

struct SubclassY
{
	struct SubclassY_vtbl *vtbl;
};

// Overrides BaseClass::A
void SubclassY_A(struct SubclassY *_this) {
	printf("SubclassY::A\n");
}

// Overrides SubclassX::B
void SubclassY_B(struct SubclassY *_this) {
	printf("SubclassY::B\n");
}

// Hides SubclassX::C
void SubclassY_C(struct SubclassY *_this) {
	printf("SubclassY::C\n");
}
             
// Overrides SubclassX::F
void SubclassY_F(struct SubclassY *_this) {
	printf("SubclassY::F\n");
}

// Introduces G
void SubclassY_G(struct SubclassY *_this) {
	printf("SubclassY::G\n");
}

struct SubclassY_vtbl SubclassY_vtbl_init = {
	&SubclassY_A,
	&SubclassY_B,
	&SubclassY_F
};


int main() 
{
        printf("\nBaseClass base\n");
	struct BaseClass base;
	base.vtbl = &BaseClass_vtbl_init;

	base.vtbl->A_ptr(&base);   // base.A();    BaseClass::A
	base.vtbl->B_ptr(&base);   // base.B();    BaseClass::B
	BaseClass_C(&base);        // base.C();    BaseClass::C
	BaseClass_D(&base);        // base.D();    BaseClass::D


        printf("\nSubclassX x\n");
	struct SubclassX x;
	x.vtbl = &SubclassX_vtbl_init;

	x.vtbl->A_ptr(&x);         // x.A();       BaseClass::A
	x.vtbl->B_ptr(&x);         // x.B();       SubclassX::B
	SubclassX_C(&x);           // x.C();       SubclassX::C
	BaseClass_D(&x);           // x.D();       BaseClass::D
	SubclassX_E(&x);           // x.E();       SubclassX::E
	x.vtbl->F_ptr(&x);         // x.F();       SubclassX::F


        printf("\nBaseClass *x_as_b = &x\n");
	struct BaseClass *x_as_b = &x;

	x_as_b->vtbl->A_ptr(x_as_b);     // x_as_b->A();  BaseClass::A
	x_as_b->vtbl->B_ptr(x_as_b);     // x_as_b->B();  SubclassX::B
	BaseClass_C(x_as_b);             // x_as_b->C();  BaseClass::C
	BaseClass_D(x_as_b);             // x_as_b->D();  BaseClass::D
	// x_as_b->BaseClass_E(x_as_b);  // x_as_b->E();  E is unknown for BaseClass
	// x_as_b->vtbl->F_ptr(x_as_b);  // x_as_b->F();  F is unknown for BaseClass


        printf("\nSubclassY y\n");
	struct SubclassY y;
	y.vtbl = &SubclassY_vtbl_init;

	y.vtbl->A_ptr(&y);     // y.A();    SubclassY::A
	y.vtbl->B_ptr(&y);     // y.B();    SubclassY::B
	SubclassY_C(&y);       // y.C();    SubclassY::C
	BaseClass_D(&y);       // y.D();    BaseClass::D
	SubclassX_E(&y);       // y.E();    SubclassX::E
	y.vtbl->F_ptr(&y);     // y.F();    SubclassY::F
	SubclassY_G(&y);       // y.G();    SubclassY::G


        printf("\nSubclassX *y_as_x = &y\n");
	struct SubclassX *y_as_x = &y;

	y_as_x->vtbl->A_ptr(y_as_x);   // y_as_x->A();  SubclassY::A
	y_as_x->vtbl->B_ptr(y_as_x);   // y_as_x->B();  SubclassY::B
	SubclassX_C(y_as_x);           // y_as_x->C();  SubclassX::C
	BaseClass_D(y_as_x);           // y_as_x->D();  BaseClass::D
	SubclassX_E(y_as_x);           // y_as_x->E();  SubclassX::E
	y_as_x->vtbl->F_ptr(y_as_x);   // y_as_x->F();  SubclassY::F
	// SubclassX_G(y_as_x);        // y_as_x->G();  G is unknown for SubclassX


        printf("\nBaseClass *y_as_b = &y\n");
	struct BaseClass *y_as_b = &y;

	y_as_b->vtbl->A_ptr(y_as_b);     // y_as_b->A();  SubclassY::A
	y_as_b->vtbl->B_ptr(y_as_b);     // y_as_b->B();  SubclassY::B
	BaseClass_C(y_as_b);             // y_as_b->C();  BaseClass::C
	BaseClass_D(y_as_b);             // y_as_b->D();  BaseClass::D
	// BaseClass_G(y_as_b);          // y_as_b->E();  G is unknown for BaseClass
	// y_as_b->vtbl->F_ptr(y_as_b);  // y_as_b->F();  G is unknown for BaseClass
	// BaseClass_G(y_as_b);          // y_as_b->G();  G is unknown for BaseClass


	return 0;
}

