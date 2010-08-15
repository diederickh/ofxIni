#include "ofxIniFile.h"
#include "ofMain.h"

ofxIniFile::ofxIniFile(char* sFile) {
	ini = iniparser_load(ofToDataPath(sFile).c_str());
}

// Get int
int	ofxIniFile::get(const char* sKey,int defaultValue) {
	return iniparser_getint(ini, sKey, defaultValue);
}

// Get float/double
double ofxIniFile::get(const char* sKey, double defaultValue) {
	return iniparser_getdouble(ini,(char*)sKey, defaultValue);
}
	
// Get std::string
char* ofxIniFile::get(const char* sKey, char* sDefaultValue) {
	return iniparser_getstring(ini, sKey, sDefaultValue);
}
	
// Get boolean	
bool	ofxIniFile::get(const char* sKey, bool defaultValue) {
	return iniparser_getboolean(ini,sKey, (defaultValue) ? 1 : 0);
}

ofxIniFile::~ofxIniFile() {
	iniparser_freedict(ini);
}
