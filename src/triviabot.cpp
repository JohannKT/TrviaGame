#include "triviabot.h"

TriviaBot::TriviaBot() {
	srand(time(NULL));
}

void TriviaBot::ImportQuestions(const char* path, bool overwrite) {
	std::string   line;
	std::ifstream inFile(path);
	if(!inFile.good()){
		std::cerr << "Error importing questions\n";
		exit(1);
	}
	// clear questions if requested
	if(overwrite) questions_.clear();

	// import questions from the file
	std::getline(inFile, line);
	while(inFile) {
		auto tokens = stringutils::TokenizeString(line, '`');
		questions_[tokens[0]] = tokens[1];
		std::getline(inFile, line);
	}
}

void TriviaBot::AddPlayer(const int& sd) {
	player_scores_[sd] = 0;
}

void TriviaBot::RemovePlayer(const int& sd) {
	player_scores_.erase(sd);
}

std::string TriviaBot::GetRandomQuestion() const {
	auto it = questions_.begin();
	std::advance(it, rand() % questions_.size());
	return it->first;
}

std::string TriviaBot::GetAnswer(const std::string& question) const {
	return questions_.at(question);
}

std::string TriviaBot::GetHint(const std::string& question) const {
	std::string answer = GetAnswer(question);
	std::string hint(answer.length(), '_');

	// show spaces
	for(int i = 0; i < answer.length(); ++i) {
		if(answer[i] == ' ') {
			hint[i] = ' ';
		}
	}

	// pick other random places to hint at
	for(int i = 0; i < answer.length() * 0.3; ++i) {
		size_t index = rand() % answer.length();
		hint[index] = answer[index];
	}

	return hint;
}
void TriviaBot::IncreaseScore(const int& sd) {
	auto itr = player_scores_.find(sd);
	++itr->second;
}
