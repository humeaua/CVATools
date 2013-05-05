//
//  KernelFunction.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 20/04/13.
//
//

#include "KernelFunction.h"

KernelFunction::KernelFunction(double dh) : dh_(dh)
{}

void KernelFunction::SetBandwidth(double dh)
{
    dh_ = dh;
}