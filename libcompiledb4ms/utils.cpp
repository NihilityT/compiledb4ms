#include <libcompiledb4ms/utils.h>
#include <libutils/utils.h>


namespace compiledb4ms {
namespace utils {

std::string Environment::get(const std::string& name, std::string_view default_value)
{
	auto it = m_environments.find(name);
	if (it != m_environments.cend()) {
		return it->second;
	}
	return ::utils::get_env(name.c_str(), default_value);
}

void Environment::set(std::unordered_map<std::string, std::string> environments)
{
	m_environments = std::move(environments);
}

Environment& get_environment()
{
	static Environment env;
	return env;
}

std::filesystem::path get_cl_path()
{
	auto& env = get_environment();
	return std::filesystem::path(env.get("VCToolsInstallDir"))
		/ "bin" / ("Host" + env.get("VSCMD_ARG_HOST_ARCH"))
		/ env.get("VSCMD_ARG_TGT_ARCH") / "cl.exe";
}

}
}
