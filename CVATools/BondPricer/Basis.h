//
//  Basis.h
//  Seminaire
//
//  Created by Alexandre HUMEAU on 23/01/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Seminaire_Basis_h
#define Seminaire_Basis_h

namespace Finance
{
    namespace Base
    {
        typedef enum {
            BONDBASIS,
            _BB,
            THIRTY360,
            _30360,
            MONEYMARKET,
            _MM,
            ACT365FIXED,
            BUS252,
            _B2,
            ACTACT,
            _AA,
            ACT360,
            _A0,
            ACT365,
            _A5,
            ACT364,
            _A4,
            // Unitary coverage = always one
            UNITARY,
            NONE
            
        } MyBasis;
    }
}
#endif
