#include "commonAlgorithm.h"

void commonAlgorithm::histogramEqualization(uint8_t* dst, uint16_t* image, std::pair<uint16_t, uint16_t>& extrema)
{
	
}

std::pair<uint16_t, uint16_t> commonAlgorithm::findExtremaInImage(const uint16_t* image)
{
	std::pair<uint16_t, uint16_t> extrema = std::make_pair(image[0], image[0]);

	for (uint8_t i = 0; i < picHeight * picWidth; i++)
	{
		auto pixel = image[i];
		if (pixel < extrema.first)
			extrema.first = pixel;
		else if (pixel > extrema.second)
			extrema.second = pixel;
	}

	return extrema;
}
