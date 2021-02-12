#include "guiframe.h"

BEGIN_EVENT_TABLE(guiframe, wxFrame)
EVT_TIMER(wxID_ANY, guiframe::onTimer)
END_EVENT_TABLE()

guiframe::guiframe(wxWindow *parent)
	: gui(parent)
{
	//asocia la variable timer con la clase guiframe y cualquier evento asociado con ella
	timer.SetOwner(this);
	sld -> Enable(false);
	bt_play_pause -> Enable(false);
	spinCut -> Enable(false);
	spinFPS -> Enable(false);
}
void guiframe::onTimer(wxTimerEvent &event)
{
	//si se inicio la videocaptura se comienza a leer (en el evento abrir video)
	if (cam.isOpened() && !video_paused)
	{
		//matrices para la captura y el histograma
		cv::Mat img, hist, b_hist, g_hist, r_hist;
		//se guarda la captura en la matriz de imagen img
		//cam >> img;
		cam.read(img);
		if (img.empty()) //comprobar que la captura se ha guardado correctamente o que se ha llegado al final del video
		{
			wxLogDebug("img.empty()\n");
			timer.Stop();
			this->imP_video->fillColor(wxColor(0, 0, 50));
			video_paused = true;
			cam.set(NFRAME, 1);
			this->sld->SetValue(0);
			snd.stop();
			return;
		}
		
		
		wxLogDebug("frame %d fin frame %d\n", (int)cam.get(NFRAME), (int)cam.get(FRAMES));
		//actualizar el cursor del slider con el numero de frame actual
		sld->SetValue((int)cam.get(NFRAME));
		//colocar los canales rgb correctamente para mostrar en pantalla
		cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
		this->imP_video->setImage(img);
		hgm.calc_histograma(&img, &b_hist, &g_hist, &r_hist, 256);
		hgm.draw_histograma(&b_hist, &g_hist, &r_hist, &hist, 256, 250, 256);
		this->imP_histogram->setImage(hist);


		//sonido
		const unsigned samples = 256;
		const unsigned sample_rate = 10000;
		int16_t raw[samples];
		cv::cvtColor(img, img, cv::COLOR_RGB2HSV);		
		hgm.calc_histograma(&img, &b_hist, &g_hist, &r_hist, 256); 
		normalize(r_hist, r_hist, 0, 10000, cv::NORM_MINMAX, -1, cv::Mat()); 
		for (int i = 0; i < r_hist.rows; i++)
		{			 
			int v = (int)r_hist.at<float>(i);
			if (v > cutSnd) raw[i] = v;
			else raw[i] = 0; 
		}

		snd.cargar_array(raw, samples, sample_rate);

		
	}
	else if (!cam.isOpened()) //cam.isOpened() == false
	{
		wxLogDebug("VideoCapture is closed\n");
		timer.Stop();
		this->imP_video->fillColor(wxColor(0, 0, 150));
		cam.set(NFRAME, 1);
		snd.stop();
		return;
	}
}
void guiframe::onSlider(wxCommandEvent &event)
{
	int video_pos = sld->GetValue();
	cam.set(NFRAME, video_pos);
	sld->SetValue(video_pos);
}

void guiframe::exit(wxCommandEvent &event)
{
	std::exit(0);
}
/**
Evento activado por el boton Abrir
**/
void guiframe::abrir_video(wxCommandEvent &event)
{
	//se abre un cuadro de dialogo para buscar archivos
	wxFileDialog
		openFileDialog(
			this,
			_("Abrir archivo de video"),
			"",
			"",
			"AVI, MP4, MOV files (*.avi;*.mp4;*.mov)|*.avi;*.mp4;*.mov",
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	//si se cancela antes de abrir
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;
	//el cuadro de dialogo nos retorna la ruta hacia el archivo
	wxString pathname = openFileDialog.GetPath();

	//FIXME openvideo
	cam.open((cv::String)pathname);
	if (!cam.isOpened()) //error al abrir el video
	{
		wxMessageBox("error cargando video");
	}
	else
	{
		sld->SetMax((int)cam.get(FRAMES));
		sld->SetValue(0);
		bt_play_pause->SetLabel(PLAY);
		video_paused = true;

		int fps = (int)cam.get(CVFPS); 
		this->spinFPS->SetMax(2 * fps);
		this->spinFPS->SetValue(fps);
		timervalue = 1000 / fps;
		timer.Start(timervalue, false);
		bt_play_pause -> Enable(true);
	}
}

void guiframe::play(wxCommandEvent &event)
{

	if (cam.isOpened())
	{
		wxString txt;
		timer.Start(timervalue, false);
		video_paused = !video_paused;
		if (video_paused)	txt = PLAY;
		else 				txt = PAUSE;
	
		bt_play_pause->SetLabel(txt);

		sld -> Enable(true);
		spinCut -> Enable(true);
		spinFPS -> Enable(true);
	
	}  
	wxLogDebug("video_paused %d , label %s", video_paused, bt_play_pause->GetLabel());
}
void guiframe::updateFPS(wxSpinEvent &event)
{
 	int c = (255/cam.get(CVFPS)) * (cam.get(CVFPS)- 1000/timervalue), r=0, b= 0; 
	if(c<0) r = -c; else b = c;
	 
	//fps = this->spinFPS->GetValue(); 
	timervalue = 1000 / this->spinFPS->GetValue();
	
	this->spinFPS->SetForegroundColour(wxColour(r,0 ,b));
	timer.Start(timervalue, false);
}
void guiframe::updateCut(wxSpinEvent &event)
{
	cutSnd = this->spinCut->GetValue(); 
}
 