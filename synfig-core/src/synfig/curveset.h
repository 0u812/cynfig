/* === S Y N F I G ========================================================= */
/*!	\file curveset.h
**	\brief Curve Set Header
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

#ifndef __SYNFIG_CURVESET_H
#define __SYNFIG_CURVESET_H

/* === H E A D E R S ======================================================= */
#include "blinepoint.h"
#include <vector>

/* === M A C R O S ========================================================= */

/* === T Y P E D E F S ===================================================== */

/* === C L A S S E S & S T R U C T S ======================================= */
namespace synfig
{

class BLinePoint;

struct CurvePoint
{
	Point	p;
	Point	l,r;

	CurvePoint () {}
	CurvePoint(const Point &pin, const Vector &left, const Vector &right);

	CurvePoint(const BLinePoint &bpoint);
};

class CurveSet
{
	bool		invert; //winding order...

	void CleanUp(int curve = 0);
public:

	typedef std::vector<CurvePoint>	region;
	typedef std::vector<region>		set_type;

	set_type	set; //specifies a region object (assumes looping)

	void SetClamp(int &i, int &si);

	//actual stuff
	CurveSet()
	{
	}

	//anything supporting iterator type operations
	template < typename Iterator >
	CurveSet(Iterator begin, Iterator end, bool invert = false)
	{
		set.push_back(std::vector<CurvePoint>(begin,end));
		CleanUp(invert);
	}

	CurveSet operator&(const CurveSet &rhs) const;	//intersect
	CurveSet operator|(const CurveSet &rhs) const; //union
	CurveSet operator-(const CurveSet &rhs) const; //subtract


	//Point containment
	int intersect(const Point &p) const;
};

}
/* === E N D =============================================================== */

#endif
