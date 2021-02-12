///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

gui::gui( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetExtraStyle( wxFRAME_EX_METAL );

	wxFlexGridSizer* sizer;
	sizer = new wxFlexGridSizer( 3, 2, 5, 5 );
	sizer->AddGrowableCol( 0 );
	sizer->AddGrowableCol( 1 );
	sizer->SetFlexibleDirection( wxVERTICAL );
	sizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );

	sizer->SetMinSize( wxSize( 300,300 ) );
	imP_video = new ImagePanel(this,wxColor(100,100,100));
	imP_video->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );
	imP_video->SetMinSize( wxSize( 300,300 ) );

	sizer->Add( imP_video, 0, 0, 5 );

	imP_histogram= new ImagePanel(this,wxColor(100,100,100));
	imP_histogram->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );
	imP_histogram->SetMinSize( wxSize( 300,300 ) );

	sizer->Add( imP_histogram, 0, 0, 5 );

	sld = new wxSlider( this, wxID_ANY, 50, 0, 100, wxPoint( 300,5 ), wxSize( 290,-1 ), wxSL_AUTOTICKS|wxSL_HORIZONTAL|wxSL_LABELS|wxSL_MIN_MAX_LABELS|wxSL_TOP );
	sizer->Add( sld, 0, 0, 5 );

	wxBoxSizer* siz_ctrl;
	siz_ctrl = new wxBoxSizer( wxHORIZONTAL );

	bt_abrir_vid = new wxButton( this, wxID_ANY, wxT("abrir video"), wxPoint( 1,1 ), wxDefaultSize, 0 );
	siz_ctrl->Add( bt_abrir_vid, 0, wxALL, 5 );

	bt_play_pause = new wxButton( this, wxID_ANY, wxT("Play"), wxDefaultPosition, wxDefaultSize, 0 );
	siz_ctrl->Add( bt_play_pause, 0, wxALL, 5 );

	bt_exit = new wxButton( this, wxID_ANY, wxT("Salir"), wxDefaultPosition, wxDefaultSize, 0 );
	siz_ctrl->Add( bt_exit, 0, wxALL, 5 );


	sizer->Add( siz_ctrl, 0, 0, 5 );

	wxFlexGridSizer* siz_spin;
	siz_spin = new wxFlexGridSizer( 0, 2, 0, 0 );
	siz_spin->SetFlexibleDirection( wxBOTH );
	siz_spin->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	spinFPS = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10, 10 );
	siz_spin->Add( spinFPS, 0, wxALL, 5 );

	lab_FPS = new wxStaticText( this, wxID_ANY, wxT("Frames por segundo"), wxDefaultPosition, wxDefaultSize, 0 );
	lab_FPS->Wrap( -1 );
	siz_spin->Add( lab_FPS, 0, wxALL, 5 );

	spinCut = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 1000 );
	siz_spin->Add( spinCut, 0, wxALL, 5 );

	lab_Cut = new wxStaticText( this, wxID_ANY, wxT("Corte inferior"), wxDefaultPosition, wxDefaultSize, 0 );
	lab_Cut->Wrap( -1 );
	siz_spin->Add( lab_Cut, 0, wxALL, 5 );


	sizer->Add( siz_spin, 1, wxEXPAND, 5 );


	this->SetSizer( sizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	sld->Connect( wxEVT_SLIDER, wxCommandEventHandler( gui::onSlider ), NULL, this );
	bt_abrir_vid->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui::abrir_video ), NULL, this );
	bt_play_pause->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui::play ), NULL, this );
	bt_exit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui::exit ), NULL, this );
	spinFPS->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( gui::updateFPS ), NULL, this );
	spinCut->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( gui::updateCut ), NULL, this );
}

gui::~gui()
{
	// Disconnect Events
	sld->Disconnect( wxEVT_SLIDER, wxCommandEventHandler( gui::onSlider ), NULL, this );
	bt_abrir_vid->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui::abrir_video ), NULL, this );
	bt_play_pause->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui::play ), NULL, this );
	bt_exit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( gui::exit ), NULL, this );
	spinFPS->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( gui::updateFPS ), NULL, this );
	spinCut->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( gui::updateCut ), NULL, this );

}
