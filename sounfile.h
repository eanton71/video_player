#ifndef SOUNDFILE_H
#define SOUNDFILE_H 
#pragma once
//sfml libreria sonido
#include <SFML/Audio.hpp> 
#include <cmath>
#include <iostream> 
 
class SoundFile
{
	public:
		int cargar_array(sf::Int16 raw[], const unsigned SAMPLES, const unsigned SAMPLE_RATE);
		int stop();
	private:
		sf::Sound sound;
		sf::SoundBuffer buffer;
		int snd_sleep = 100;
};

#endif