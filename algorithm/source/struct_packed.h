#ifndef STRUCT_PACKED_H_
# define STRUCT_PACKED_H_

//
// Packed structure declaration example:
//
// STRUCT_PACKED(toto,
//     int foo;
//     char bar;
// );
// struct toto;
//
// Note: (nov 2015) Works fine with g++ 5.2.0, and MSVC 2013
//

# if __GNUC__

#  define STRUCT_PACKED(name, declaration) \
    struct name \
    { \
        declaration \
    } \
    __attribute__((__packed__))

# elif _WIN32

#  define STRUCT_PACKED(name, declaration) \
    __pragma(pack(push, 1)) \
    struct name \
    { \
        declaration \
    } \
    __pragma(pack(pop))

# endif // !_WIN32 || !__GNUC__

#endif // !STRUCT_PACKED_H_
