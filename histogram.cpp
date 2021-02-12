#include "histogram.hpp"
histogram::histogram()
{

}
/**
calcular historgrama de src 
**/
void histogram::calc_histograma(cv::Mat *src, cv::Mat *b_hist, cv::Mat *g_hist, cv::Mat *r_hist, int hSize)
{
	//si la imagen es nula se sale
	if (src->empty())
	{
		return;
	}
	//creamos un array de 3 elementos para los tres canales de src
	cv::Mat bgr[3];
	cv::split(*src, bgr); 
	float range[] = {0, 256}; //the upper boundary is exclusive
	const float *hRange = {range};
	bool uniform = true, accumulate = false;
	//cv::Mat b_hist, g_hist, r_hist;
	/**
	calculo de histograma:
	 bgr[ ], imagen de entrada
	 numero de imagenes de entrada
	 lista de canales a procesar (en este caso el 0)
	 mascara, si no esta vacia debe ser una imagen del mismo tama�o que la de entrada y de 8 bits
	 b_hist,..., vector de salida unidimensional conteniendo la cantidad de pixeles (intensidad) de cada nivel 
	 dims, n� dimensiones a calcular, en este caso 1, definidas en hRange
	 hSize, tama�o del histograma
	 hRange, rango en que se mueven los valores, 0 a 256

	 https://docs.opencv.org/4.2.0/d8/dbc/tutorial_histogram_calculation.html
	 **/ 
	cv::calcHist(&bgr[0], 1, 0, cv::Mat(), *b_hist, 1, &hSize, &hRange, uniform, accumulate);
	cv::calcHist(&bgr[1], 1, 0, cv::Mat(), *g_hist, 1, &hSize, &hRange, uniform, accumulate);
	cv::calcHist(&bgr[2], 1, 0, cv::Mat(), *r_hist, 1, &hSize, &hRange, uniform, accumulate); 
}
void histogram::draw_histograma(cv::Mat* b_hist, cv::Mat* g_hist, cv::Mat* r_hist, cv::Mat* hist,   int hist_w, int hist_h, int hSize)
{
	int bin_w = cvRound((double)hist_w / hSize);

	hist->create(hist_h, hist_w, CV_8UC3);
	hist->setTo(cv::Scalar::all(0));
	normalize(*b_hist, *b_hist, 0, hist->rows, cv::NORM_MINMAX, -1, cv::Mat());
	normalize(*g_hist, *g_hist, 0, hist->rows, cv::NORM_MINMAX, -1, cv::Mat());
	normalize(*r_hist, *r_hist, 0, hist->rows, cv::NORM_MINMAX, -1, cv::Mat());
	for (int i = 1; i < hSize; i++)
	{
		line(*hist,
			cv::Point(
				bin_w * (i - 1),
				hist_h - cvRound(b_hist->at<float>(i - 1))),
			cv::Point(
				bin_w * (i),
				hist_h - cvRound(b_hist->at<float>(i))),
			cv::Scalar(255, 0, 0), 2, 8, 0);
		line(*hist,
			cv::Point(
				bin_w * (i - 1),
				hist_h - cvRound(g_hist->at<float>(i - 1))),
			cv::Point(
				bin_w * (i),
				hist_h - cvRound(g_hist->at<float>(i))),
			cv::Scalar(0, 255, 0), 2, 8, 0);
		line(*hist,
			cv::Point(
				bin_w * (i - 1),
				hist_h - cvRound(r_hist->at<float>(i - 1))),
			cv::Point(
				bin_w * (i),
				hist_h - cvRound(r_hist->at<float>(i))),
			cv::Scalar(0, 0, 255), 2, 8, 0);
	}
}