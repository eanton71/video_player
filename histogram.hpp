#ifndef __HISTOGRAM__
#define __HISTOGRAM__ 
 
#include <wx/log.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

//// end generated include

/** Implementing frame */
class histogram
{

public:
    /** Constructor */
    histogram();
    
    /**
     * guarda en la imagen hist, el histomgrama de los canales de la imagen src
     * **/
    void calc_histograma(cv::Mat* src, cv::Mat* b_hist, cv::Mat* g_hist, cv::Mat* r_hist, int hSize);
    void draw_histograma(cv::Mat* b_hist, cv::Mat* g_hist, cv::Mat* r_hist, cv::Mat* hist, int hist_w, int hist_h, int hSize);
};

#endif //__HISTOGRAM__

