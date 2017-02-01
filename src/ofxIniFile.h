#pragma once

#include "SimpleIni.h"

/**
 * Simple wrapper for a c-style minimal ini setting parser.
 */
class ofxIniFile {
public:
	ofxIniFile();
	ofxIniFile(const std::string & sFile);
	~ofxIniFile();
	
	bool isOpen() { return bOpen; }

	int			get(const string & sSection, const string & sKey, int defaultValue);
	long		get(const string & sSection, const string & sKey, long defaultValue);
    bool		get(const string & sSection, const string & sKey, bool defaultValue);
    string		get(const string & sSection, const string & sKey, const string & defaultValue);

	template <typename T>
	T get(const string & sSection, const string & sKey, const T & defaultValue)
	{
		string value = this->get(sSection, sKey, ofToString<T>(defaultValue));
		if(value == "")
		{
			return defaultValue;
		}
		else
		{
			return ofFromString<T>(value);
		}
	}

	vector<string> getStringVector(const string & sSection, const std::string & sKey, const std::string & defaultValue, char sSeparator = ',');
	// use this when you have multiple same keys.
	vector<string> getAllValues(const std::string & sSection, const std::string & sKey);
	
	void set(const string & sSection, const string & sKey, int value);
	void set(const string & sSection, const string & sKey, bool value);
	void set(const string & sSection, const string & sKey, long value);
	void set(const string & sSection, const string & sKey, const string & value);

	template <class T>
	void save (const string & name, T value)
	{
		this->save(name, ofToString(value));
	}

	void save();
	
private:
    CSimpleIniA  ini;
	std::string  ini_file;
	//dictionary*  ini;
	bool bOpen;

	void trim(std::string& sValue);
};
