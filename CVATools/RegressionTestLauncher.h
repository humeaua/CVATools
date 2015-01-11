//
//  RegressionTestLauncher.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/01/15.
//
//

#ifndef __CVATools__RegressionTestLauncher__
#define __CVATools__RegressionTestLauncher__

#include <iostream>
#include "RegressionTests.h"
#include "HashTable.h"

typedef bool (RegressionTest::* RegressionTestFunction)() const;

class RegressionTestLauncher : public RegressionTest
{
public:
    RegressionTestLauncher(std::ostream & out);
    bool Launch() const;
    
private:
    void FillMap();
    Utilities::HashTable<std::string, RegressionTestFunction> m_mapping;
};

#endif /* defined(__CVATools__RegressionTestLauncher__) */
