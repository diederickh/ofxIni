#ifndef OFXINIFILEH
#define OFXINIFILEH

#include <string>
#include <vector>
#include <sstream>
#include "SimpleIni.h"

struct IniVec3f {
	IniVec3f(float fX, float fY, float fZ):x(fX),y(fY),z(fZ) {};
	float x,y,z;
};

/**
 * Simple wrapper for a c-style minimal ini setting parser.
 */
class ofxIniFile {
public:
	ofxIniFile(std::string  sFile);
	~ofxIniFile();
	
	long getLong(
		 std::string sSection
		,std::string sKey
		,long nDefaultValue
	);
	
	int getInt(
		 std::string sSection
		,std::string sKey
		,int nDefaultValue
	);
	
    std::string getString(
		 std::string sSection
		,std::string sKey
		,std::string sDefaultValue = ""
	);
	
    bool getBool(
		 std::string sSection
		,std::string sKey
		,bool bDefaultValue = false
	);
	
    std::vector<std::string> getStringVector(
		 std::string sSection
		,std::string sKey
		,std::string sDefaultValue
		,char sSeparator = ','
	);
	
	IniVec3f getVec3f(
 		 std::string sSection
		,std::string sKey
		,std::string sDefaultValue // comma separated float string
	);
	
	float getFloat(
		 std::string sSection
		,std::string sKey
		,float fDefaultValue = 0.0f
	);
	
	// use this when you have multiple same keys.
	std::vector<std::string> getAllValues(
			 std::string sSection
			,std::string sKey
	);
	
	void setInt(
		std::string sSection
		,std::string sKey
		,int nIntValue
	);
	
	void setLong(
		std::string sSection
		,std::string sKey
		,long nLongValue
	);
	
	void setBool(
		std::string sSection
		,std::string sKey
		,bool bBoolValue
	);
	
	void setVec3f(
		std::string sSection
		,std::string sKey
		,IniVec3f oVec3f
	);
	
	void setString(
		std::string sSection
		,std::string sKey
		,std::string sValue
	);

	void setFloat(
		std::string sSection
		,std::string sKey
		,float fValue
	);

	
	
	void save();
	
	void trim(std::string& sValue);

/*
    bool GetAllValues(
        const SI_CHAR * a_pSection,
        const SI_CHAR * a_pKey,
        TNamesDepend &  a_values
        ) const;


	std::vector<std::string> getStringVector(std::string sSection, std::string  sKey, std::string  sDefaultValue, char sSeparator = ',');
*/
private:
    CSimpleIniA  ini;
	std::string  ini_file;
	//dictionary*  ini;
};

#endif
