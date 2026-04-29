/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
TEST(GuesserTest, smoke_test)
{
  Guesser object("Secret");
  ASSERT_EQ( 1+1, 2 );
}

TEST(GuesserTest, secret_match) {
	Guesser object("Secret");
	ASSERT_EQ(0, object.distance("Secret"));
}

TEST(GuesserTest, secret_smaller) {
	Guesser object("Secret");
	ASSERT_EQ(6, object.distance("NOT Secret"));
}

TEST(GuesserTest, secret_larger) {
	Guesser object("Secret");
	ASSERT_EQ(3, object.distance("Sec"));
}

TEST(GuesserTest, secret_larger_no_matches) {
	Guesser object("Secret");
	ASSERT_EQ(6, object.distance("abd"));
}

TEST(GuesserTest, secret_empty) {
	Guesser object("");
	ASSERT_EQ(0, object.distance("Test"));
}

TEST(GuesserTest, guess_empty) {
	Guesser object("Secret");
	ASSERT_EQ(6, object.distance(""));
}

TEST(GuesserTest, large_secret) {
	Guesser object("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"); //33 letters
	ASSERT_EQ(32, object.distance(""));
}

////////////////////////////////

TEST(GuesserTest, four_guesses) {
	Guesser object("Secret");
	bool guess = object.match("Secret");
	guess = object.match("Secre");
	guess = object.match("Secren");
	guess = object.match("Secret");
	ASSERT_TRUE(guess);
}

TEST(GuesserTest, test) {
	Guesser object("Secret");
	ASSERT_TRUE(object.match("Secret"));
	ASSERT_FALSE(object.match("Secre"));
	ASSERT_FALSE(object.match("Secren"));
	ASSERT_TRUE(object.match("Secret"));
}

TEST(GuesserTest, lockout_in_distance) {
	Guesser object("Secret");
	ASSERT_FALSE(object.match("Secre"));
	ASSERT_FALSE(object.match("Secre"));
	ASSERT_FALSE(object.match("Secre"));
	ASSERT_FALSE(object.match("Secret")); //locked out bc 3 wrong guesses
}

TEST(GuesserTest, brute_force) {
	Guesser object("Secret");
	ASSERT_FALSE(object.match("This is brute force"));
	ASSERT_FALSE(object.match("Secret"));
}

TEST(GuesserTest, corret_then_brute_force) {
	Guesser object("Secret");
	ASSERT_TRUE(object.match("Secret"));
	ASSERT_FALSE(object.match("Secren"));
	ASSERT_FALSE(object.match("aisjdoawindoaiwndoa"));
	ASSERT_FALSE(object.match("Secret"));
}

TEST(GuesserTest, empty_secret_match) {
	Guesser object("");
	ASSERT_FALSE(object.match("Not brute force because empty string"));
	ASSERT_FALSE(object.match("STILL NOT"));
	ASSERT_TRUE(object.match(""));
}

TEST(GuesserTest, count_reset) { //This should return true because it should reset the guess  count on correct guess
	Guesser object("Secret");
	ASSERT_TRUE(object.match("Secret"));
	ASSERT_FALSE(object.match("Secre"));
	ASSERT_FALSE(object.match("Secre"));
	ASSERT_TRUE(object.match("Secret"));
	ASSERT_FALSE(object.match("Secre"));
	ASSERT_FALSE(object.match("Secre"));
	ASSERT_TRUE(object.match("Secret"));
	ASSERT_FALSE(object.match("Secre"));
	ASSERT_FALSE(object.match("Secre"));
	ASSERT_TRUE(object.match("Secret"));
}