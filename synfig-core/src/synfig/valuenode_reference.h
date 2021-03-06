/* === S Y N F I G ========================================================= */
/*!	\file valuenode_reference.h
**	\brief Header file for implementation of the "Reference" valuenode conversion.
**
**	$Id$
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
**  Copyright (c) 2011 Carlos López
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

#ifndef __SYNFIG_VALUENODE_REFERENCE_H
#define __SYNFIG_VALUENODE_REFERENCE_H

/* === H E A D E R S ======================================================= */

#include "valuenode.h"

/* === M A C R O S ========================================================= */

/* === C L A S S E S & S T R U C T S ======================================= */

namespace synfig {

class ValueNode_Reference : public LinkableValueNode
{
	ValueNode::RHandle link_;
public:
	typedef etl::handle<ValueNode_Reference> Handle;
	typedef etl::handle<const ValueNode_Reference> ConstHandle;

	ValueNode_Reference(const ValueBase::Type &x);

	ValueNode_Reference(const ValueNode::Handle &x);

//	static Handle create(const ValueBase::Type &x);
//	static Handle create(const ValueNode::Handle &x);


	virtual ValueNode::LooseHandle get_link_vfunc(int i)const;

	virtual ValueBase operator()(Time t)const;

	virtual ~ValueNode_Reference();

	virtual String get_name()const;

	virtual String get_local_name()const;

protected:
	virtual bool set_link_vfunc(int i,ValueNode::Handle x);

	LinkableValueNode* create_new()const;

public:
	using synfig::LinkableValueNode::set_link_vfunc;
	static bool check_type(ValueBase::Type type);
	static ValueNode_Reference* create(const ValueBase &x);
	virtual Vocab get_children_vocab_vfunc()const;
}; // END of class ValueNode_Reference

}; // END of namespace synfig

/* === E N D =============================================================== */

#endif
