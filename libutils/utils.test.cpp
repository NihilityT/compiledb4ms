#include <gtest/gtest.h>
#include <libutils/utils.h>

using namespace utils;

TEST(Utils, read_file)
{
	std::string content = read_file("./libutils/utils.test.txt");
	ASSERT_EQ("123", content);
}

TEST(Utils, split)
{
	std::vector<std::string> splited = split("1 2 3 ", ' ');
	std::vector<std::string> expected{
		"1", "2", "3",
	};
	ASSERT_EQ(splited, expected);
}

TEST(Utils, replace)
{
	std::string s = "1,2,3,2,3";
	replace(s, ",2,", "2");
	ASSERT_EQ(s, "123,2,3");
}
