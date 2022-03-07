Demonstrates the problem with C++ incomplete type when
implementing PIMPL idiom and making the interface class
constructor either inline or default.

The example breaks down `cpp_destr` code into equivalent
C code showing the underlying implementation and exposing
the problem. The equivalent code is nominally C, but has
to be compiled in C++ in order to expose missing 
`Detail_dtor` declaration. This is because C implicitly
declares all functions that do not have explicit declaration.
