#include <iostream>
#include <fstream>
#include <string>
#include <intrin.h>

void readToInt(std::ifstream& stream, int* i) {
	char c;
	char* mod = (char*)i;
	for (int i = 0; i < 4 ; i++) {
		stream.read(&c, sizeof(c));
		mod[3-i] = c;
	}
}

void readToFloat(std::ifstream& stream, float* f) {
	char c;
	char* mod = (char*)f;
	for (int i = 0; i < 4; i++) {
		stream.read(&c, sizeof(c));
		mod[3-i] = c;
	}
}


int main()
{
	int version = 0;
	int hash = 0;
	int entries = 0;
	int s = 0;
	std::ifstream is;
	std::ofstream os;
	os.open("parsed.txt");
	is.open("chart.fsgmub", std::ios::binary);
	if (is.is_open()) {
		readToInt(is, &version);
		readToInt(is, &hash);
		readToInt(is, &entries);
		readToInt(is, &s);

		os << "version: " << version << std::endl;
		os << "crc:" << (unsigned int)hash << std::endl;
		os << "note entries:" << entries << std::endl;
		os << "string length:" << s << std::endl;

		for (int i = 0; i < entries; i++) {
			os << "entry #" << i << ":\t";
			float time;
			int type;
			float length;
			float extra;

			readToFloat(is, &time);
			readToInt(is, &type);
			readToFloat(is, &length);
			readToFloat(is, &extra);

			if (type == 0)os << "green tap \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 1)os << "red tap \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 2)os << "blue tap \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 3)os << "scr g up \tat\t" << time << std::endl;
			else if (type == 4)os << "scr b up \tat\t" << time << std::endl;
			else if (type == 5)os << "scr g down \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 6)os << "scr b down \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 7)os << "scr g any \tat\t" << time << std::endl;
			else if (type == 8)os << "scr b any \tat\t" << time << std::endl;
			else if (type == 9)os << "cross b \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 10)os << "cross c \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 11)os << "cross g \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 12)os << "eff. g \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 13)os << "eff. b \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 14)os << "eff. r \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 15)os << "euphoria \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 16)os << "fs sample/scratch \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 17)os << "fs crossfade \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 20)os << "green scr. zone\tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 21)os << "blue scr. zone \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 22)os << "eff. all lanes \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 23)os << "cross force center \tat\t" << time << std::endl;
			else if (type == 26)os << "battle chart data \tat\t" << time << "\twith data\t" << (unsigned int)extra << std::endl;
			else if (type == 27)os << "cross spike g \tat\t" << time << std::endl;
			else if (type == 28)os << "cross spike b \tat\t" << time << std::endl;
			else if (type == 29)os << "cross spike c \tat\t" << time << std::endl;
			else if (type == 30)os << "megamix transition \tat\t" << time << "\twith data\t" << (unsigned int)extra << std::endl;
			else if (type == 31)os << "fs marker g \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type == 32)os << "fs marker b \tat\t" << time << "\tlong for\t" << length << std::endl;
			else if (type >= 0x05FFFFFF && type <= 0x06000009)os << "effect id \tat\t" << time << "\twith data\t" << (unsigned int)extra << std::endl;
			else if (type == 0x0B000001)os << "bpm marker" << "\tat\t" << time << std::endl;
			else if (type == 0x0B000002)os << "beats / minute \t\t" << extra << std::endl;
			else if (type == 0x0AFFFFFF)os << "charter string data" << std::endl;
			else if (type == 0x09FFFFFF)os << "checkpoint marker \tat\t" << time << std::endl;
			else if (type == 0xFFFFFFFF)os << "chart start"<< std::endl;
			else os << "undefined \t" << type << std::endl;
  		}
		char text[4096];
		is.read(text,s );

		os << "string data:" << text << std::endl;
		std::cout << "done parsing file" << std::endl;
	}
	else if(os.is_open()){
		os << "ERROR: cannot open original file 'chart.fsgmub'." << std::endl;
 		std::cerr << "error: cannot open original file 'chart.fsgmub'." << std::endl;
	}
	else {
		std::cerr << "error: cannot open original file nor parsed output. check if you have permission to write" << std::endl;
	}
	std::cout << "Press enter to close" << std::endl;
	std::cin.get();
	return 0;
}
