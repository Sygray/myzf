#ifndef INCLUDED_ZFUTIL_H_
#define INCLUDED_ZFUTIL_H_
#include <cstring>
#include <ctime>
#include <iostream>
#include <boost/optional.hpp>
#include <openssl/hmac.h> 
#include <openssl/sha.h>

class ZfUtil
{
public:
	static std::string now();
	static std::string HMAC_SHA512(std::string key, std::string input);
};
#endif
