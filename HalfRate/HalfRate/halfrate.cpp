//NAME:Carson Hansen
//DATE: 4/20/2022
//PURPOSE: Take a .wav file and downsize the sample rate and sample size by 50%
#include<iostream>
#include<math.h>
#include<algorithm>
#include<fstream>
#include<string>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

using namespace std;
sf::Sound sound;
void FirFilter(sf::SoundBuffer& buffer, float* coefficentArray, sf::SoundBuffer& result);
void GetCoefficents(float*);

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
	float coefficentArray[91];
	sf::SoundBuffer buffer;
	sf::SoundBuffer result;

	//check if user gave 2 command line args
	if (argc != 2)
	{
		cout << "You must provide only two argument and the last must be a .wav file!\n";
		return 0;
	}

	//get the filter coefficents and put them into an array
	GetCoefficents(coefficentArray);
	
	//load the .wav into the buffer from file
	if (buffer.loadFromFile(argv[1]))
	{
		FirFilter(buffer, coefficentArray,result);

		cout << "\n-_-_-_-Input .wav Summary-_-_-_-\n";
		cout << "Number of channels: " << buffer.getChannelCount() << endl;
		cout << "Sample size: " << buffer.getSampleCount() << endl;
		cout << "Duration (in seconds): " << buffer.getDuration().asSeconds() << endl;
		cout << "Sample rate: " << buffer.getSampleRate() << endl;

		cout << "\n-_-_-_-New .wav Summary-_-_-_-\n";
		cout << "Number of channels: " << result.getChannelCount() << endl;
		cout << "Sample size: " << result.getSampleCount() << endl;
		cout << "Duration (in seconds): " << result.getDuration().asSeconds() << endl;
		cout << "Sample rate: " << result.getSampleRate() << endl;

		//save new sample to a .wav
		string file = argv[1];
		file.insert(0, "r");
		result.saveToFile(file);
	}
	else
	{
		cout << "Exiting the program...\n";
		return 0;
	}

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
}

//Apply the fir filter algorithm to the input .wav file, creating a new .wav
//that has had its sample rate and sample size reduced by 50%
void FirFilter(sf::SoundBuffer& buffer, float* coefficentArray, sf::SoundBuffer& result)
{
	const sf::Int16* inputArray = buffer.getSamples();
	vector<sf::Int16> bufferVector;
	vector<sf::Int16> outputVector;
	float temp = 0.0f;
	 
	 for (size_t i = 0; i < buffer.getSampleCount(); i++)
	 {
		 temp = 0.0f;
		 for (size_t j = 0; j < 90; j++)
			 temp += inputArray[i + j] * coefficentArray[j];

		 bufferVector.push_back(temp);
	 }

	 //Decimate the sample
	 for (size_t i = 0; i < bufferVector.size(); i+=2)
		 outputVector.push_back(bufferVector.at(i));

	 //load the decimated sample into the sound buffer
	 result.loadFromSamples(&outputVector[0], outputVector.size(), 1, outputVector.size()/ buffer.getDuration().asSeconds());
}

//initalize the filter coefficents for the fir filter
void GetCoefficents(float* coefficentArray)
{
	float initArray[91] = {
		0.0007402732643054117,
		-0.0007116178196449282,
		-0.0012364542225753877,
		0.0004878382037768346,
		0.001762355408397323,
		-4.42067370785638e-18,
		-0.002215182400043849,
		-0.0007717219779807554,
		0.002468118275890691,
		0.0017997462427444813,
		-0.002385864864076639,
		-0.0029997753194695915,
		0.0018453409331850108,
		0.004228422134073137,
		-0.0007592690890261643,
		-0.005289349745070121,
		-0.0009003571537489589,
		0.005948391131440519,
		0.0030822569848409777,
		-0.005956801424111659,
		-0.00564241768842927,
		0.005080467069416566,
		0.008339545358107981,
		-0.003131762701341885,
		-0.01084034550601907,
		1.3106206228765793e-17,
		0.012733594561465547,
		0.004323800421297494,
		-0.013549309312476557,
		-0.009731690323690397,
		0.012775497060241557,
		0.015996022350404576,
		-0.009858263926207278,
		-0.022780555925105705,
		0.004155841182759176,
		0.029665112243643956,
		0.005226581766628221,
		-0.036181637361030625,
		-0.019949557006721064,
		0.04185792449918842,
		0.044243745670944155,
		-0.04626408217804201,
		-0.09396783582341778,
		0.04905629457673092,
		0.3142499866912212,
		0.45011339147505103,
		0.3142499866912212,
		0.04905629457673092,
		-0.09396783582341778,
		-0.04626408217804201,
		0.044243745670944155,
		0.04185792449918842,
		-0.019949557006721064,
		-0.036181637361030625,
		0.005226581766628221,
		0.029665112243643956,
		0.004155841182759176,
		-0.022780555925105705,
		-0.009858263926207278,
		0.015996022350404576,
		0.012775497060241557,
		-0.009731690323690397,
		-0.013549309312476557,
		0.004323800421297494,
		0.012733594561465547,
		1.3106206228765793e-17,
		-0.01084034550601907,
		-0.003131762701341885,
		0.008339545358107981,
		0.005080467069416566,
		-0.00564241768842927,
		-0.005956801424111659,
		0.0030822569848409777,
		0.005948391131440519,
		-0.0009003571537489589,
		-0.005289349745070121,
		-0.0007592690890261643,
		0.004228422134073137,
		0.0018453409331850108,
		-0.0029997753194695915,
		-0.002385864864076639,
		0.0017997462427444813,
		0.002468118275890691,
		-0.0007717219779807554,
		-0.002215182400043849,
		-4.42067370785638e-18,
		0.001762355408397323,
		0.0004878382037768346,
		-0.0012364542225753877,
		-0.0007116178196449282,
		0.0007402732643054117 };

	for (size_t i = 0; i < 90; i++)
	{
		coefficentArray[i] = initArray[i];
	}
}
