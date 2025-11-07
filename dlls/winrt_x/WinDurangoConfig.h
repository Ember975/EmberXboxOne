#pragma once

#include "toml.hpp"

struct WinDurangoConfigData
{
	std::string gamertag{ "XboxOneTest" };
	int gamerscore{ 0 };
	int reputation{ 0 };
	enum class AgeGroup
	{
		Child,
		Teen,
		Adult,
		Unknown
	} ageGroup{ AgeGroup::Unknown };
};

class WinDurangoConfig
{
public:
	static WinDurangoConfig& Instance();

	[[nodiscard]] WinDurangoConfigData GetData() const;
	void SetData(const WinDurangoConfigData& data);

	WinDurangoConfig(const WinDurangoConfig&) = delete;
	WinDurangoConfig& operator=(const WinDurangoConfig&) = delete;
	WinDurangoConfig(WinDurangoConfig&&) = delete;
	WinDurangoConfig& operator=(WinDurangoConfig&&) = delete;

private:
	WinDurangoConfig();
	~WinDurangoConfig() = default;

	static void ProcessConfigFile();

	WinDurangoConfigData _data{};

	std::string _configFilePath{};
};
