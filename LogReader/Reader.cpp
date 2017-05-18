#include "Reader.h"
#include <fstream>

Reader::Reader() {
	file_path_ = "";
}

ResultMap Reader::ReadLogFile() {
	StrPair line;
	ResultMap result;
	if (file_path_ != "") {
		std::ifstream log_file;
		log_file.open(file_path_);
		if (log_file) {
			while (!log_file.eof()) {
				std::string buff;
				getline(log_file, buff, '\n');
				line = getSubStr(buff);
				if (line.first != "\0" && line.second != "\0") { result.insert(line); }
			}
		}
	}
	return result;
}

void Reader::setPath(std::string path) {
	file_path_ = path;
}

Reader::~Reader() {}

StrPair Reader::getSubStr(std::string full_string) {
	StrPair substr{ "","" };
	char hex_symbol[3];
	std::string control_symbol{ "7e" };
	hex_symbol[2] = '\0';
	int i = 8;
	RevIter r_it_end;
	RevIter r_it_begin;
	r_it_end = std::find(full_string.rbegin(), full_string.rend(), 'e');
	if (r_it_end != full_string.rend()) {
		hex_symbol[1] = *r_it_end;
		hex_symbol[0] = *(++r_it_end);
		if (hex_symbol == control_symbol) {
			hex_symbol[0] = '\0';
			r_it_begin = ++r_it_end;
			while (hex_symbol != control_symbol) {
				r_it_begin = std::find(r_it_begin, full_string.rend(), 'e');
				if (r_it_begin != full_string.rend()) {
					hex_symbol[1] = *r_it_begin;
					hex_symbol[0] = *(++r_it_begin);
					if (hex_symbol == control_symbol) {
						for (r_it_begin -= 3; r_it_begin != r_it_end; --r_it_begin) {
							if (*r_it_begin != ' ') {
								if (i != 0) {
									substr.first.push_back(*r_it_begin);
									--i;
								}
								else { substr.second.push_back(*r_it_begin); }
							}
						}
					}
					else { ++r_it_begin; }
				}
			}
		}
	}
	return substr;
}