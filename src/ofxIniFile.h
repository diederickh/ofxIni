#ifndef OFXINIFILEH
#define OFXINIFILEH

#include <string>
#include <vector>
#include <sstream>
extern "C" {
	#include "iniparser.h"
}

/**
 * Simple wrapper for a c-style minimal ini setting parser.
 */
class ofxIniFile {
public:
	ofxIniFile(char* sFile);
	~ofxIniFile();

	int	get(const char* sKey, int defaultValue);
	double get(const char* sKey, double defaultValue);
	char* get(const char* sKey, char* sDefaultValue);
	bool get(const char* sKey, bool defaultValue);
	std::vector<std::string> getStringVector(const char* sKey, char* sDefaultValue, char sSeparator = ',');

private:
	const char* ini_file;
	dictionary*  ini;
};

#endif
