/* === S Y N F I G ========================================================= */
/*!	\file synfig/module.cpp
**	\brief writeme
**
**	$Id$
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
**
**	This package is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License as
**	published by the Free Software Foundation; either version 2 of
**	the License, or (at your option) any later version.
**
**	This package is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
**	General Public License for more details.
**	\endlegal
*/
/* ========================================================================= */

/* === H E A D E R S ======================================================= */

#ifdef USING_PCH
#	include "pch.h"
#else
#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include "module.h"
#include "general.h"
#include <ETL/stringf>

#include <Poco/SharedLibrary.h>

#endif

/* === M A C R O S ========================================================= */

/* === G L O B A L S ======================================================= */

using namespace std;
using namespace etl;
using namespace synfig;

Module::Book *synfig::Module::book_;

/* === P R O C E D U R E S ================================================= */

void
Module::addSearchDir(const std::string& dir) {
    modpaths_.push_back(dir);
}

bool
Module::subsys_init(const String &prefix)
{
    // TODO: Boost filesystem paths
	addSearchDir(".");
	if(getenv("HOME"))
		addSearchDir(std::string(getenv("HOME")) + "/.synfig/modules");
	addSearchDir(prefix+"/lib/synfig/modules");
#ifdef SYNFIG_CORE_LIB_PATH
	addSearchDir(SYNFIG_CORE_LIB_PATH "/synfig/modules");
#endif
#ifdef __APPLE__
	addSearchDir("/Library/Frameworks/synfig.framework/Resources/modules");
#else
	addSearchDir("/usr/local/lib/synfig/modules");
	addSearchDir(".");
#endif
	book_=new Book;
	return true;
}

bool
Module::subsys_stop()
{
	delete book_;

    if(module_.isLoaded())
        module_.unload();
    
	return true;
}

void
Module::register_default_modules(ProgressCallback *callback)
{
	#define REGISTER_MODULE(module) if (!Register(module, callback)) \
										throw std::runtime_error(std::string("Unable to load module '") + module + "'")
	REGISTER_MODULE("lyr_freetype");
	REGISTER_MODULE("mod_geometry");
	REGISTER_MODULE("mod_gradient");
	REGISTER_MODULE("mod_particle");
}

Module::Book&
Module::book()
{
	return *book_;
}

void
synfig::Module::Register(Module::Handle mod)
{
	book()[mod->Name()]=mod;
}

void
synfig::Module::loadModule(const std::string& module_name) {
    ModulePaths paths = generatePaths(module_name);
    
    for(const ModulePath& p : paths) {
        try {
            module_.load(p);
            return;
        } catch(Poco::LibraryLoadException) {}
    }
    
    throw std::runtime_error("Failed to load " + module_name);
}

synfig::Module::ModulePaths
synfig::Module::generatePaths(const std::string& module_name) {
    ModulePaths paths;
    for(const ModulePath& p : modpaths_) {
        paths.emplace_back(p+module_name);
        paths.emplace_back(p+"lib"+module_name);
    }
    return paths;
}

bool
synfig::Module::Register(const String &module_name, ProgressCallback *callback)
{
	if(callback)callback->task(std::string("Attempting to register \"") + module_name + "\"");
    
    try {
        loadModule(module_name);
    } catch(std::runtime_error) {
        if(callback)callback->warning(std::string("Unable to find module \"") + module_name + "\"");
        return false;
    }

	if(callback)callback->task(std::string("Found module \"") + module_name + "\"");

	Module::constructor_type constructor=nullptr;
	Handle mod;

	if(!constructor)
	{
//		if(callback)callback->task(string("looking for -> ")+module_name+"_LTX_new_instance()");
        try {
            constructor=(Module::constructor_type )module_.getSymbol(module_name+"_LTX_new_instance");
        } catch(Poco::NotFoundException) {constructor = nullptr;}
	}

	if(!constructor)
	{
//		if(callback)callback->task(string("looking for -> lib")+module_name+"_LTX_new_instance()");
        try {
            constructor=(Module::constructor_type )module_.getSymbol(std::string("lib")+module_name+"_LTX_new_instance");
        } catch(Poco::NotFoundException) {constructor = nullptr;}
	}
	if(!constructor)
	{
//		if(callback)callback->task(string("looking for -> _lib")+module_name+"_LTX_new_instance()");
        try {
            constructor=(Module::constructor_type )module_.getSymbol(std::string("_lib")+module_name+"_LTX_new_instance");
        } catch(Poco::NotFoundException) {constructor = nullptr;}
	}
	if(!constructor)
	{
//		if(callback)callback->task(string("looking for -> _")+module_name+"_LTX_new_instance()");
        try {
            constructor=(Module::constructor_type )module_.getSymbol(std::string("_")+module_name+"_LTX_new_instance");
        } catch(Poco::NotFoundException) {constructor = nullptr;}
	}

	if(constructor)
	{
//		if(callback)callback->task(strprintf("Executing callback for \"%s\"",module_name);
		mod=handle<Module>((*constructor)(callback));
	}
	else
	{
		if(callback)callback->error(std::string("Unable to find entrypoint in module \"") + module_name + "\"");
		return false;
	}

//	if(callback)callback->task(strprintf("Done executing callback for \"%s\"",module_name);

	if(mod)
	{
//		if(callback)callback->task(strprintf("Registering \"%s\"",module_name);
		Register(mod);
	}
	else
	{
		if(callback)callback->error(_("Entrypoint did not return a module."));
		return false;
    }

	if(callback)callback->task(std::string("Success for \"") + module_name + "\"");
    
	return true;
}
