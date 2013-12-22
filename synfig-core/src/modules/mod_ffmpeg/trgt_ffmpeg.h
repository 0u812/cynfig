/* === S Y N F I G ========================================================= */
/*!	\file trgt_ffmpeg.h
**	\brief Template Header
**
**	$Id$
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
**	Copyright (c) 2010 Diego Barrios Romero
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
**
** === N O T E S ===========================================================
**
** ========================================================================= */

/* === S T A R T =========================================================== */

#ifndef __SYNFIG_TRGT_FFMPEG_H
#define __SYNFIG_TRGT_FFMPEG_H

/* === H E A D E R S ======================================================= */

#include <synfig/target_scanline.h>
#include <synfig/string.h>
#include <synfig/targetparam.h>
#include <sys/types.h>
#include <cstdio>

/* === M A C R O S ========================================================= */

/* === T Y P E D E F S ===================================================== */

/* === C L A S S E S & S T R U C T S ======================================= */

class TargetParam;

class ffmpeg_trgt : public synfig::Target_Scanline
{
	SYNFIG_TARGET_MODULE_EXT
private:
	pid_t pid;
	int imagecount;
	bool multi_image;
	FILE *file;
	synfig::String filename;
	unsigned char *buffer;
	synfig::Color *color_buffer;
	std::string video_codec;
	int bitrate;
public:
	ffmpeg_trgt(const char *filename,
				const synfig::TargetParam& params);

	virtual bool set_rend_desc(synfig::RendDesc *desc);
	virtual bool init();
	virtual bool start_frame(synfig::ProgressCallback *cb);
	virtual void end_frame();

	virtual ~ffmpeg_trgt();

	virtual synfig::Color * start_scanline(int scanline);
	virtual bool end_scanline();
};

/* === E N D =============================================================== */

#endif
