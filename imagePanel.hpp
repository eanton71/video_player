#ifndef IMAGEPANEL_HPP
#define IMAGEPANEL_HPP
#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/log.h>
#include <wx/dcclient.h>
#include <opencv2/core.hpp>
class ImagePanel : public wxPanel
{

private:   
    wxImage image;
    wxBitmap bitmap;
    float min_scale = 1.0;

public:
    ImagePanel(wxFrame *parent, wxString file, wxBitmapType format);
    ImagePanel(wxFrame* parent, wxColor color);
    void OnPaint(wxPaintEvent &evt);    
    void OnSize(wxSizeEvent &event);
    void paintNow();
    void render(wxDC &dc);
    bool loadImage(wxString file, wxBitmapType format);
    bool setImage(cv::Mat img); 
    bool fillColor(wxColor c);
    //declarar tabla de eventos
    DECLARE_EVENT_TABLE()
};

#endif
