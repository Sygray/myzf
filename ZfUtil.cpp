#include "ZfUtil.h"

using namespace std;

string ZfUtil::now()
{
	//Get timestamp for nonce
 	time_t current;
 	time(&current);
 	struct tm* current_tm = localtime(&current);
 	char charTime[256];
 	strftime(charTime, 255, "%Y%m%d.%H%M%S", current_tm);
 	string strTime = charTime;
 	return strTime;
}

string ZfUtil::HMAC_SHA512(string key, string input)
{
    	// The data that we're going to hash using HMAC
    	char charParam[256];
	strncpy(charParam, input.c_str(), 255);

	// The key to hash
	const char* charKey = key.c_str();

    	// Using sha1 hash engine here.
	unsigned char* digest;
    	digest = HMAC(EVP_sha512(), charKey, strlen(charKey), (unsigned char*)charParam, strlen(charParam), NULL, NULL);    
    	char mdString[SHA512_DIGEST_LENGTH*2+1];
    	for(int i = 0; i < SHA512_DIGEST_LENGTH; i++)
	{
         	sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
 	}
	//printf("HMAC digest: %s\n", mdString);
	string strResult = mdString;

	return strResult;
}
