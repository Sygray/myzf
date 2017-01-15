#include "MyZf.h"
#include "ZfUtil.h"

using namespace std;
using namespace boost::property_tree;

size_t callbackWrite(char *ptr, size_t size, size_t nmemb, string *stream)
{
	int dataLength = size * nmemb;
	stream->append(ptr, dataLength);
	return dataLength;
}

int MyZf()
{
	//Read ini file	 
	ptree pt;
	string APIKey, APISecret, URLTradeAPI, URLInfoAPI;
	try{
		read_ini("iniMyZf.ini",pt);
		APIKey = pt.get<string>("APIKey.Key_Trade");
		APISecret = pt.get<string>("APIKey.Secret_Trade");
		URLTradeAPI = pt.get<string>("General.URL_TradeAPI");
		URLInfoAPI = pt.get<string>("General.URL_InfoAPI");
	}catch(ptree_error& e){
		cout << "ptree_error##" << e.what() << endl;
	}
	
	//Get timestamp for nonce
	string strTime = ZfUtil::now();
	cout << "Nonce: " << strTime << endl;

	//Prepare request
	string strKey = "Key: " + APIKey;

    	// The data that we're going to hash using HMAC
	string strParam = "nonce=" + strTime + "&method=get_info2";
    	string strMd = ZfUtil::HMAC_SHA512(APISecret, strParam);
	string strSign = "Sign: "+ strMd;

	//Process curl
	CURL *curl;
	CURLcode ret;

        curl = curl_easy_init();
        string chunk;

        if (curl == NULL) {
                cerr << "curl_easy_init() failed" << endl;
                return 1;
        }

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, strKey.c_str());
	headers = curl_slist_append(headers, strSign.c_str());
        
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strParam.c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_URL, URLTradeAPI.c_str()); // /1/ticker/btc_jpy");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackWrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
        
	ret = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (ret != CURLE_OK) {
                cerr << "curl_easy_perform() failed." << endl;
                return 1;
        }

        //cout << chunk << endl;
	
	//Parse response
	ptree ptRes;
	std::istringstream is(chunk);
	read_json(is, ptRes);
	double fundJPY, fundBTC, fundMON, depoJPY, depoBTC, depoMON;
	try {
		fundJPY = ptRes.get<double>("return.funds.jpy");
		fundBTC = ptRes.get<double>("return.funds.btc");
		fundMON = ptRes.get<double>("return.funds.mona");
		depoJPY = ptRes.get<double>("return.deposit.jpy");
		depoBTC = ptRes.get<double>("return.deposit.btc");
		depoMON = ptRes.get<double>("return.deposit.mona");
	}catch(ptree_error& e){
		cout << "ptree_error##" << e.what() << endl;
	}
	cout << fixed << setprecision(6);
	cout << "JPY: " << fundJPY << " / " << depoJPY << endl;
	cout << "BTC: " << fundBTC << " / " << depoBTC << endl;
	cout << "MON: " << fundMON << " / " << depoMON << endl;

	return 0;
}
