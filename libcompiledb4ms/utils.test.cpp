#include <gtest/gtest.h>
#include <libcompiledb4ms/utils.h>
#include <libutils/utils.h>

using namespace compiledb4ms::utils;

TEST(Compiledb4ms_utils_Environment, get_environment)
{
	Environment& env = get_environment();
	ASSERT_FALSE(env.get("PATH").empty());
}

TEST(Compiledb4ms_utils_Environment, return_default_value_when_environment_not_exists)
{
	Environment& env = get_environment();
	ASSERT_EQ(env.get("NOT_EXISTS_ENVIRONMENT", "123"), "123");
}

TEST(Compiledb4ms_utils_Environment, inject_environment_for_test)
{
	Environment& env = get_environment();
	env.set({
		{"TEST_ENVIRONMENT", "890"},
	});
	ASSERT_EQ(env.get("TEST_ENVIRONMENT"), "890");
	ASSERT_EQ(env.get("test_environment"), "");
}

TEST(Compiledb4ms_utils, get_cl_path)
{
	Environment& env = get_environment();
	env.set({
		{"VCToolsInstallDir", "D:/"},
		{"VSCMD_ARG_HOST_ARCH", "x64"},
		{"VSCMD_ARG_TGT_ARCH", "x86"},
	});
	ASSERT_EQ(get_cl_path(), "D:/bin/Hostx64/x86/cl.exe");
}
