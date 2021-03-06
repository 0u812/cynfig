/* === S Y N F I G ========================================================= */
/*!	\file gtkmm/render.cpp
**	\brief Template File
**
**	$Id$
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
**	Copyright (c) 2007, 2008 Chris Moore
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

#include <ETL/stringf>
#include "render.h"
#include "app.h"
#include <gtkmm/frame.h>
#include <gtkmm/alignment.h>
#include <synfig/target_scanline.h>
#include <synfig/canvas.h>
#include "asyncrenderer.h"
#include "dialogs/dialog_targetparam.h"

#include "general.h"

#include <errno.h>

#endif

/* === U S I N G =========================================================== */

using namespace std;
using namespace etl;
using namespace synfig;
using namespace studio;

/* === M A C R O S ========================================================= */

/* === G L O B A L S ======================================================= */

/* === P R O C E D U R E S ================================================= */

/* === M E T H O D S ======================================================= */

RenderSettings::RenderSettings(Gtk::Window& parent, etl::handle<synfigapp::CanvasInterface> canvas_interface):
	Gtk::Dialog(_("Render Settings"),parent,false,true),
	canvas_interface_(canvas_interface),
	adjustment_quality(3,0,9),
	entry_quality(adjustment_quality,1,0),
	adjustment_antialias(1,1,31),
	entry_antialias(adjustment_antialias,1,0),
	toggle_single_frame(_("Render _current frame only"), true),
	tparam("mpeg4",200)
{
	tparam.sequence_separator=App::sequence_separator;
	widget_rend_desc.show();
	widget_rend_desc.signal_changed().connect(sigc::mem_fun(*this,&studio::RenderSettings::on_rend_desc_changed));
	widget_rend_desc.set_rend_desc(canvas_interface_->get_canvas()->rend_desc());

	canvas_interface->signal_rend_desc_changed().connect(sigc::mem_fun(*this,&RenderSettings::on_rend_desc_changed));

	menu_target=manage(new class Gtk::Menu());

	menu_target->items().push_back(Gtk::Menu_Helpers::MenuElem(_("Auto"),
			sigc::bind(sigc::mem_fun(*this,&RenderSettings::set_target),String())
		));

	synfig::Target::Book::iterator iter;
	synfig::Target::Book book(synfig::Target::book());

	for(iter=book.begin();iter!=book.end();iter++)
	{
		menu_target->items().push_back(Gtk::Menu_Helpers::MenuElem(iter->first,
			sigc::bind(sigc::mem_fun(*this,&RenderSettings::set_target),iter->first)
		));
	}
	optionmenu_target.set_menu(*menu_target);

	optionmenu_target.set_history(0);

	Gtk::Alignment *dialogPadding = manage(new Gtk::Alignment(0, 0, 1, 1));
	dialogPadding->set_padding(12, 12, 12, 12);
	get_vbox()->pack_start(*dialogPadding, false, false, 0);

	Gtk::VBox *dialogBox = manage(new Gtk::VBox(false, 12));
	dialogPadding->add(*dialogBox);

	Gtk::Button *choose_button(manage(new class Gtk::Button(Gtk::StockID(_("Choose...")))));
	choose_button->show();
	choose_button->signal_clicked().connect(sigc::mem_fun(*this, &studio::RenderSettings::on_choose_pressed));

	tparam_button=manage(new class Gtk::Button(Gtk::StockID(_("Parameters..."))));
	tparam_button->show();
	tparam_button->set_sensitive(false);
	tparam_button->signal_clicked().connect(sigc::mem_fun(*this, &studio::RenderSettings::on_targetparam_pressed));

	Gtk::Frame *target_frame=manage(new Gtk::Frame(_("Target")));
	target_frame->set_shadow_type(Gtk::SHADOW_NONE);
	((Gtk::Label *) target_frame->get_label_widget())->set_markup(_("<b>Target</b>"));
	dialogBox->pack_start(*target_frame);
	Gtk::Alignment *targetPadding = manage(new Gtk::Alignment(0, 0, 1, 1));
	targetPadding->set_padding(6, 0, 24, 0);
	target_frame->add(*targetPadding);

	Gtk::Table *target_table = manage(new Gtk::Table(2, 3, false));
	target_table->set_row_spacings(6);
	target_table->set_col_spacings(12);
	targetPadding->add(*target_table);

	Gtk::Label *filenameLabel = manage(new Gtk::Label(_("_Filename"), true));
	filenameLabel->set_alignment(0, 0.5);
	filenameLabel->set_mnemonic_widget(entry_filename);
	target_table->attach(*filenameLabel, 0, 1, 0, 1, Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK|Gtk::FILL, 0, 0);
	target_table->attach(entry_filename, 1, 2, 0, 1, Gtk::EXPAND|Gtk::FILL, Gtk::SHRINK|Gtk::FILL, 0, 0);
	target_table->attach(*choose_button, 2, 3, 0, 1, Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK|Gtk::FILL, 0, 0);

	Gtk::Label *targetLabel = manage(new Gtk::Label(_("_Target"), true));
	targetLabel->set_alignment(0, 0.5);
	targetLabel->set_mnemonic_widget(optionmenu_target);
	target_table->attach(*targetLabel, 0, 1, 1, 2, Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK|Gtk::FILL, 0, 0);
	target_table->attach(optionmenu_target, 1, 2, 1, 2, Gtk::EXPAND|Gtk::FILL, Gtk::SHRINK|Gtk::FILL, 0, 0);
	target_table->attach(*tparam_button, 2, 3, 1, 2, Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK|Gtk::FILL, 0, 0);

	toggle_single_frame.signal_toggled().connect(sigc::mem_fun(*this, &studio::RenderSettings::on_single_frame_toggle));

	Gtk::Frame *settings_frame=manage(new Gtk::Frame(_("Settings")));
	settings_frame->set_shadow_type(Gtk::SHADOW_NONE);
	((Gtk::Label *) settings_frame->get_label_widget())->set_markup(_("<b>Settings</b>"));
	dialogBox->pack_start(*settings_frame);

	Gtk::Alignment *settingsPadding = manage(new Gtk::Alignment(0, 0, 1, 1));
	settingsPadding->set_padding(6, 0, 24, 0);
	settings_frame->add(*settingsPadding);

	Gtk::Table *settings_table=manage(new Gtk::Table(2,2,false));
	settings_table->set_row_spacings(6);
	settings_table->set_col_spacings(12);
	settingsPadding->add(*settings_table);

	Gtk::Label *qualityLabel = manage(new Gtk::Label(_("_Quality"), true));
	qualityLabel->set_alignment(0, 0.5);
	qualityLabel->set_mnemonic_widget(entry_quality);
	settings_table->attach(*qualityLabel, 0, 1, 0, 1, Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK|Gtk::FILL, 0, 0);
	settings_table->attach(entry_quality, 1, 2, 0, 1, Gtk::EXPAND|Gtk::FILL, Gtk::SHRINK|Gtk::FILL, 0, 0);

	Gtk::Label *antiAliasLabel = manage(new Gtk::Label(_("_Anti-Aliasing"), true));
	antiAliasLabel->set_alignment(0, 0.5);
	antiAliasLabel->set_mnemonic_widget(entry_antialias);
	settings_table->attach(*antiAliasLabel, 0, 1, 1, 2, Gtk::SHRINK|Gtk::FILL, Gtk::SHRINK|Gtk::FILL, 0, 0);
	settings_table->attach(entry_antialias, 1, 2, 1, 2, Gtk::EXPAND|Gtk::FILL, Gtk::SHRINK|Gtk::FILL, 0, 0);

	toggle_single_frame.set_alignment(0, 0.5);
	settings_table->attach(toggle_single_frame, 0, 2, 2, 3, Gtk::EXPAND|Gtk::FILL, Gtk::SHRINK|Gtk::FILL, 0, 0);

	dialogBox->pack_start(widget_rend_desc);


	Gtk::Button *render_button(manage(new class Gtk::Button(Gtk::StockID(_("Render")))));
	render_button->show();
	add_action_widget(*render_button,1);
	render_button->signal_clicked().connect(sigc::mem_fun(*this, &studio::RenderSettings::on_render_pressed));

	Gtk::Button *cancel_button(manage(new class Gtk::Button(Gtk::StockID("gtk-cancel"))));
	cancel_button->show();
	add_action_widget(*cancel_button,0);
	cancel_button->signal_clicked().connect(sigc::mem_fun(*this, &studio::RenderSettings::on_cancel_pressed));

	//set_default_response(1);

	set_title(_("Render Settings")+String(" - ")+canvas_interface_->get_canvas()->get_name());

	toggle_single_frame.set_active(false);
	widget_rend_desc.enable_time_section();

	set_entry_filename();

	get_vbox()->show_all();
}

RenderSettings::~RenderSettings()
{
}

void
RenderSettings::set_entry_filename()
{
	String filename(filename_sans_extension(canvas_interface_->get_canvas()->get_file_name()));

	// if this isn't the root canvas, append (<canvasname>) to the filename
	etl::handle<synfig::Canvas> canvas = canvas_interface_->get_canvas();
	if (!canvas->is_root())
	{
		if(canvas->get_name().empty())
			filename+=" ("+canvas->get_id()+')';
		else
			filename+=" ("+canvas->get_name()+')';
	}

	filename += ".png";

	try
	{
		entry_filename.set_text((filename));
	}
	catch(...)
	{
		synfig::warning("Averted crash!");
		entry_filename.set_text("output.png");
	}
}

void
RenderSettings::on_rend_desc_changed()
{
	widget_rend_desc.set_rend_desc(canvas_interface_->get_canvas()->rend_desc());
}

void
RenderSettings::set_target(synfig::String name)
{
	target_name=name;
	tparam_button->set_sensitive(target_name.compare("ffmpeg")?false:true);
}

void
RenderSettings::on_choose_pressed()
{
	String filename=entry_filename.get_text();
	if(App::dialog_save_file("Save Render As", filename, RENDER_DIR_PREFERENCE))
		entry_filename.set_text(filename);
}

void
RenderSettings::on_targetparam_pressed()
{
	Dialog_TargetParam *dialogtp = new Dialog_TargetParam(*this, tparam);
	if(dialogtp->run()==Gtk::RESPONSE_OK)
		tparam=dialogtp->get_tparam();

	delete dialogtp;
}

void
RenderSettings::on_render_pressed()
{
	String filename=entry_filename.get_text();
	synfig::String calculated_target_name(target_name);

	if(filename.empty())
	{
		canvas_interface_->get_ui_interface()->error(_("You must supply a filename!"));
		return;
	}

	// If the target type is not yet defined,
	// try to figure it out from the outfile.
	if(calculated_target_name.empty())
	{
		try
		{
			String ext(filename_extension(filename));
			if (ext.size()) ext=ext.substr(1); // skip initial '.'
			synfig::info("render target filename: '%s'; extension: '%s'", filename.c_str(), ext.c_str());
			if(Target::ext_book().count(ext))
			{
				calculated_target_name=Target::ext_book()[ext];
				synfig::info("'%s' is a known extension - using target '%s'", ext.c_str(), calculated_target_name.c_str());
			}
			else
			{
				calculated_target_name=ext;
				synfig::info("unknown extension");
			}
		}
		catch(std::runtime_error x)
		{
			canvas_interface_->get_ui_interface()->error(_("Unable to determine proper target from filename."));
			return;
		}
	}

	if(filename.empty() && calculated_target_name!="null")
	{
		canvas_interface_->get_ui_interface()->error(_("A filename is required for this target"));
		return;
	}

	Target::Handle target=Target::create(calculated_target_name,filename, tparam);
	if(!target)
	{
		canvas_interface_->get_ui_interface()->error(_("Unable to create target for ")+filename);
		return;
	}
	// Test whether the output file is writable (path exists or has write permit)
	if (access(dirname(filename).c_str(),W_OK) == -1)
	{
		canvas_interface_->get_ui_interface()->error(_("Unable to create file for ")+filename+": "+strerror( errno ));
		return;
	}

	hide();

	target->set_canvas(canvas_interface_->get_canvas());
	RendDesc rend_desc(widget_rend_desc.get_rend_desc());
	rend_desc.set_antialias((int)adjustment_antialias.get_value());
	rend_desc.set_render_excluded_contexts(false);

	// If we are to only render the current frame
	if(toggle_single_frame.get_active())
		rend_desc.set_time(canvas_interface_->get_time());

	target->set_rend_desc(&rend_desc);
	target->set_quality((int)adjustment_quality.get_value());
	if( !target->init() ){
		canvas_interface_->get_ui_interface()->error(_("Target initialization failure"));
		return;
	}

	canvas_interface_->get_ui_interface()->task(_("Rendering ")+filename);

	if(async_renderer)
	{
		async_renderer->stop();
		async_renderer.detach();
	}
	async_renderer=new AsyncRenderer(target);
	async_renderer->signal_finished().connect( sigc::mem_fun(*this,&RenderSettings::on_finished));
	async_renderer->start();
	/*
	if(!target->render(canvas_interface_->get_ui_interface().get()))
	{
		canvas_interface_->get_ui_interface()->error(_("Render Failure"));
		canvas_interface_->get_ui_interface()->amount_complete(0,10000);
		return;
	}

	// Success!
	canvas_interface_->get_ui_interface()->task(filename+_(" rendered successfully"));
	canvas_interface_->get_ui_interface()->amount_complete(0,10000);
	*/
	return;
}

void
RenderSettings::on_finished()
{
	canvas_interface_->get_ui_interface()->task(_("File rendered successfully"));
	canvas_interface_->get_ui_interface()->amount_complete(0,10000);
}

void
RenderSettings::on_cancel_pressed()
{
	hide();
}

void
RenderSettings::on_single_frame_toggle()
{
	if(toggle_single_frame.get_active())
		widget_rend_desc.disable_time_section();
	else
		widget_rend_desc.enable_time_section();
}
