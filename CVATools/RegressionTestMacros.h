//
//  RegressionTestMacros.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 28/06/2015.
//
//

#ifndef CVATools_RegressionTestMacros_h
#define CVATools_RegressionTestMacros_h

#include <iostream>
#include <typeinfo>
#include "Logger.h"

// Print the name of the function in the logging : temporary solution use typeid(*this) but it does not work entirely properly since it return some kind of number before the actual class name (should fix it at some point but not main concern currently)

#ifndef NAME_OF_FUNCTION
#define NAME_OF_FUNCTION typeid(*this).name() + std::string("::") + __FUNCTION__
#endif

#ifndef TEST
#define TEST(status) \
std::stringstream line; line << __LINE__; \
const std::string msg = std::string("Test ") + status + std::string(" (") + NAME_OF_FUNCTION + std::string(") on line ") + line.str();
#endif

#ifndef TOSTRING
#define TOSTRING(x) #x
#endif

#ifndef CONDITION_TOSTRING
#define CONDITION_TOSTRING(condition)\
const std::string conditionStr = std::string(" : ") + TOSTRING(condition);
#endif

#ifndef REGRESSIONTESTRETURNSUCCESS
#define REGRESSIONTESTRETURNSUCCESS \
TEST("succeeded")\
m_logger.PutLine(msg);\
return true;
#endif

#ifndef REGRESSIONTESTRETURN
#define REGRESSIONTESTRETURN(condition) \
if ((condition))\
{\
TEST("succeeded")\
CONDITION_TOSTRING(condition);\
m_logger.PutLine(msg + conditionStr);\
{\
REGRESSIONTESTRETURNSUCCESS\
}\
}\
else\
{\
TEST("failed")\
CONDITION_TOSTRING(condition);\
m_logger.PutLine(msg + conditionStr);\
return false;\
}

#endif

#ifndef REGRESSIONTESTRETURNONFAILURE
#define REGRESSIONTESTRETURNONFAILURE(condition) \
if (!(condition))\
{\
TEST("failed")\
CONDITION_TOSTRING(condition);\
m_logger.PutLine(msg + conditionStr);\
return false;\
}\
else\
{\
TEST("succeeded")\
CONDITION_TOSTRING(condition);\
m_logger.PutLine(msg + conditionStr);\
}
#endif

#endif
