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

uint32_t commonAlgorithm::getCurTimeStamp()
{
	//获取当前时间
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	std::tm* local_time = std::localtime(&now_time);

	// 获取毫秒部分
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

	//组合时间戳为格式 hhmmssmmm
	uint32_t timestamp = (local_time->tm_hour * 10000000) + (local_time->tm_min * 100000) +
		(local_time->tm_sec * 1000) + static_cast<unsigned int>(milliseconds.count());

	return timestamp;
}

curTime commonAlgorithm::convertTimeStamp(uint32_t timestamp)
{
	curTime item;
	item.millisecond = timestamp % 1000;
	timestamp /= 1000;

	item.second = timestamp % 100;
	timestamp /= 100;

	item.minute = timestamp % 100;
	timestamp /= 100;

	item.hour = timestamp;

	return item;
}
