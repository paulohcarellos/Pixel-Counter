#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

#include "LodePNG.h"

int getPixels(std::string filename);

int main(int argc, char** argv) {

	std::string folderName;
	std::vector<std::string> filePaths;

	if (argc != 2) {

		std::cout << "Usage: 'program.exe -folderName'";
		return 1;
	}

	else
		folderName = ((std::string)argv[1]).substr(1);

	try {

		for (const std::filesystem::directory_entry& it : std::filesystem::directory_iterator(folderName))
			filePaths.push_back(it.path().string());
	}
	
	catch (std::filesystem::filesystem_error) {

		std::cout << "Could not open folder" << std::endl;
		return 1;
	}

	for (std::string& it : filePaths) {

		int pixels = getPixels(it);

		if (pixels > 0)
			std::cout << it.substr(folderName.length() + 1) << " - " << pixels << "px" << std::endl;
	}

	return 0;
}

int getPixels(std::string filename) {

	std::vector<unsigned char> image;
	unsigned w, h;

	//If there's an error with the png file 'error' will be true
	unsigned error = lodepng::decode(image, w, h, filename);

	if (error) {

		std::cout << "Could not decode " << filename << std::endl;
		return 0;
	}

	return image.size() / 4;
}