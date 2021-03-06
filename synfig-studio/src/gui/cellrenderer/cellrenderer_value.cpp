/* === S Y N F I G ========================================================= */
/*!	\file cellrenderer_value.cpp
**	\brief Template File
**
**	$Id$
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
**	Copyright (c) 2007, 2008 Chris Moore
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

/* === H E A D E R S ======================================================= */

#ifdef USING_PCH
#	include "pch.h"
#else
#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include <ETL/stringf>
#include <gtkmm/label.h>
#include <gtkmm/celleditable.h>
#include <gtkmm/editable.h>
#include <gtkmm/entry.h>
#include <gtkmm/eventbox.h>
#include <gtk/gtkentry.h> /* see XXX below */

#include "app.h"
#include "widgets/widget_value.h"
#include "widgets/widget_vector.h"
#include "widgets/widget_filename.h"
#include "widgets/widget_enum.h"
#include "widgets/widget_color.h"
#include "widgets/widget_canvaschooser.h"
#include "widgets/widget_time.h"

#include "cellrenderer_gradient.h"
#include "cellrenderer_value.h"
#include <synfig/valuenode_bone.h>

#include "widgets/widget_gradient.h"
#include "dialogs/dialog_gradient.h"
#include "dialogs/dialog_color.h"
#include <gtkmm/textview.h>

#include "general.h"

#endif

using namespace synfig;
using namespace etl;
using namespace std;
using namespace studio;

/* === M A C R O S ========================================================= */

#define DIGITS		15

/* === G L O B A L S ======================================================= */

class studio::ValueBase_Entry : public Gtk::EventBox, public Gtk::CellEditable
{
	Glib::ustring path;
	Widget_ValueBase *valuewidget;
	bool edit_done_called;
	Gtk::Widget *parent;
public:
	ValueBase_Entry():
		Glib::ObjectBase  (typeid(ValueBase_Entry)),
		Gtk::EventBox     (),
		Gtk::CellEditable ()
	{
		parent=0;
		edit_done_called=false;
/*
		  Gtk::HBox *const hbox = new Gtk::HBox(false, 0);
		  add(*Gtk::manage(hbox));

		  Gtk::Entry *entry_ = new Gtk::Entry();
			entry_->set_text("bleh");
		  hbox->pack_start(*Gtk::manage(entry_), Gtk::PACK_EXPAND_WIDGET);
		  entry_->set_has_frame(false);
		  entry_->gobj()->is_cell_renderer = true; // XXX

*/
		valuewidget=manage(new class Widget_ValueBase());
		valuewidget->inside_cellrenderer();
		add(*valuewidget);
		valuewidget->show();

		//set_flags(Gtk::CAN_FOCUS);
		//set_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);

		/*
		set_events(//(Gdk::ALL_EVENTS_MASK)
		~(	Gdk::EXPOSURE_MASK
			| Gdk::ENTER_NOTIFY_MASK
			| Gdk::LEAVE_NOTIFY_MASK
			| Gdk::FOCUS_CHANGE_MASK
			| Gdk::STRUCTURE_MASK
			| Gdk::PROPERTY_CHANGE_MASK
			| Gdk::VISIBILITY_NOTIFY_MASK
			| Gdk::PROXIMITY_IN_MASK
			| Gdk::PROXIMITY_OUT_MASK
			| Gdk::SUBSTRUCTURE_MASK
		)
		);
		*/
		//signal_editing_done().connect(sigc::mem_fun(*this, &studio::ValueBase_Entry::hide));
		//signal_remove_widget().connect(sigc::mem_fun(*this, &studio::ValueBase_Entry::hide));

		show_all_children();

		//signal_show().connect(sigc::mem_fun(*this, &ValueBase_Entry::grab_focus));
	}
	~ValueBase_Entry()
	{
	}

	void on_editing_done()
	{
		hide();
		if(parent)parent->grab_focus();
		if(!edit_done_called)
		{
			edit_done_called=true;
			Gtk::CellEditable::on_editing_done();
		}
		else
		{
			synfig::error("on_editing_done(): Called twice!");
		}
	}
	void set_parent(Gtk::Widget*x) { parent=x; }
	void on_remove_widget()
	{
		hide();
		edit_done_called=true;
		if(parent)parent->grab_focus();
		Gtk::CellEditable::on_remove_widget();
	}
	void start_editing_vfunc(GdkEvent */*event*/)
	{
		valuewidget->signal_activate().connect(sigc::mem_fun(*this, &studio::ValueBase_Entry::editing_done));
		show();
		//valuewidget->grab_focus();
		//get_window()->set_focus(*valuewidget);
	}
	bool on_event(GdkEvent *event)
	{
		if(event->any.type==GDK_BUTTON_PRESS ||
			event->any.type==GDK_2BUTTON_PRESS ||
			event->any.type==GDK_KEY_PRESS ||
			event->any.type==GDK_KEY_RELEASE ||
			event->any.type==GDK_SCROLL ||
			event->any.type==GDK_3BUTTON_PRESS)
			return true;
		return Gtk::EventBox::on_event(event);
	}
	void on_grab_focus()
	{
		Gtk::EventBox::on_grab_focus();
		if(valuewidget)
			valuewidget->grab_focus();
	}
	void set_path(const Glib::ustring &p)
	{
		path=p;
	}
	void set_value(const synfig::ValueBase &data)
	{
		if(valuewidget)
			valuewidget->set_value(data);
		//valuewidget->grab_focus();
	}
	void set_canvas(const etl::handle<synfig::Canvas> &data)
	{
		assert(data);
		if(valuewidget)
			valuewidget->set_canvas(data);
	}
	void set_param_desc(const synfig::ParamDesc &data)
	{
		if(valuewidget)
			valuewidget->set_param_desc(data);
	}

	void set_value_desc(const synfigapp::ValueDesc &data)
	{
		if(valuewidget)
			valuewidget->set_value_desc(data);
	}

	void set_child_param_desc(const synfig::ParamDesc &data)
	{
		if(valuewidget)
			valuewidget->set_child_param_desc(data);
	}

	const synfig::ValueBase &get_value()
	{
		if(valuewidget)
			return valuewidget->get_value();

		warning("%s:%d this code shouldn't be reached", __FILE__, __LINE__);
		return *(new synfig::ValueBase());
	}

	const Glib::ustring &get_path()
	{
		return path;
	}

};

/* === P R O C E D U R E S ================================================= */

bool get_paragraph(synfig::String& text)
{
	Gtk::Dialog dialog(
		_("Paragraph"),		// Title
		true,		// Modal
		true		// use_separator
	);
	Gtk::Label label(_("Enter Paragraph Text Here:"));
	label.show();
	dialog.get_vbox()->pack_start(label);


	Glib::RefPtr<Gtk::TextBuffer> text_buffer(Gtk::TextBuffer::create());
	text_buffer->set_text(text);

	Gtk::TextView text_view(text_buffer);
	text_view.show();
	dialog.get_vbox()->pack_start(text_view);

/*
	Gtk::Entry entry;
	entry.set_text(text);
	entry.show();
	entry.set_activates_default(true);
	dialog.get_vbox()->pack_start(entry);
*/

	dialog.add_button(Gtk::StockID("gtk-ok"),Gtk::RESPONSE_OK);
	dialog.add_button(Gtk::StockID("gtk-cancel"),Gtk::RESPONSE_CANCEL);
	dialog.set_default_response(Gtk::RESPONSE_OK);

	//text_entry.signal_activate().connect(sigc::bind(sigc::mem_fun(dialog,&Gtk::Dialog::response),Gtk::RESPONSE_OK));

	dialog.show();

	if(dialog.run()!=Gtk::RESPONSE_OK)
		return false;

	text=text_buffer->get_text();

	return true;
}

/* === M E T H O D S ======================================================= */

CellRenderer_ValueBase::CellRenderer_ValueBase():
	Glib::ObjectBase	(typeid(CellRenderer_ValueBase)),
	Gtk::CellRendererText	(),
	property_value_	(*this,"value",synfig::ValueBase()),
	property_canvas_(*this,"canvas",etl::handle<synfig::Canvas>()),
	property_param_desc_(*this,"param_desc",synfig::ParamDesc()),
	property_value_desc_(*this,"value_desc",synfigapp::ValueDesc()),
	property_child_param_desc_(*this,"child_param_desc", synfig::ParamDesc())
{
	CellRendererText::signal_edited().connect(sigc::mem_fun(*this,&CellRenderer_ValueBase::string_edited_));
	value_entry=new ValueBase_Entry();
	value_entry->hide();

	Pango::AttrList attr_list;
	{
		Pango::AttrInt pango_size(Pango::Attribute::create_attr_size(Pango::SCALE*8));
		pango_size.set_start_index(0);
		pango_size.set_end_index(64);
		attr_list.change(pango_size);
	}
	property_attributes()=attr_list;

	property_foreground()=Glib::ustring("#7f7f7f");
	property_inconsistent()=false;
}

CellRenderer_ValueBase::~CellRenderer_ValueBase()
{
	if (getenv("SYNFIG_DEBUG_DESTRUCTORS"))
		synfig::info("CellRenderer_ValueBase::~CellRenderer_ValueBase(): Deleted");
}

void
CellRenderer_ValueBase::string_edited_(const Glib::ustring&path,const Glib::ustring&str)
{
	ValueBase old_value=property_value_.get_value();
	ValueBase value;

	if(old_value.get_type()==ValueBase::TYPE_TIME)
	{
		value=ValueBase(Time((String)str,get_canvas()->rend_desc().get_frame_rate()));
	}
	else
		value=ValueBase((String)str);

	if(old_value!=value)
		signal_edited_(path,value);
}

void
CellRenderer_ValueBase::render_vfunc(
		const Glib::RefPtr<Gdk::Drawable>& window,
		Gtk::Widget& widget,
		const Gdk::Rectangle& background_area,
		const Gdk::Rectangle& ca,
		const Gdk::Rectangle& expose_area,
		Gtk::CellRendererState flags)
{
	if(!window)
		return;
//	const unsigned int cell_xpad = property_xpad();
//	const unsigned int cell_ypad = property_ypad();

	//int x_offset = 0, y_offset = 0;
//	int	width = ca.get_width();
	int	height = ca.get_height();
//	get_size(widget, ca, x_offset, y_offset, width, height);

//	width  -= cell_xpad * 2;
//	height -= cell_ypad * 2;

//	if(width <= 0 || height <= 0)
//		return;

	Gtk::StateType state = Gtk::STATE_INSENSITIVE;
	if(property_editable())
		state = Gtk::STATE_NORMAL;
	if((flags & Gtk::CELL_RENDERER_SELECTED) != 0)
		state = (widget.has_focus()) ? Gtk::STATE_SELECTED : Gtk::STATE_ACTIVE;

	ValueBase data=property_value_.get_value();

	switch(data.get_type())
	{
	case ValueBase::TYPE_REAL:
		if(((synfig::ParamDesc)property_param_desc_).get_is_distance())
		{
			Distance x(data.get(Real()),Distance::SYSTEM_UNITS);
			x.convert(App::distance_system,get_canvas()->rend_desc());
			property_text()=(Glib::ustring)x.get_string(6).c_str();
		}
		else
			property_text()=(Glib::ustring)strprintf("%.6f",data.get(Real()));
		break;
	case ValueBase::TYPE_TIME:
		property_text()=(Glib::ustring)data.get(Time()).get_string(get_canvas()->rend_desc().get_frame_rate(),App::get_time_format());
		break;
	case ValueBase::TYPE_ANGLE:
		property_text()=(Glib::ustring)strprintf("%.2fᵒ",(Real)Angle::deg(data.get(Angle())).get());
		break;
	case ValueBase::TYPE_INTEGER:
		{
			String param_hint, child_param_hint;
			param_hint=get_param_desc().get_hint();
			child_param_hint=get_child_param_desc().get_hint();
			if(param_hint!="enum" && child_param_hint!="enum")
			{
				property_text()=(Glib::ustring)strprintf("%i",data.get(int()));
			}
			else
			{
				property_text()=(Glib::ustring)strprintf("(%i)",data.get(int()));
				std::list<synfig::ParamDesc::EnumData> enum_list;
				if(param_hint=="enum")
					enum_list=((synfig::ParamDesc)property_param_desc_).get_enum_list();
				else if(child_param_hint=="enum")
					enum_list=((synfig::ParamDesc)property_child_param_desc_).get_enum_list();
				std::list<synfig::ParamDesc::EnumData>::iterator iter;
				for(iter=enum_list.begin();iter!=enum_list.end();iter++)
					if(iter->value==data.get(int()))
					{
						// don't show the key_board s_hortcut under_scores
						String local_name = iter->local_name;
						String::size_type pos = local_name.find_first_of('_');
						if (pos != String::npos)
							property_text() = local_name.substr(0,pos) + local_name.substr(pos+1);
						else
							property_text() = local_name;
						break;
					}
			}
		}
		break;

	case ValueBase::TYPE_VECTOR:
		{
			Vector vector=data.get(Vector());
			Distance x(vector[0],Distance::SYSTEM_UNITS),y(vector[1],Distance::SYSTEM_UNITS);
			x.convert(App::distance_system,get_canvas()->rend_desc());
			y.convert(App::distance_system,get_canvas()->rend_desc());
			property_text()=static_cast<Glib::ustring>(strprintf("%s,%s",x.get_string(6).c_str(),y.get_string(6).c_str()));
		}
		break;

	case ValueBase::TYPE_STRING:

		if(data.get_type()==ValueBase::TYPE_STRING)
		{
			if(!data.get(synfig::String()).empty())
				property_text()=static_cast<Glib::ustring>(data.get(synfig::String()));
			else
				property_text()=Glib::ustring("<empty>");
		}
		break;
	case ValueBase::TYPE_CANVAS:
		if(data.get(etl::handle<synfig::Canvas>()))
		{
			if(data.get(etl::handle<synfig::Canvas>())->is_inline())
				property_text()=_("<Group>");
			else
				property_text()=(Glib::ustring)data.get(etl::handle<synfig::Canvas>())->get_id();
		}
		else
			property_text()=_("<No Image Selected>");
		break;
	case ValueBase::TYPE_COLOR:
		{
			render_color_to_window(window,ca,data.get(Color()));
			return;
		}
		break;
	case ValueBase::TYPE_BOOL:
		{
			widget.get_style()->paint_check(
				Glib::RefPtr<Gdk::Window>::cast_static(window), state,
				data.get(bool())?Gtk::SHADOW_IN:Gtk::SHADOW_OUT,
				ca, widget, "cellcheck",
				ca.get_x()/* + x_offset + cell_xpad*/,
				ca.get_y()/* + y_offset + cell_ypad*/,
				height-1,height-1);
			return;
		}
		break;
	case ValueBase::TYPE_NIL:
		//property_text()=(Glib::ustring)" ";
		return;
		break;
	case ValueBase::TYPE_GRADIENT:
		render_gradient_to_window(window,ca,data.get(Gradient()));
		return;
		break;
	case ValueBase::TYPE_BONE:
	case ValueBase::TYPE_SEGMENT:
	case ValueBase::TYPE_LIST:
	case ValueBase::TYPE_BLINEPOINT:
	case ValueBase::TYPE_WIDTHPOINT:
	case ValueBase::TYPE_DASHITEM:
		property_text()=(Glib::ustring)(ValueBase::type_local_name(data.get_type()));
		break;
	case ValueBase::TYPE_VALUENODE_BONE:
	{
		ValueNode_Bone::Handle bone_node(data.get(ValueNode_Bone::Handle()));
		String name(_("No Parent"));

		if (!bone_node->is_root())
		{
			name = (*(bone_node->get_link("name")))(get_canvas()->get_time()).get(String());
			if (name.empty())
				name = bone_node->get_guid().get_string();
		}

		property_text()=(Glib::ustring)(name);
		break;
	}
	default:
		property_text()=static_cast<Glib::ustring>(_("UNKNOWN"));
		break;
	}
	CellRendererText::render_vfunc(window,widget,background_area,ca,expose_area,flags);
}


/*
bool
CellRenderer_ValueBase::activate_vfunc(	GdkEvent* event,
	Gtk::Widget& widget,
	const Glib::ustring& path,
	const Gdk::Rectangle& background_area,
	const Gdk::Rectangle& cell_area,
	Gtk::CellRendererState flags)
{
	ValueBase data=(ValueBase)property_value_.get_value();

	switch(data.type)
	{
	case ValueBase::TYPE_BOOL:
		if(property_editable())
			signal_edited_(path,ValueBase(!data.get(bool())));
    	return true;
	case ValueBase::TYPE_STRING:
		return CellRendererText::activate_vfunc(event,widget,path,background_area,cell_area,flags);
	}
	return false;
}
*/

void
CellRenderer_ValueBase::gradient_edited(synfig::Gradient gradient, Glib::ustring path)
{
	ValueBase old_value(property_value_.get_value());
	ValueBase value(gradient);
	if(old_value!=value)
		signal_edited_(path,value);
}

void
CellRenderer_ValueBase::color_edited(synfig::Color color, Glib::ustring path)
{
	ValueBase old_value(property_value_.get_value());
	ValueBase value(color);
	if(old_value!=value)
		signal_edited_(path,value);
}

Gtk::CellEditable*
CellRenderer_ValueBase::start_editing_vfunc(
#if(!SYNFIG_WINDOWS_TARGET)
	GdkEvent* event SYNFIG_ATTR_UNUSED,
#else
	GdkEvent* event,
#endif
	Gtk::Widget& widget,
	const Glib::ustring& path,
#if(!SYNFIG_WINDOWS_TARGET)
	const Gdk::Rectangle& background_area SYNFIG_ATTR_UNUSED,
	const Gdk::Rectangle& cell_area SYNFIG_ATTR_UNUSED,
	Gtk::CellRendererState flags SYNFIG_ATTR_UNUSED)
#else
	const Gdk::Rectangle& background_area,
	const Gdk::Rectangle& cell_area,
	Gtk::CellRendererState flags)
#endif
{
	edit_value_done_called = false;
	// If we aren't editable, then there is nothing to do
	if(!property_editable())
		return 0;

	ValueBase data=property_value_.get_value();

	switch(data.get_type())
	{
	case ValueBase::TYPE_BOOL:
		signal_edited_(path,ValueBase(!data.get(bool())));
    	return NULL;
	//case ValueBase::TYPE_TIME:
	//	property_text()=(Glib::ustring)data.get(Time()).get_string(get_canvas()->rend_desc().get_frame_rate(),App::get_time_format()|Time::FORMAT_FULL);
	//	return CellRendererText::start_editing_vfunc(event,widget,path,background_area,cell_area,flags);

	case ValueBase::TYPE_GRADIENT:
		App::dialog_gradient->reset();
		App::dialog_gradient->set_gradient(data.get(Gradient()));
		App::dialog_gradient->signal_edited().connect(
			sigc::bind(
				sigc::mem_fun2(*this,&studio::CellRenderer_ValueBase::gradient_edited), // JKM: used to be mem_fun, but only mem_fun0 accepts objects & methods: http://libsigc.sourceforge.net/libsigc2/docs/reference/html/group__mem__fun.html#g7d9ea809173f48bf5c76cf1989591602
				path
			)
		);
		App::dialog_gradient->set_default_button_set_sensitive(true);
		App::dialog_gradient->present();

		return NULL;

	case ValueBase::TYPE_COLOR:
		App::dialog_color->reset();
		App::dialog_color->set_color(data.get(Color()));
		App::dialog_color->signal_edited().connect(
			sigc::bind(
				sigc::mem_fun2(*this,&studio::CellRenderer_ValueBase::color_edited),
				path
			)
		);
		App::dialog_color->present();

		return NULL;
	case ValueBase::TYPE_STRING:
		if(get_param_desc().get_hint()=="paragraph")
		{
			synfig::String string;
			string=data.get(string);
			if(get_paragraph(string))
				signal_edited_(path,ValueBase(string));
			return NULL;
		}
		// if(get_param_desc().get_hint()!="filename")
			// return CellRendererText::start_editing_vfunc(event,widget,path,background_area,cell_area,flags);
	default:
		{
			assert(get_canvas());
			//delete value_entry;
			value_entry=manage(new ValueBase_Entry());
			value_entry->set_path(path);
			value_entry->set_canvas(get_canvas());
			value_entry->set_param_desc(get_param_desc());
			value_entry->set_value_desc(get_value_desc());
			value_entry->set_child_param_desc(get_child_param_desc());
			value_entry->set_value(data);
			value_entry->set_parent(&widget);
			value_entry->signal_editing_done().connect(sigc::mem_fun(*this, &CellRenderer_ValueBase::on_value_editing_done));
			return value_entry;
		}
	}
	return NULL;
}

void
CellRenderer_ValueBase::on_value_editing_done()
{
	if (edit_value_done_called)
	{
		synfig::error("on_value_editing_done(): Called twice!");
		return;
	}

	edit_value_done_called = true;

	if(value_entry)
	{
		ValueBase old_value(property_value_.get_value());
		ValueBase value(value_entry->get_value());

		if(old_value!=value)
			signal_edited_(value_entry->get_path(),value);

		//delete value_entry;
		//value_entry=0;
	}
}
