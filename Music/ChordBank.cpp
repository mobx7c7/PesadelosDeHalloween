/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-06-10
***********************************************************************/
#include "ChordBank.h"

namespace KeyMapper
{
	int getNumber(float frequency)
	{
		return 12*log2(frequency/440.0f)+49;
	}
	float getFrequency(int number)
	{
		return pow(pow(2, 1.0f/12),number-49)*440.0f;
	}
};

void ChordBank::setChord(string chord, vector<float>& key_list)
{
	ChordMapIterator it = chord_map.find(chord);
	if(it != chord_map.end())
	{
		it->second = key_list;
		return;
	}
	chord_map.insert(ChordMapPair(chord, key_list));
}
vector<float> ChordBank::getChordKeys(string chord)
{
	ChordMapIterator it = chord_map.find(chord);
	if(it != chord_map.end())
	{
		return it->second;
	}
	return vector<float>();
}

vector<string> ChordBank::getChordNames()
{
    vector<string> chordNames(chord_map.size(), " ");
    ChordMapIterator it = chord_map.begin();
    for(int i=0; it != chord_map.end(); i++, it++)
    {
        chordNames[i] = it->first;
    }
    return chordNames;
}

int ChordBank::readChordFile(string file_path)
{
	ifstream f("res\\notes.txt");

	if(!f)
	{
	    cout << "[ChordBank] Impossível abrir arquivo " << file_path << endl;
		return -1;
	}

	cout << "[ChordBank] Abrindo arquivo " << file_path << endl;

	stringstream    ss;
	string          line;
	string          curr_name;
	string          curr_values;
	int             curr_length;
	int             pos_curr;
	int             pos_begin;
	int             pos_end;

	while(getline(f,line))
	{
		if((pos_curr = line.find("name")) != -1)
		{
			if((pos_curr = line.find_first_of('=')) != -1)
			{
				if((pos_begin = line.find_first_of('\"')) != -1 && (pos_end = line.find_last_of('\"')) != -1)
				{
					curr_name = line.substr(pos_begin+1, pos_end-pos_begin-1);
				}
			}
		}
		else if((pos_curr = line.find("length")) != -1)
		{
			if((pos_curr = line.find_first_of('=')) != -1)
			{
				ss.clear();
				ss.str( line.substr(pos_curr+1) );
				ss >> curr_length;
			}
		}
		else if((pos_curr = line.find("values")) != -1)
		{
			if((pos_curr = line.find_first_of('=')) != -1)
			{
				if((pos_begin = line.find_first_of('{')) != -1 && (pos_end = line.find_last_of('}')) != -1)
				{
					curr_values = line.substr(pos_begin+1, pos_end-pos_begin-1);
				}
			}
		}

		// se possuir os parâmetros nescessários...
		if(!curr_name.empty() && curr_length > 0 && !curr_values.empty())
		{
			pos_begin = pos_end = 0;
			// tokeniza
			vector<float> values(curr_length, 0);
			for(int i=0; i<curr_length; i++)
			{
				pos_end = curr_values.find_first_of(',', pos_begin);
				if(pos_end == -1) pos_end = curr_values.size();

				int value;
				ss.clear();
				ss.str( curr_values.substr(pos_begin, pos_end-pos_begin) );
				ss >> value;

				values[i] = KeyMapper::getFrequency(value);
				pos_begin = pos_end+1;
			}
			// ordena
			std::sort(values.begin(), values.end());
			// insere
			setChord(curr_name, values);
			// limpa
			curr_values.clear();
			curr_name.clear();
			curr_length = 0;
		}
	}
	f.close();

//	map<string, vector<float>>::iterator it = chord_map.begin();
//	while(it != chord_map.end())
//	{
//		cout << it->first << " = ";
//		for(float& x : it->second)
//		{
//			cout << x << " ";
//		}
//		cout << endl;
//		it++;
//	}

	return 0;
}
