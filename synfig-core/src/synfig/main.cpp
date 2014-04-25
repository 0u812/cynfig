/* === S Y N F I G ========================================================= */
/*!	\file synfig/main.cpp
**	\brief \writeme
**
**	$Id$
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
**	Copyright (c) 2007, 2008 Chris Moore
**	Copyright (c) 2013 Konstantin Dmitriev
**  Copyright (c) 2014 J Kyle Medley
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

#if SYNFIG_WINDOWS_TARGET
#define NOMINMAX
#include <windows.h>
#endif

#include <iostream>
#include "version.h"
#include "general.h"
#include "module.h"
#include <cstdlib>
//#include <ltdl.h>
#include <glibmm.h>
#include <stdexcept>

// Includes used by get_binary_path():
#if SYNFIG_WINDOWS_TARGET
    #define GETPID_SYM _getpid
    #include <process.h>
//#include <windows.h>
#elif defined(__APPLE__)
    #define GETPID_SYM getpid
    #include <mach-o/dyld.h>
    #include <sys/param.h>
#else
    #define GETPID_SYM getpid
    #include <sys/stat.h>
    #include <unistd.h>
#endif

#include "target.h"
#include <ETL/stringf>
#include "cairolistimporter.h"
#include "listimporter.h"
#include "cairoimporter.h"
#include "color.h"
#include "vector.h"
#include <fstream>
#include <time.h>
#include "layer.h"
#include "valuenode.h"

#include "main.h"
#include "loadcanvas.h"

#include "guid.h"

#include "mutex.h"

#ifdef HAVE_SIGNAL_H
#include <signal.h>
#endif

#endif

using namespace std;
using namespace etl;
using namespace synfig;

/* === M A C R O S ========================================================= */

#define MODULE_LIST_FILENAME	"synfig_modules.cfg"

/* === S T A T I C S ======================================================= */

static etl::reference_counter synfig_ref_count_(0);

/* === P R O C E D U R E S ================================================= */

/* === M E T H O D S ======================================================= */

const char *
synfig::get_version()
{
#ifdef VERSION
	return VERSION;
#else
	return "Unknown";
#endif
}

const char *
synfig::get_build_date()
{
	return __DATE__;
}

bool
synfig::check_version_(int version,int vec_size, int color_size, int node_size, int canvas_size,int layer_size)
{
	bool ret=true;

	if(version!=SYNFIG_LIBRARY_VERSION)
	{
		synfig::error(_("API Version mismatch (LIB:%d, PROG:%d)"),SYNFIG_LIBRARY_VERSION,version);
		ret=false;
	}
	if(vec_size!=sizeof(Vector))
	{
		synfig::error(_("Size of Vector mismatch (app:%d, lib:%d)"),vec_size,sizeof(Vector));
		ret=false;
	}
	if(color_size!=sizeof(Color))
	{
		synfig::error(_("Size of Color mismatch (app:%d, lib:%d)"),color_size,sizeof(Color));
		ret=false;
	}
    if(node_size!=sizeof(Node))
    {
        synfig::error(_("Size of Node mismatch (app:%d, lib:%d, sigc::signal<void>: %d, RWLock: %d, etl::rshared_object: %d)"),node_size,sizeof(Node),sizeof(sigc::signal<void>), sizeof(RWLock), sizeof(etl::rshared_object));
        ret=false;
    }
	if(canvas_size!=sizeof(Canvas))
	{
		synfig::error(_("Size of Canvas mismatch (app:%d, lib:%d)"),canvas_size,sizeof(Canvas));
		ret=false;
	}
	if(layer_size!=sizeof(Layer))
	{
		synfig::error(_("Size of Layer mismatch (app:%d, lib:%d)"),layer_size,sizeof(Layer));
		ret=false;
	}

	return ret;
}

static void broken_pipe_signal (int /*sig*/)  {
	synfig::warning("Broken Pipe...");
}

bool retrieve_modules_to_load(String filename,std::list<String> &modules_to_load)
{
	std::ifstream file(filename.c_str());

	if(!file)
	{
		// warning("Cannot open "+filename);
		return false;
	}

	while(file)
	{
		String modulename;
		getline(file,modulename);
		if(!modulename.empty() && find(modules_to_load.begin(),modules_to_load.end(),modulename)==modules_to_load.end())
			modules_to_load.push_back(modulename);
	}

	return true;
}

synfig::Main::Main(const synfig::String& basepath,ProgressCallback *cb):
	ref_count_(synfig_ref_count_)
{
	if(ref_count_.count())
		return;

	synfig_ref_count_.reset();
	ref_count_=synfig_ref_count_;

	// Add initialization after this point

#if ENABLE_NLS
	String locale_dir;
	locale_dir = etl::dirname(basepath)+ETL_DIRECTORY_SEPARATOR+"share"+ETL_DIRECTORY_SEPARATOR+"locale";
#ifdef WIN32
	locale_dir = Glib::locale_from_utf8(locale_dir);
#endif

	bindtextdomain("synfig", locale_dir.c_str() );
	bind_textdomain_codeset("synfig", "UTF-8");
#endif

	String prefix=etl::dirname(basepath);

	unsigned int i;
#if defined(_DEBUG) && SYNFIG_GNU_EXTENSIONS
	std::set_terminate(__gnu_cxx::__verbose_terminate_handler);
#endif

#if defined(HAVE_SIGNAL_H) && defined(SIGPIPE)
	signal(SIGPIPE, broken_pipe_signal);
#endif

	//_config_search_path=new vector"string.h"();

	// Init the subsystems
	if(cb)cb->amount_complete(0, 100);
	if(cb)cb->task(_("Starting Subsystem \"Modules\""));
	if(!Module::subsys_init(prefix))
		throw std::runtime_error(_("Unable to initialize subsystem \"Module\""));

	if(cb)cb->task(_("Starting Subsystem \"Layers\""));
	if(!Layer::subsys_init())
	{
		Module::subsys_stop();
		throw std::runtime_error(_("Unable to initialize subsystem \"Layers\""));
	}

	if(cb)cb->task(_("Starting Subsystem \"Targets\""));
	if(!Target::subsys_init())
	{
		Layer::subsys_stop();
		Module::subsys_stop();
		throw std::runtime_error(_("Unable to initialize subsystem \"Targets\""));
	}

	if(cb)cb->task(_("Starting Subsystem \"Importers\""));
	if(!Importer::subsys_init())
	{
		Target::subsys_stop();
		Layer::subsys_stop();
		Module::subsys_stop();
		throw std::runtime_error(_("Unable to initialize subsystem \"Importers\""));
	}

	if(cb)cb->task(_("Starting Subsystem \"Cairo Importers\""));
	if(!CairoImporter::subsys_init())
	{
		Importer::subsys_stop();
		Target::subsys_stop();
		Layer::subsys_stop();
		Module::subsys_stop();
		throw std::runtime_error(_("Unable to initialize subsystem \"Cairo Importers\""));
	}

	if(cb)cb->task(_("Starting Subsystem \"ValueNodes\""));
	if(!ValueNode::subsys_init())
	{
		CairoImporter::subsys_stop();
		Importer::subsys_stop();
		Target::subsys_stop();
		Layer::subsys_stop();
		Module::subsys_stop();
		throw std::runtime_error(_("Unable to initialize subsystem \"ValueNodes\""));
	}

	// Load up the list importer
	Importer::book()[String("lst")]=Importer::BookEntry(ListImporter::create, ListImporter::supports_file_system_wrapper__);
	CairoImporter::book()[String("lst")]=CairoImporter::BookEntry(CairoListImporter::create, CairoListImporter::supports_file_system_wrapper__);

	// Load up the modules
	std::list<String> modules_to_load;
	std::vector<String> locations;

	if(getenv("SYNFIG_MODULE_LIST"))
		locations.push_back(getenv("SYNFIG_MODULE_LIST"));
	else
	{
		locations.push_back("./" MODULE_LIST_FILENAME);
		if(getenv("HOME"))
			locations.push_back(strprintf("%s/.synfig/%s", getenv("HOME"), MODULE_LIST_FILENAME));
	#ifdef SYNFIG_MODULES_DIR
		std::stringstream ss;
		ss << (char)ETL_DIRECTORY_SEPARATOR;
		locations.push_back(SYNFIG_MODULES_DIR+ss.str()+MODULE_LIST_FILENAME);
	#endif
		locations.push_back(prefix+ETL_DIRECTORY_SEPARATOR+"etc"+ETL_DIRECTORY_SEPARATOR+MODULE_LIST_FILENAME);
		locations.push_back("/usr/local/etc/" MODULE_LIST_FILENAME);
	#ifdef __APPLE__
		locations.push_back("/Library/Frameworks/synfig.framework/Resources/" MODULE_LIST_FILENAME);
		locations.push_back("/Library/Synfig/" MODULE_LIST_FILENAME);
		if(getenv("HOME"))
			locations.push_back(strprintf("%s/Library/Synfig/%s", getenv("HOME"), MODULE_LIST_FILENAME));
	#endif
	#ifdef WIN32
		locations.push_back("C:\\Program Files\\Synfig\\etc\\" MODULE_LIST_FILENAME);
	#endif
	}

	for(i=0;i<locations.size();i++)
		if(retrieve_modules_to_load(locations[i],modules_to_load))
		{
			synfig::info(_("Loading modules from %s"), locations[i].c_str());
			if(cb)cb->task(strprintf(_("Loading modules from %s"),locations[i].c_str()));
			break;
		}

	if (i == locations.size())
	{
		Importer::subsys_stop();
		CairoImporter::subsys_stop();
		Target::subsys_stop();
		Layer::subsys_stop();
		Module::subsys_stop();
		throw std::runtime_error(strprintf(_("Unable to open module list file '%s'"), MODULE_LIST_FILENAME));
	}

	std::list<String>::iterator iter;

	Module::register_default_modules(cb);

	for(i=0,iter=modules_to_load.begin();iter!=modules_to_load.end();++iter,i++)
	{
		Module::Register(*iter,cb);
		if(cb)cb->amount_complete((i+1)*100,modules_to_load.size()*100);
	}

	if(cb)cb->amount_complete(100, 100);
	if(cb)cb->task(_("DONE"));
}

synfig::Main::~Main()
{
	ref_count_.detach();
	if(!synfig_ref_count_.unique())
		return;
	synfig_ref_count_.detach();

	// Add deinitialization after this point

	if(get_open_canvas_map().size())
	{
		synfig::warning("Canvases still open!");
		std::map<synfig::String, etl::loose_handle<Canvas> >::iterator iter;
		for(iter=get_open_canvas_map().begin();iter!=get_open_canvas_map().end();++iter)
		{
			synfig::warning("%s: count()=%d",iter->first.c_str(), iter->second.count());
		}
	}

	// synfig::info("ValueNode::subsys_stop()");
	ValueNode::subsys_stop();
	// synfig::info("Importer::subsys_stop()");
	Importer::subsys_stop();
	CairoImporter::subsys_stop();
	// synfig::info("Target::subsys_stop()");
	Target::subsys_stop();
	// synfig::info("Layer::subsys_stop()");
	Layer::subsys_stop();
	/*! \todo For some reason, uncommenting the next line will cause things to crash.
			  This needs to be looked into at some point. */
 	// synfig::info("Module::subsys_stop()");
	// Module::subsys_stop();
	// synfig::info("Exiting");

#if defined(HAVE_SIGNAL_H) && defined(SIGPIPE)
	signal(SIGPIPE, SIG_DFL);
#endif
}

static const String
current_time()
{
	const int buflen = 50;
	time_t t;
	struct tm *lt;
	char b[buflen];
	time(&t);
	lt = localtime(&t);
	strftime(b, buflen, " [%X] ", lt);
	return String(b);
}

void
synfig::error(const char *format,...)
{
	va_list args;
	va_start(args,format);
	error(vstrprintf(format,args));
}

void
synfig::error(const String &str)
{
	static Mutex mutex; Mutex::Lock lock(mutex);
	cerr<<"synfig("<<GETPID_SYM()<<")"<<current_time().c_str()<<_("error")<<": "<<str.c_str()<<endl;
}

void
synfig::warning(const char *format,...)
{
	va_list args;
	va_start(args,format);
	warning(vstrprintf(format,args));
}

void
synfig::warning(const String &str)
{
	static Mutex mutex; Mutex::Lock lock(mutex);
	cerr<<"synfig("<<GETPID_SYM()<<")"<<current_time().c_str()<<_("warning")<<": "<<str.c_str()<<endl;
}

void
synfig::info(const char *format,...)
{
	va_list args;
	va_start(args,format);
	info(vstrprintf(format,args));
}

void
synfig::info(const String &str)
{
	static Mutex mutex; Mutex::Lock lock(mutex);
	cerr<<"synfig("<<GETPID_SYM()<<")"<<current_time().c_str()<<_("info")<<": "<<str.c_str()<<endl;
}

// synfig::get_binary_path()
// See also: http://libsylph.sourceforge.net/wiki/Full_path_to_binary

String
synfig::get_binary_path(const String &fallback_path)
{
	
	String result;

#if SYNFIG_WINDOWS_TARGET
	
	size_t buf_size = PATH_MAX - 1;
	char* path = (char*)malloc(buf_size);
	
	// GetModuleFileName is a macro, excluded by WIN32_LEAN_AND_MEAN
	// unicode verson: GetModuleFileNameW
	GetModuleFileNameA(NULL, path, PATH_MAX);

	result = String(path);
	
	free(path);

#elif defined(__APPLE__)
	
	uint32_t buf_size = MAXPATHLEN;
	char* path = (char*)malloc(MAXPATHLEN);
	
	if(_NSGetExecutablePath(path, &buf_size) == -1 ) {
		path = (char*)realloc(path, buf_size);
		_NSGetExecutablePath(path, &buf_size);
	}
	
	result = String(path);
	
	free(path);
	
	// "./synfig" case workaround
	String artifact("/./");
	size_t start_pos = result.find(artifact);
	if (start_pos != std::string::npos)
		result.replace(start_pos, artifact.length(), "/");
	
#else

	size_t buf_size = PATH_MAX - 1;
	char* path = (char*)malloc(buf_size);

	ssize_t size;
	struct stat stat_buf;
	FILE *f;

	/* Read from /proc/self/exe (symlink) */
	char* path2 = (char*)malloc(buf_size);
	strncpy(path2, "/proc/self/exe", buf_size - 1);

	while (1) {
		int i;

		size = readlink(path2, path, buf_size - 1);
		if (size == -1) {
			/* Error. */
			break;
		}

		/* readlink() success. */
		path[size] = '\0';

		/* Check whether the symlink's target is also a symlink.
		 * We want to get the final target. */
		i = stat(path, &stat_buf);
		if (i == -1) {
			/* Error. */
			break;
		}

		/* stat() success. */
		if (!S_ISLNK(stat_buf.st_mode)) {

			/* path is not a symlink. Done. */
			result = String(path);
			
			break;
		}

		/* path is a symlink. Continue loop and resolve this. */
		strncpy(path, path2, buf_size - 1);
	}
	
	free(path2);

	if (result == "")
	{
		/* readlink() or stat() failed; this can happen when the program is
		 * running in Valgrind 2.2. Read from /proc/self/maps as fallback. */

		buf_size = PATH_MAX + 128;
		char* line = (char*)malloc(buf_size);

		f = fopen("/proc/self/maps", "r");
		if (f == NULL) {
			synfig::error("Cannot open /proc/self/maps.");
		}

		/* The first entry should be the executable name. */
		char *r;
		r = fgets(line, (int) buf_size, f);
		if (r == NULL) {
			synfig::error("Cannot read /proc/self/maps.");
		}

		/* Get rid of newline character. */
		buf_size = strlen(line);
		if (buf_size <= 0) {
			/* Huh? An empty string? */
			synfig::error("Invalid /proc/self/maps.");
		}
		if (line[buf_size - 1] == 10)
			line[buf_size - 1] = 0;

		/* Extract the filename; it is always an absolute path. */
		path = strchr(line, '/');

		/* Sanity check. */
		if (strstr(line, " r-xp ") == NULL || path == NULL) {
			synfig::error("Invalid /proc/self/maps.");
		}

		result = String(path);
		free(line);
		fclose(f);
	}
	
	free(path);

#endif
	
	if (result == "")
	{
		// In worst case use value specified as fallback 
		// (usually should come from argv[0])
		result = etl::absolute_path(fallback_path);
	}
	return result;
}
