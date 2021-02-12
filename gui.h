///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include "imagePanel.hpp"
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/slider.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class gui
///////////////////////////////////////////////////////////////////////////////
class gui : public wxFrame
{
	private:

	protected:
		ImagePanel* imP_video;
		ImagePanel* imP_histogram;
		wxSlider* sld;
		wxButton* bt_abrir_vid;
		wxButton* bt_play_pause;
		wxButton* bt_exit;
		
		wxStaticText* lab_FPS;
		wxSpinCtrl* spinCut;
		wxStaticText* lab_Cut;

		// Virtual event handlers, overide them in your derived class
		virtual void onSlider( wxCommandEvent& event ) { event.Skip(); }
		virtual void abrir_video( wxCommandEvent& event ) { event.Skip(); }
		virtual void play( wxCommandEvent& event ) { event.Skip(); }
		virtual void exit( wxCommandEvent& event ) { event.Skip(); }
		virtual void updateFPS( wxSpinEvent& event ) { event.Skip(); }
		virtual void updateCut( wxSpinEvent& event ) { event.Skip(); }


	public:
		wxSpinCtrl* spinFPS;
		gui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("titulo"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 924,518 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~gui();

};

