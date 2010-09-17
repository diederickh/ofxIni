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

// Get a list with values.
std::vector<std::string> ofxIniFile::getStringVector(const char* sKey, char* sDefaultValue, char sSeparator) {
	std::cout << "Get a vector string!" << std::endl;
	std::string value = get(sKey, sDefaultValue);
	std::vector<std::string> result;
	std::stringstream ss(value);
    std::string item;
	while(std::getline(ss, item, sSeparator)) {
		if(item == "" || item.size() == 0)
			continue;
		// trim.
		int val = 0;
		for(int cur = 0; cur < item.size(); ++cur) {
			if(item[cur] != ' ') {
				item[val] = item[cur];
				val++;
			}
		}
		item.resize(val);
		result.push_back(item);
    }
	return result;
}

ofxIniFile::~ofxIniFile() {
	iniparser_freedict(ini);
}
