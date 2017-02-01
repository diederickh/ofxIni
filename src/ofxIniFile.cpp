#include "ofxIniFile.h"
#include "ofMain.h"
#include <sstream>

ofxIniFile::ofxIniFile(const std::string & sFile)
:ini(false, true, false)
,ini_file(sFile)
{
	// try from data path
	ini_file = ofToDataPath(sFile,false);
	SI_Error err = ini.LoadFile(ini_file.c_str());
	if(err != SI_OK)
		ofLogError("ofxIniFile") << "Error loading file: " << ini_file;

	// 2010.11.02, make it possible to use multi keys.
	ini.SetMultiKey(true);
}


int ofxIniFile::get(const std::string & sSection, const std::string & sKey, int defaultValue) 
{
    long lvalue = static_cast<double>(defaultValue);
    return get(sSection, sKey, lvalue);
}

long ofxIniFile::get(const string & sSection, const string & sKey, long defaultValue)
{
    return ini.GetLongValue(sSection.c_str(), sKey.c_str(), defaultValue);
}

bool ofxIniFile::get(const std::string & sSection, const std::string & sKey, bool defaultValue) 
{
    return ini.GetBoolValue(sSection.c_str(), sKey.c_str(), defaultValue);
}

std::string ofxIniFile::get(const std::string & sSection, const std::string & sKey, const std::string & defaultValue) 
{
	return ini.GetValue(sSection.c_str(), sKey.c_str(), defaultValue.c_str());
}

// Get a list with values.
std::vector<std::string> ofxIniFile::getStringVector(const std::string & sSection, const std::string & sKey, const std::string & sDefaultValue, char sSeparator) {
    std::string value = get(sSection, sKey, sDefaultValue);
	string separator = string(1, sSeparator);
	return ofSplitString(value, separator, true, true);
}

// It's possible to define multiple keys with the same name; use this function to
// return all values associated with that name.
// SimpleIni isn't working here; got a error at map::find()
std::vector<std::string> ofxIniFile::getAllValues(const std::string & sSection, const std::string & sKey)
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

void ofxIniFile::trim(std::string& sValue) {
	sValue.erase( std::remove_if(sValue.begin(), sValue.end(), 
		[](const char& c){ return c == ' ' || c == '\t' ;})
	, sValue.end());
}

// Set int
void ofxIniFile::set(const std::string & sSection, const std::string & sKey, int value)
{
	 long lvalue = static_cast<long>(value);
	 set(sSection, sKey, lvalue);
}

void ofxIniFile::set(const std::string & sSection, const std::string & sKey, long value)
{
	// some params can't be specified yet.. (not sure if necessary)
	SI_Error err = ini.SetLongValue(
		sSection.c_str()
		,sKey.c_str()
		,value
		,NULL
		,false
		,true
	);
	
	if(err < 0) {
		ofLogError("ofxIniFile") << "Could not set long value: " << err;
	}
}

void ofxIniFile::set(const std::string & sSection, const std::string & sKey, bool bBoolValue)
{
	SI_Error err = ini.SetBoolValue(
		 sSection.c_str()
		,sKey.c_str()
		,bBoolValue
		,NULL
		,true
	);
	if(err < 0) {
		ofLogError("ofxIniFile") << "Could not set bool value: " << err;
	}
}

void ofxIniFile::set(const std::string & sSection, const std::string & sKey, const std::string & sValue)
{
	SI_Error err = ini.SetValue(
		 sSection.c_str()
		,sKey.c_str()
		,sValue.c_str()
		,NULL
		,true
	);
	if(err < 0) {
		ofLogError("ofxIniFile") << "Could not set string value" << err;
	}
}

void ofxIniFile::save() {
	SI_Error err = ini.SaveFile(ini_file.c_str());
	if (err < 0) {
		ofLogError("ofxIniFile") << "save err: " << err;
	}
	
}

ofxIniFile::~ofxIniFile() {
}
