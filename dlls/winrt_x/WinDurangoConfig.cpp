#include "pch.h"
#include "WinDurangoConfig.h"

WinDurangoConfig& WinDurangoConfig::Instance()
{
	static WinDurangoConfig instance;
	return instance;
}

WinDurangoConfigData WinDurangoConfig::GetData() const
{
	return _data;
}

void WinDurangoConfig::SetData(const WinDurangoConfigData& data)
{
	_data = data;
}

using namespace std::string_view_literals;

void WinDurangoConfig::ProcessConfigFile()
{
	static constexpr auto default_config_data = R"(
		[WinDurango]
		Gamertag = "TheDurangler2"
		Gamerscore = 1500
		Reputation = 5
		AgeGroup = "Adult"
	)"sv;

	try
	{
		// TODO: Try to read the config file from disk. If it doesn't exist, use the default data.

		auto tbl = toml::parse(default_config_data);

		const auto gamertag_opt = tbl["WinDurango"]["Gamertag"].value<std::string_view>();
		const auto gamerscore_opt = tbl["WinDurango"]["Gamerscore"].value<int>();
		const auto reputation_opt = tbl["WinDurango"]["Reputation"].value<int>();
		const auto agegroup_opt = tbl["WinDurango"]["AgeGroup"].value<std::string_view>();

		const WinDurangoConfigData data
		{
			.gamertag = std::string(gamertag_opt.value()),
			.gamerscore = gamerscore_opt.value_or(0),
			.reputation = reputation_opt.value_or(0),
			.ageGroup =
				agegroup_opt.has_value()
					? (agegroup_opt.value() == "Child" ? WinDurangoConfigData::AgeGroup::Child
						: agegroup_opt.value() == "Teen" ? WinDurangoConfigData::AgeGroup::Teen
						: agegroup_opt.value() == "Adult" ? WinDurangoConfigData::AgeGroup::Adult
						: WinDurangoConfigData::AgeGroup::Unknown)
					: WinDurangoConfigData::AgeGroup::Unknown
		};

		Instance().SetData(data);

		// TODO: Save the config file, if the file didn't exist before.
	}
	catch (const toml::parse_error& err)
	{
		std::cerr << "Parsing failed:\n" << err << "\n";
	}
}

WinDurangoConfig::WinDurangoConfig()
{
	ProcessConfigFile();
}