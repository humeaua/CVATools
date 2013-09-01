//
//  StringUtilities.h
//  Seminaire
//
//  Created by Alexandre HUMEAU on 29/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Seminaire_StringUtilities_h
#define Seminaire_StringUtilities_h

#include <string>
#include <vector>

namespace Utilities
{
    typedef std::string::size_type (std::string::*find_t)(const std::string& delim, 
                                                          std::string::size_type offset) const;
    /// <summary>
    /// Splits the string s on the given delimiter(s) and
    /// returns a list of tokens without the delimiter(s)
    /// </summary>
    /// <param name=s>The string being split</param>
    /// <param name=match>The delimiter(s) for splitting</param>
    /// <param name=removeEmpty>Removes empty tokens from the list</param>
    /// <param name=fullMatch>
    /// True if the whole match string is a match, false
    /// if any character in the match string is a match
    /// </param>
    /// <returns>A list of tokens</returns>
    
    std::vector<std::string> Split(const std::string& s,
                                   const std::string& match,
                                   bool removeEmpty=false,
                                   bool fullMatch=false);
    
    std::vector<std::string> Split(const std::string& s,
                                   char match,
                                   bool removeEmpty=false,
                                   bool fullMatch=false);
    
    std::string ToUpper(const std::string & s);
}

#endif
