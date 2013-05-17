/*
 * File:   consoletest.h
 * Author: Kenji
 *
 * Created on 17-may-2013, 10:35:20
 */

#ifndef CONSOLETEST_H
#define	CONSOLETEST_H

#include <cppunit/extensions/HelperMacros.h>

class ConsoleTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(ConsoleTest);

    CPPUNIT_TEST(itShouldShowTheHelpWhenTheWrittenCommandIsHWithoutArgs);
    CPPUNIT_TEST(itShouldShowAnUnknowArgsErrorWhenTheWrittenCommandIsHWithArgs);
    CPPUNIT_TEST(itShouldShowAnUnknowCompressionArgsWhenTheWrittenCCommandIsWrong);
    CPPUNIT_TEST(itShouldShowAnUnknowOptionWhenTheCommandDoesNotExists);
    CPPUNIT_TEST(itShouldShowAnUnknowArgsErrorWhenTheInputCommandDoesNotMatch);

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
};

#endif	/* CONSOLETEST_H */

