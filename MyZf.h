#ifndef INCLUDED_MYZF_H_
#define INCLUDED_MYZF_H_
#include <string>
#include <iostream>
#include <curl/curl.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>
#include <ctime>

size_t callbackWrite(char *ptr, size_t size, size_t nmemb, std::string *stream);

int MyZf();

#endif
