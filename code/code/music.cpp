#include "music.h"

bool enable_music = true;

// Helper function to convert std::string to std::wstring
std::wstring StringToWString(const std::string& str) {
	return std::wstring(str.begin(), str.end());
}

void PlaySong(const std::string& Song_Title) {
	if (!enable_music) {
		return;
	}

	std::wstring wSong_Title = StringToWString(Song_Title); // Convert to wide string
	PlaySound(NULL, NULL, 0); // Stop any currently playing sound
	PlaySound(wSong_Title.c_str(), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);


}

void MusicDialog() {
	char input = 'z';

	while (input != 'y' && input != 'n' && input != 'Y' && input != 'N') {
		std::cout << "music? (Y/n): ";
		std::cin >> input;

		if (input == 'y' || input == 'Y') {
			enable_music = true;
			return;
		}
		else if (input == 'n' || input == 'N') {
			enable_music = false;
			return;
		}
	}

}