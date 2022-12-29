#include <Json.h>
#include <CommandLineManager.h>
#include <Macro.h>

#include <fstream>

Json LoadJsonFromFile(const std::string& InPath)
{
	std::string ContentPath = CommandLineManager::Get().GetValue("-Content");

	std::ifstream JsonFile(ContentPath + InPath);
	CHECK((JsonFile.is_open()), "failed to load json file");

	return Json::parse(JsonFile);
}
