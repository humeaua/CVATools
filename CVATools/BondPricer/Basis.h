//
//  Basis.h
//  Seminaire
//
//  Created by Alexandre HUMEAU on 23/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Seminaire_Basis_h
#define Seminaire_Basis_h

namespace Finance {
    
    typedef enum {
        BONDBASIS,
        THIRTY360,
        MONEYMARKET,
        ACT365FIXED,
        BUS252,
        ACTACT,
        ACT360,
        ACT365,
        ACT364
        
    } MyBasis;
    
}

#endif
