#include "ofxIniFile.h"
#include "ofMain.h"
#include <sstream>

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

IniVec3f ofxIniFile::getVec3f(
		std::string sSection
		,std::string sKey
		,std::string sDefaultValue
)
{
	// ugly as what.. but it works
	std::string vec_string = getString(sSection, sKey, sDefaultValue);
	std::stringstream iss(vec_string);
	
	std::string x,y,z;
	getline(iss, x, ',');
	getline(iss, y, ',');
	getline(iss, z, ',');
	trim(x);
	trim(y);
	trim(z);
	std::string result = x + "\n" + y + "\n" +z;
	std::istringstream is(result);
	float xx,yy,zz;
	IniVec3f v(0,0,0);
	is >> v.x >> v.y >> v.z;
	return v;
}

void ofxIniFile::trim(std::string& sValue) {
	char str[sValue.size()+1];
	int len = sValue.size();
	const char* v = sValue.c_str();
	int j = 0;
	for(int i = 0; v[i] != '\0'; ++i) {
		if(v[i] != ' ' && v[i] != '\t') {
			str[j++] = v[i];
		}
	}
	str[j] = '\0'; 
	sValue = str;
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

float ofxIniFile::getFloat(
				std::string sSection
				,std::string sKey
				,float fDefaultValue 
) 
{
	// TODO how to make this cleaner?
	istringstream iss;
	ostringstream oss;
	oss << fDefaultValue; 
	std::string value = getString(sSection, sKey, iss.str());
	stringstream ss;
	ss << value;
	float result;
	ss >> result;
	return result;
}
	
void ofxIniFile::setVec3f(
					std::string sSection
					,std::string sKey
					,IniVec3f oVec3f
)
{	
	ostringstream oss;
	oss << oVec3f.x << ", " << oVec3f.y << ", " << oVec3f.z;
	SI_Error err = ini.SetValue(
		sSection.c_str()
		,sKey.c_str()
		,oss.str().c_str()
		,NULL
		,true
	);
	if(err < 0) {
		std::cout << "Could not set vec3f value" << std::endl;
	}
}

void ofxIniFile::setFloat(
					std::string sSection
					,std::string sKey
					,float fValue
)
{	
	stringstream ss;
	ss << fValue;
	setString(sSection, sKey, ss.str());
}

void ofxIniFile::setString(
		 std::string sSection
		,std::string sKey
		,std::string sValue
)
{
	SI_Error err = ini.SetValue(
		 sSection.c_str()
		,sKey.c_str()
		,sValue.c_str()
		,NULL
		,true
	);
	if(err < 0) {
		std::cout << "Could not set string value" << std::endl;
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
