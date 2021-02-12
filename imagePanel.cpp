
#include "imagePanel.hpp"
#include <wx/msgdlg.h>
#include "iostream"
#include <wx/gdicmn.h>
BEGIN_EVENT_TABLE(ImagePanel, wxPanel) //https://wiki.wxwidgets.org/Events
// asocia a la funcion OnPaint el evento de pintado 
EVT_PAINT(ImagePanel::OnPaint)
//Evento de cambio de tamaño del panel
EVT_SIZE(ImagePanel::OnSize)
END_EVENT_TABLE() 
/*
 Constructor
 */
ImagePanel::ImagePanel(wxFrame *parent, wxString file, wxBitmapType format) : wxPanel(parent)
{ 
    image.LoadFile(file, format);
}
ImagePanel::ImagePanel(wxFrame* parent, wxColor color) : wxPanel(parent)
{

    this->fillColor(color);
}
/*
 Evento generado cuando el panel necesita ser redibujado o ejecutando Refresh()/Update().
 */
void ImagePanel::OnPaint(wxPaintEvent &evt)
{
    //wxLogDebug("OnPaint\n");
    wxPaintDC dc(this);
    render(dc);
    evt.Skip();
}
void ImagePanel::OnSize(wxSizeEvent& event)
{
    //FIXME revisar esto para que cambie e tamaño la imagen 
    wxLogDebug("OnSize\n");
    //paintNow();
    event.Skip();
}
/*
 Alternativamente, puede usar un clientDC para pintar en el panel en cualquier momento. 
 Usando esto generalmente no lo libera de la captura de eventos de pintura, ya que es posible que,
  p. el administrador de la ventana tira su dibujo cuando la ventana llega al fondo,
   y espera que lo vuelva a dibujar cuando la ventana regrese (enviando un evento de pintura).
 */
void ImagePanel::paintNow()
{
    //wxLogDebug("paintNow\n" );
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void ImagePanel::render(wxDC &dc)
{
    //wxLogDebug("  render\n"); 
    /*
    guardamos en estas variables el tamaño del tablero de dibujo dc
    , que en este caso es ImagePanel
    */
     
    int width, height; 
    dc.GetSize(&width, &height); 
    //obtenemos la escala dividiendo las medidas  del tablero de dibujo dc entre las de la imagen 
    float sw = ((float)width - 1) / ((float)image.GetWidth());
    float sh = ((float)height - 1 ) / ((float)image.GetHeight());

    //para que la imagn se vea a escala, la escalamos al 
    min_scale = cv::min(sw, sh);
    dc.SetUserScale(min_scale, min_scale);
   
    
    //min_scale = cv::min(width, height);
    //image.Rescale(min_scale, min_scale); 
     
    bitmap = wxBitmap(image);
    dc.Clear();
    dc.DrawBitmap(bitmap, 0, 0, false); 
}
/*
 Aquí llamamos actualizar para decirle al panel que se dibuje nuevamente.
 Cuando el usuario cambia el tamaño del panel de imagen, la imagen también debe cambiar de tamaño.
 */

bool ImagePanel::loadImage(wxString file, wxBitmapType format)
{
    //wxLogDebug("loadImage\n");
    image.Destroy();
    if (!image.LoadFile(file, format))
        wxMessageBox("error cargando imagen");

    paintNow();
    return true;
}
bool ImagePanel::setImage(cv::Mat img)
{
    //wxLogDebug("setImage\n"); 
    image.Destroy();
    image.Create(img.cols, img.rows, img.data, true);
    paintNow();
    return true;
}
bool ImagePanel::fillColor(wxColor c)
{
    //wxRect r = wxRect(1,1, this->GetMinSize().x, this->GetMinSize().y);
    //wxSize s = this->GetMinSize();    
   
    //image.Destroy();
    //this.get
    image.Create(wxSize(100,100),  true);
    image.SetRGB(image.GetSize(), c.Red(),c.Green(),c.Blue());
    paintNow();
    //bitmap = wxBitmap(image);
    return true;
}