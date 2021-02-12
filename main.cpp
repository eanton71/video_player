#include "guiframe.h"

 
class mainApp : public wxApp
{
public:
     
    virtual bool OnInit()
    {
        
	    //Inicializa todos los manejadores de imágenes disponibles LLAMAR al inicio
	    wxInitAllImageHandlers();
        //Creamos instancia de la clase guiframe 
        wxFrame *dialog = new guiframe((wxWindow *)NULL);
        //Muestra el cuadro de dialogo. Funcion heredada de wxDialog::Show
        dialog->Show();
        //definimos dialog como ventana principal
        SetTopWindow(dialog);
        return true;
    }
};
IMPLEMENT_APP(mainApp)
 