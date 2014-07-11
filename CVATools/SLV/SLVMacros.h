//
//  SLVMacros.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/07/14.
//
//

#ifndef CVATools_SLVMacros_h
#define CVATools_SLVMacros_h

#define GetSetVariable(var, type, name) \
    const type & Get@name() const\
    {\
        return var; \
    }\
    void Set\name(const type & o) \
    {\
        var = o \
    }\
        

#endif
