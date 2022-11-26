#include <gtest/gtest.h>
#include <string>
#include <advent_registry.h>

static Registry TEST_REGISTRY;

struct TestSolution1: Solution{
    static const char* saved_filename;
    virtual int run(const char* input_filename) {
        saved_filename = input_filename;
        return 0;
    }
};

const char* TestSolution1::saved_filename = "none";

static RegisterSolution<TestSolution1> _rs1(TEST_REGISTRY, 1);

struct TestSolution2: Solution{
    static const char* saved_filename;
    virtual int run(const char* input_filename) {
        saved_filename = input_filename;
        return 0;
    }
};
const char* TestSolution2::saved_filename = "none";

static RegisterSolution<TestSolution2> _rs2(TEST_REGISTRY, 2);

TEST(RegistryTest, InitIsOk) {
    EXPECT_STREQ(TestSolution1::saved_filename, "none");
    EXPECT_STREQ(TestSolution2::saved_filename, "none");
}

TEST(RegistryTest, Day1) {
    TEST_REGISTRY.run(1, "day1");
    EXPECT_STREQ(TestSolution1::saved_filename, "day1");
    EXPECT_STREQ(TestSolution2::saved_filename, "none");
}

TEST(RegistryTest, Day2) {
    TEST_REGISTRY.run(2, "day2");
    EXPECT_STREQ(TestSolution1::saved_filename, "none");
    EXPECT_STREQ(TestSolution2::saved_filename, "day2");
}
