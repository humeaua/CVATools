//
//  HTTPFetcher.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 27/10/13.
//
//

#include "HTTPFetcher.h"

// Need Curl to do so
// http://stackoverflow.com/questions/7168933/get-page-contents-in-c
/*
 *  HttpFetcher.cpp
 *  Much of this is quite similar to examples on the libcURL site
 */

#include "HttpFetcher.h"
#include "curl.h"
#include "easy.h"
#include <iostream>


size_t HttpFetcher::WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)data;
    
    mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        // out of memory! 
        printf("not enough memory (realloc returned NULL)\n");
        exit(EXIT_FAILURE);
    }
    
    memcpy(&(mem->memory[mem->size]), ptr, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}



std::string HttpFetcher::simpleGetRequest(std::string url)
{
    std::string toReturn = "";
    CURL *curl = NULL;
    
    struct MemoryStruct chunk;
    chunk.memory = (char*)malloc(1);
    chunk.size = 0;
    
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
        // Some requests fail without a user agent.
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        
        res = curl_easy_perform(curl);
        
        curl_easy_cleanup(curl);
        
        toReturn = std::string(chunk.memory);
    }
    
    free(chunk.memory);
    
    return toReturn;
}
