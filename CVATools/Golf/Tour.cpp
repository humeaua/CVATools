//
//  Tour.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 13/01/15.
//
//

#include "Tour.h"

Tour::~Tour()
{}

TourTypeTranslator::TourTypeTranslator()
{
    Add("PGATOUR",PGATOUR);
    Add("EUROPEANTOUR",EUROPEANTOUR);
    Add("CHALLENGETOUR",CHALLENGETOUR);
    Add("WEBCOMTOUR",WEBCOMTOUR);
    Add("ASIANTOUR",ASIANTOUR);
    Add("JAPANTOUR",JAPANTOUR);
    Add("SUNSHINETOUR",SUNSHINETOUR);
    Add("PGATOURCANADA",PGATOURCANADA);
    
    Add("MAJOR",MAJOR);
}