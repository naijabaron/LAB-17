#include <stdio.h>
#include "libs/data_struct/string/string.h"
#include <malloc.h>
#include <ctype.h>

#define ASSERT_STRING(expected, got) assertString(expected, got, __FILE__, __FUNCTION__, __LINE__)
#define ASSERT_BOOLEAN(expected, got) assertBoolean(expected, got, __FILE__, __FUNCTION__, __LINE__)
#define ASSERT_INT(expected, got) assertInt(expected, got, __FILE__, __FUNCTION__, __LINE__)

static void assertString(char *expected, char *got, char const *fileName, char const *funcName, int line) {
    if (compareStrings(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else {
        fprintf(stdout, "%s on line %d - OK\n", funcName, line);
    }
}

static void assertBoolean(bool expected, bool got, char const *fileName, char const *funcName, int line) {
    if (got != expected) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", (expected ? "true" : "false"));
        fprintf(stderr, "Got: \"%s\"\n\n", (got ? "true" : "false"));
    } else {
        fprintf(stdout, "%s on line %d - OK\n", funcName, line);
    }
}

static void assertInt(int expected, int got, char const *fileName, char const *funcName, int line) {
    if (got != expected) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%d\"\n", expected);
        fprintf(stderr, "Got: \"%d\"\n\n", got);
    } else {
        fprintf(stdout, "%s on line %d - OK\n", funcName, line);
    }
}

static void printTest(char* testableComponent, void (*testingFunction)()) {
    printf("Testing %s:\n\n", testableComponent);

    testingFunction();

    printf("\n--------------------------------------------------\n\n");
}

void testGetLength() {
    ASSERT_INT(0, getLength(""));
    ASSERT_INT(3, getLength("abc"));
}

void testFind() {
    char* testString = "abcdef";

    ASSERT_INT(3, find(testString, testString + getLength(testString), 'd') - testString);
}

void testFindNonSpace() {
    char* testString = "  abc  ";

    ASSERT_INT(2, findNonSpace(testString) - testString);
}

void testFindSpace() {
    char* testString = "abc def";

    ASSERT_INT(3, findSpace(testString) - testString);
}

void testFindNonSpaceReverse() {
    char* testString = "abc def  ";

    ASSERT_INT(6, findNonSpaceReverse(testString, testString + getLength(testString)) - testString);
}

void testFindSpaceReverse() {
    char* testString = "abc def  ghi";

    ASSERT_INT(8, findSpaceReverse(testString, testString + getLength(testString)) - testString);
}

void testCompareStrings() {
    ASSERT_INT(-1, compareStrings("abc", "def"));
    ASSERT_INT(0, compareStrings("abc", "abc"));
    ASSERT_INT(1, compareStrings("def", "abc"));
}

void testCopy() {
    char* source = "abc";
    char* destination = malloc(CHAR_SIZE * 4);

    *copy(source, source + getLength(source), destination) = '\0';

    ASSERT_STRING("abc", destination);
}

static bool isLetter(char character) {
    return isalpha(character);
}

void testCopyIf() {
    char* source = "6ab12c57";
    char* destination = malloc(CHAR_SIZE * 4);

    *copyIf(source, source + getLength(source), destination, isLetter) = '\0';

    ASSERT_STRING("abc", destination);
}

void testCopyIfReverse() {
    char* source = "6ab12c57";
    char* destination = malloc(CHAR_SIZE * 4);

    *copyIfReverse(source + getLength(source), source, destination, isLetter) = '\0';

    ASSERT_STRING("cba", destination);
}

int main() {
    printTest("getLength", testGetLength);
    printTest("find", testFind);
    printTest("findNonSpace", testFindNonSpace);
    printTest("findSpace", testFindSpace);
    printTest("findNonSpaceReverse", testFindNonSpaceReverse);
    printTest("findSpaceReverse", testFindSpaceReverse);
    printTest("compareStrings", testCompareStrings);
    printTest("copy", testCopy);
    printTest("copyIf", testCopyIf);
    printTest("copyIfReverse", testCopyIfReverse);
}