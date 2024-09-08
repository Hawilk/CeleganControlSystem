#include "commonAlgorithm.h"

void commonAlgorithm::histogramEqualization(uint8_t* dst, uint16_t* image, std::pair<uint16_t, uint16_t>& extrema)
{
	auto scale = 255.0 / (extrema.second - extrema.first);

	int64_t i = 0;
	for (i = 0; i < picHeight * picWidth; i++)
	{
		dst[i] = static_cast<uint8_t>((image[i] - extrema.first) * scale);
	}
}

std::pair<uint16_t, uint16_t> commonAlgorithm::findExtremaInImage(uint16_t* image)
{
	std::pair<uint16_t, uint16_t> extrema = std::make_pair(image[0], image[0]);

	int64_t i = 0;
	for (i = 0; i < picHeight * picWidth; i++)
	{
		auto pixel = image[i];
		if (pixel < extrema.first)
			extrema.first = pixel;
		else if (pixel > extrema.second)
			extrema.second = pixel;
	}

	return extrema;
}
