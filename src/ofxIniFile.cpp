#include "ofxIniFile.h"
#include "ofMain.h"

ofxIniFile::ofxIniFile(std::string sFile)
:ini(false, true, false)
,ini_file(sFile)
{
	//ini = iniparser_load(ofToDataPath(sFile).c_str());
	SI_Error err = ini.LoadFile(sFile.c_str());
	if (err != SI_OK) {
		// try from data path
		sFile = ofToDataPath(sFile,false);
		ini_file = sFile;
		err = ini.LoadFile(sFile.c_str());
		if(err != SI_OK)
			std::cout << "ofxIniFile: error loading file" << std::endl;
	}
	// 2010.11.02, make it possible to use multi keys.
	ini.SetMultiKey(true);
}

// Get long
long ofxIniFile::getLong(std::string sSection, std::string sKey, long nDefaultValue) {
    return ini.GetLongValue(sSection.c_str(), sKey.c_str(), nDefaultValue);
}

// Get std::string
std::string ofxIniFile::getString(std::string sSection, std::string sKey, std::string sDefaultValue) {
	return ini.GetValue(sSection.c_str(), sKey.c_str(), sDefaultValue.c_str());
}

// Get int.
int ofxIniFile::getInt(std::string sSection, std::string  sKey, int nDefaultValue) {
    long lvalue = static_cast<long>(nDefaultValue);
    return getLong(sSection, sKey, lvalue);
}

// Get boolean
bool ofxIniFile::getBool(std::string sSection, std::string sKey, bool bDefaultValue) {
    return ini.GetBoolValue(sSection.c_str(), sKey.c_str(), bDefaultValue);
}

// It's possible to define multiple keys with the same name; use this function to
// return all values associated with that name.
// SimpleIni isn't working here; got a error at map::find()
std::vector<std::string> ofxIniFile::getAllValues(
			 std::string sSection
			,std::string sKey
)
{
	std::vector<std::string> retrieved;
	
	CSimpleIniA::TNamesDepend values;
	bool result = ini.GetAllValues(
			 sSection.c_str()
			,sKey.c_str()
			,values
	);
	
	if(!result)
		return retrieved;
	
	values.sort(CSimpleIniA::Entry::LoadOrder());
	CSimpleIniA::TNamesDepend::iterator i;
	for (i = values.begin(); i != values.end(); ++i) { 
		std::string val = i->pItem;
		retrieved.push_back(val);
	}
	return retrieved;
}



// Get a list with values.
std::vector<std::string> ofxIniFile::getStringVector(std::string sSection, std::string sKey, std::string sDefaultValue, char sSeparator) {
    std::string value = getString(sSection, sKey, sDefaultValue);
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

// Set int
void ofxIniFile::setInt(
				std::string sSection
				,std::string sKey
				,int nValue
)
{
	 long lvalue = static_cast<long>(nValue);
	 setLong(sSection, sKey, lvalue);
}

void ofxIniFile::setLong(
				std::string sSection
				,std::string sKey
				,long nLongValue)
{
	// some params can't be specified yet.. (not sure if necessary)
	SI_Error err = ini.SetLongValue(
		sSection.c_str()
		,sKey.c_str()
		,nLongValue
		,NULL
		,false
		,true
	);
	
	if(err < 0) {
		std::cout << "Could not set long value: " <<  err << std::endl;
	}
}

void ofxIniFile::setBool(
					std::string sSection
					,std::string sKey
					,bool bBoolValue
)
{
	SI_Error err = ini.SetBoolValue(
		 sSection.c_str()
		,sKey.c_str()
		,bBoolValue
		,NULL
		,true
	);
	if(err < 0) {
		std::cout << "Could not set bool value: " <<  err << std::endl;
	}
}


void ofxIniFile::save() {
	SI_Error err = ini.SaveFile(ini_file.c_str());
	if (err < 0) {
	std::cout << "save err: " << err << std::endl;
	}
	
}

ofxIniFile::~ofxIniFile() {
}
