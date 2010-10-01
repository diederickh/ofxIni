#ifndef OFXINIFILEH
#define OFXINIFILEH

#include <string>
#include <vector>
#include <sstream>
#include "SimpleIni.h"
/*
extern "C" {
	#include "iniparser.h"
}
*/

/**
 * Simple wrapper for a c-style minimal ini setting parser.
 */
class ofxIniFile {
public:
	ofxIniFile(std::string  sFile);
	~ofxIniFile();

	long            getLong(std::string sSection, std::string  sKey, long           nDefaultValue);
	int             getInt(std::string sSection, std::string  sKey, int            nDefaultValue);
    std::string     getString(std::string sSection, std::string  sKey, std::string    sDefaultValue);
    bool            getBool(std::string sSection, std::string  sKey, bool           bDefaultValue = false);
    std::vector<std::string> getStringVector(std::string sSection, std::string  sKey, std::string  sDefaultValue, char sSeparator = ',');
/*



	std::vector<std::string> getStringVector(std::string sSection, std::string  sKey, std::string  sDefaultValue, char sSeparator = ',');
*/
private:
    CSimpleIniA  ini;
	std::string  ini_file;
	//dictionary*  ini;
};

#endif
