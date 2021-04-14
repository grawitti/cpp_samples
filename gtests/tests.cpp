#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "sample.cpp"

class MinimalistPrinter : public ::testing::EmptyTestEventListener {
	// Called before a test starts.
	virtual void OnTestStart(const ::testing::TestInfo& test_info) {
		printf("*** Test %s.%s starting.\n",
		       test_info.test_suite_name(),
		       test_info.name());
	}

	// Called after a failed assertion or a SUCCESS().
	virtual void
	OnTestPartResult(const ::testing::TestPartResult& test_part_result) {
		printf("%s in %s:%d\n%s\n",
		       test_part_result.failed() ? "*** Failure" : "Success",
		       test_part_result.file_name(),
		       test_part_result.line_number(),
		       test_part_result.summary());
	}

	// Called after a test ends.
	virtual void OnTestEnd(const ::testing::TestInfo& test_info) {
		printf("*** Test %s.%s ending.\n",
		       test_info.test_suite_name(),
		       test_info.name());
	}
};

class FooEnvironment : public ::testing::Environment {
public:
	~FooEnvironment() override {}

	void SetUp() override {
		std::cout << "Global SetUp()\n";
		i = 1;
		c = 'c';
	}
	void TearDown() override {
		std::cout << "Global TearDown()\n";
		i = 0;
		c = ' ';
	}

	int i;
	char c;
	static int iii;
};

::testing::Environment* const foo_env =
    AddGlobalTestEnvironment(new FooEnvironment);

class TestFoo : public ::testing::Test {
protected:
	void SetUp() {
		foo.i = 5;
		std::cout << "SetUp\n";
	}

	void TearDown() { std::cout << "TearDown\n"; }

	static void SetUpTestSuite() { std::cout << "SetUpTestFoo\n"; }

	static void TearDownTestSuite() { std::cout << "TearDownTestFoo\n"; }

	Foo foo;
};

int Foo::ii = 15;

TEST_F(TestFoo, test1) {
	iii = 12;
	ASSERT_EQ(foo.i, 5);
	foo.set_i(10);
	ASSERT_EQ(foo.i, 10);
}

TEST_F(TestFoo, DISABLED_test2) {
	const char* str = "Error msg";
	ASSERT_EQ(foo.i, 6) << "Можно выводить свои сообщения: " << str;
}

TEST_F(TestFoo, TestAsThrow) {
	// Так же можно генерировать не фатальные проверки EXPECT_*
	// Проверка на генерацию исключения определенного типа
	ASSERT_THROW(foo.set_i(-1), std::runtime_error);
	// Проверка на генерацию исключения любого типа
	ASSERT_ANY_THROW(foo.set_i(-1));
	// Проверка что не генерирует исключение
	ASSERT_NO_THROW(foo.set_i(0));
}

TEST(SampleTests, TestExTrue) {
	EXPECT_TRUE(is_positive(1));
	SUCCEED() << "Генерирует удачу";
	ADD_FAILURE() << "Генерирует не фатальную неудачу";
	ADD_FAILURE_AT("not_exist_file.cpp", 11) << "Генерирует не фатальную "
	                                            "неудачу с указанием на место "
	                                            "вручную";
	FAIL() << "Генерирует фатальную неудачу";
}

TEST(SampleTests, TestExFalse) {
	EXPECT_FALSE(is_positive(-1));
}

TEST(SampleTests, TestExEq) {
	EXPECT_EQ(is_positive_i(1), 1);
}

TEST(SampleTests, TestExEqN) {
	EXPECT_EQ(is_positive_i(-1), 0);
}

TEST(SampleTests, TestAssStrEq) {
	ASSERT_EQ(is_positive_char(1), "true");
}

TEST(SampleTests, DISABLED_TestAssStrNe) {
	ASSERT_NE(is_positive_char(-1), "true");
}

TEST(SampleTests, TestAssStrCaseEq) {
	ASSERT_NE(is_positive_char(1), "TRUE");
}

TEST(AdvancedTests, ExPredicant) {
	int a = 1;
	EXPECT_PRED1(is_positive, a);
}

::testing::AssertionResult IsEven(int n) {
	if ((n % 2) == 0)
		return ::testing::AssertionSuccess();
	else
		return ::testing::AssertionFailure() << n << " is odd";
}

TEST(AdvancedTests, IsEven) {
	EXPECT_TRUE(IsEven(2));
}

TEST(AdvancedTests, TestsFloating) {
	float a = 2.123456;
	float b = 2.123456111;
	EXPECT_FLOAT_EQ(a, b);

	double c = 1.123456789;
	double d = 1.123456789;
	EXPECT_DOUBLE_EQ(c, d);
}

TEST(AdvancedTests, TestMock) {
	// Используем gMock для проверки что строка начинается с "tr"
	EXPECT_THAT(is_positive_char(1), ::testing::StartsWith("tr"));
	EXPECT_THAT(is_positive_char(1), ::testing::HasSubstr("ue"));
	EXPECT_THAT(is_positive_char(1), ::testing::MatchesRegex("^\\w+"));
}

TEST(AdvancedTests, TypeTest) {
	// Компилятор будет ругаться есть типы не одинаковые
	::testing::StaticAssertTypeEq<int, int>();
}

int ii = 9;

TEST(DeathTests, Foo) {
	SCOPED_TRACE("Test scope trace mesaage");

	ASSERT_EXIT(
	    {
		    // Ошибка сегментации
		    int* nu = nullptr;
		    *nu     = 3;
	    },
	    ::testing::KilledBySignal(SIGSEGV),
	    ".*");

	// Если в текущем тесте были выявлены сбои вернёт true
	if (HasFatalFailure())
		std::cout << "Была неудача";
}

TEST(AdvancedTests, RecordInfo) {
	const ::testing::TestInfo* const test_info =
	    ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << "Test name: " << test_info->name()
	          << "\nTest suite name: " << test_info->test_suite_name() << "\n";
	RecordProperty("TestRecord", 123);
}

