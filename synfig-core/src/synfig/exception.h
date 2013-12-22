/* === S Y N F I G ========================================================= */
/*!	\file exception.h
**	\brief Exceptions
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

/* === S T A R T =========================================================== */

#ifndef __SYNFIG_EXCEPTION_H
#define __SYNFIG_EXCEPTION_H

/* === H E A D E R S ======================================================= */

#include <stdexcept>
#include "string_decl.h"

/* === M A C R O S ========================================================= */

/* === T Y P E D E F S ===================================================== */

/* === C L A S S E S & S T R U C T S ======================================= */

namespace synfig {

namespace Exception {

class BadLinkName : public std::runtime_error
{
public:
	BadLinkName(const String &what);
}; // END of class BadLinkName

class BadType : public std::runtime_error
{
public:
	BadType(const String &what);
}; // END of class BadType

class IDAlreadyExists : public std::runtime_error
{
public:
	IDAlreadyExists(const String &what);
};

class NotFound : public std::runtime_error
{
public:
	NotFound(const String &what);
};

class IDNotFound : public NotFound
{
public:
	IDNotFound(const String &what);
};

class FileNotFound : public NotFound
{
public:
	FileNotFound(const String &what);
};

class BadTime : public std::runtime_error
{
public:
	BadTime(const String &what);
};

class BadFrameRate : public std::runtime_error
{
public:
	BadFrameRate(const String &what);
};

}; // END of namespace Exception

}; // END of namespace synfig

/* === E N D =============================================================== */

#endif
