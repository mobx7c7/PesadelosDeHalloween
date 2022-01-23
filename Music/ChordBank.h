/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-06-10
***********************************************************************/
#ifndef CHORDBANK_H
#define CHORDBANK_H

#include <iostream>
#include <fstream>
#include <algorithm> // sort
#include <vector>
#include <string>
#include <sstream>
#include <map>

using std::stringstream;
using std::string;
using std::ifstream;
using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::pair;

namespace KeyMapper
{
	// Baseado em: http://en.wikipedia.org/wiki/Piano_key_frequencies
	int     getNumber(float frequency);

	float   getFrequency(int number);
};

typedef map<string, vector<float>>              ChordMap;
typedef pair<string, vector<float>>             ChordMapPair;
typedef map<string, vector<float>>::iterator    ChordMapIterator;

class ChordBank
{
	protected:

		ChordMap chord_map;

	public:

		void            setChord(string chord, vector<float>& key_list);

		vector<float>   getChordKeys(string chord);

		vector<string>  getChordNames();

		int             readChordFile(string file_path);

};
#endif // CHORDBANK_H
