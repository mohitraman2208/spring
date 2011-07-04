/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#include "StdAfx.h"
#include "ConfigVariable.h"
#include "System/LogOutput.h"

using std::map;
using std::string;


#define LOG_VAR(data) \
	LogObject() << data->declarationFile << ":" << data->declarationLine << ": "


ConfigVariable::MetaDataMap& ConfigVariable::GetMutableMetaDataMap()
{
	static MetaDataMap vars;
	return vars;
}

const ConfigVariable::MetaDataMap& ConfigVariable::GetMetaDataMap()
{
	return GetMutableMetaDataMap();
}

void ConfigVariable::AddMetaData(const ConfigVariableMetaData* data)
{
	MetaDataMap& vars = GetMutableMetaDataMap();
	MetaDataMap::const_iterator pos = vars.find(data->key);

	if (pos != vars.end()) {
		LOG_VAR(data) << "Duplicate config variable declaration \"" << data->key << "\"\n";
		LOG_VAR(pos->second) << "  Previously declared here\n";
	}
	else {
		vars[data->key] = data;
	}
}

const ConfigVariableMetaData* ConfigVariable::GetMetaData(const string& key)
{
	const MetaDataMap& vars = GetMetaDataMap();
	MetaDataMap::const_iterator pos = vars.find(key);

	if (pos != vars.end()) {
		return pos->second;
	}
	else {
		return NULL;
	}
}