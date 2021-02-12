#include "sounfile.h"
int SoundFile::cargar_array(sf::Int16 raw[], const unsigned samples, const unsigned sample_rate) {

	/*
	const unsigned AMPLITUDE = 30000;
	const double TWO_PI = 6.28318;
	const double increment = 440. / 44100;
	double x = 0;
	for (unsigned i = 0; i < samples; i++) {
		 raw[i] = AMPLITUDE * sin(x * TWO_PI);
		x += increment;
	}*/
	


	if (!buffer.loadFromSamples(raw, samples, 1, sample_rate)) {
		std::cerr << "Loading failed!" << std::endl;
		return 1;
	}

	sound.setBuffer(buffer);
	sound.setLoop(true); //lo reoetiria indefinidametne
	sound.play();
	//sf::sleep(sf::milliseconds(snd_sleep));
	
	return 0;
}
int SoundFile::stop()
{
	sound.stop();
	return 0;
}
