//
//  StringUtilities.cpp
//  Seminaire
//
//  Created by Alexandre HUMEAU on 29/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "StringUtilities.h"
#include <sstream>

namespace Utilities {
    
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
                                   bool removeEmpty,
                                   bool fullMatch)
    {
        std::vector<std::string> result;                 // return container for tokens
        std::string::size_type start = 0,           // starting position for searches
        skip = 1;            // positions to skip after a match
        find_t pfind = &std::string::find_first_of; // search algorithm for matches
        if (fullMatch)
        {
            // use the whole match string as a key
            // instead of individual characters
            // skip might be 0. see search loop comments
            skip = match.length();
            pfind = &std::string::find;
        }
        while (start != std::string::npos)
        {
            // get a complete range [start..end)
            std::string::size_type end = (s.*pfind)(match, start);
            // null strings always match in string::find, but
            // a skip of 0 causes infinite loops. pretend that
            // no tokens were found and extract the whole string
            if (skip == 0)
            {
                end = std::string::npos;
            }
            std::string token = s.substr(start, end - start);
            if (!(removeEmpty && token.empty()))
            {
                // extract the token and add it to the result list
                result.push_back(token);
            }
            // start the next range
            if ((start = end) != std::string::npos)
            {
                start += skip;
            }
        }
        return result;
    }
    
    std::vector<std::string> Split(const std::string& s,
                                   char match,
                                   bool removeEmpty,
                                   bool fullMatch)
    {
        std::string cMatch(1,match);
        return Split(s, cMatch, removeEmpty, fullMatch);
    }
    
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
    {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim))
        {
            elems.push_back(item);
        }
        return elems;
    }
    
    std::string ToUpper(const std::string & s)
    {
        std::string res(s);
        for (std::string::iterator it = res.begin() ; it !=res.end() ; ++it)
        {
            toupper(*it);
        }
        return res;
    }
}