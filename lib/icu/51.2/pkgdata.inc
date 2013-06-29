GENCCODE_ASSEMBLY_TYPE=-a gcc-darwin
SO=dylib
SOBJ=dylib
A=a
LIBPREFIX=lib
LIB_EXT_ORDER=.51.2.dylib
COMPILE=/usr/bin/clang -DU_ATTRIBUTE_DEPRECATED=    -pipe -O2 -arch x86_64 -O2 -std=c99 -pedantic -Wshadow -Wpointer-arith -Wmissing-prototypes -Wwrite-strings  -fno-common -c
LIBFLAGS=-I/opt/local/include  -dynamic
GENLIB=/usr/bin/clang -dynamiclib -dynamic -pipe -O2 -arch x86_64 -O2 -std=c99 -pedantic -Wshadow -Wpointer-arith -Wmissing-prototypes -Wwrite-strings  -arch x86_64  
LDICUDTFLAGS=
LD_SONAME=-Wl,-compatibility_version -Wl,51 -Wl,-current_version -Wl,51.2 -install_name /opt/local/lib/
RPATH_FLAGS=
BIR_LDFLAGS=
AR=ar
ARFLAGS=r -c
RANLIB=ranlib
INSTALL_CMD=/usr/bin/install -c
