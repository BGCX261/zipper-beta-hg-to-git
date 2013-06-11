/* 
 * File:   consoletest.h
 * Author: Kenji Lozano
 * Description: Tests for the console user interface
 *
 */

#ifndef CONSOLETEST_H
#define	CONSOLETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "zipper.h"
#include "help.h"
#include "outputerror.h"
#include "errorcode.h"


class ConsoleTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(ConsoleTest);

    CPPUNIT_TEST(itShouldShowTheHelpWhenTheWrittenCommandIsHWithoutArgs);
    CPPUNIT_TEST(itShouldShowAnUnknowArgsErrorWhenTheWrittenCommandIsHWithArgs);
    CPPUNIT_TEST(itShouldShowAnUnknowCompressionArgsWhenTheWrittenCCommandIsWrong);
    CPPUNIT_TEST(itShouldShowAnUnknowOptionWhenTheCommandDoesNotExists);
    CPPUNIT_TEST(itShouldShowAnUnknowArgsErrorWhenTheInputCommandDoesNotMatch);
    CPPUNIT_TEST(testTraverseOptionWithAnyParameter);
    CPPUNIT_TEST(testTraverseOptionWithANonZipFile);
    CPPUNIT_TEST(testTraverseOptionWithAFileThatDoNotExist);
    CPPUNIT_TEST(testTraverseOptionWithAZipFile);
    CPPUNIT_TEST(testTraverseOptionWithLevel);
    CPPUNIT_TEST(testTraverseOptionWithWrongLevel);
    CPPUNIT_TEST_SUITE_END();

public:
    ConsoleTest();
    virtual ~ConsoleTest();
    void setUp();
    void tearDown();

private:
    void itShouldShowTheHelpWhenTheWrittenCommandIsHWithoutArgs();
    void itShouldShowAnUnknowArgsErrorWhenTheWrittenCommandIsHWithArgs();
    void itShouldShowAnUnknowCompressionArgsWhenTheWrittenCCommandIsWrong();
    void itShouldShowAnUnknowOptionWhenTheCommandDoesNotExists();
    void itShouldShowAnUnknowArgsErrorWhenTheInputCommandDoesNotMatch();
    void testTraverseOptionWithAnyParameter();
    void testTraverseOptionWithANonZipFile();
    void testTraverseOptionWithAFileThatDoNotExist();
    void testTraverseOptionWithAZipFile();
    void testTraverseOptionWithLevel();
    void testTraverseOptionWithWrongLevel();
};

#endif	/* CONSOLETEST_H */

