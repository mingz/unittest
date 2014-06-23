/*
 *  CUnit - A Unit testing framework library for C.
 *  Copyright (C) 2001        Anil Kumar
 *  Copyright (C) 2004, 2005  Anil Kumar, Jerry St.Clair
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <CUnit.h>


/*****************************************************************************/
/*                        Test function begins here                          */
/*****************************************************************************/

#define UBOOL8 unsigned char
#define cmsUtl_strncasecmp strncasecmp
#define TRUE 1
#define FALSE 0
#define BUFLEN_256 256
#define cmsLog_error printf

static UBOOL8 MatchKeyword_WORD(char *src, char *keyword)
{ 
    int i = 0, j = 0;
    char *begin = NULL;
    int len = 0;
    int len2 = 0;

    if (src == NULL || keyword == NULL)
        return FALSE;

    len = strlen(src);
    len2 = strlen(keyword);

    if( len <= 0 || len > BUFLEN_256)
    {
        cmsLog_error("String lengh is invalid.");
        return FALSE;
    }


    for(; i < strlen(src) ; i++)
    {
        if(src[i] != ' ')
        {
            j = 0;
            begin = &src[i];
            while(' ' != src[i] && '\0' != src[i])
            {
                i++;
                j++;
            }
            if ( j == len2 && cmsUtl_strncasecmp(keyword, begin, len2) == 0)
            {
                return TRUE;
            }
        }

    }

    return FALSE;

}

static void cmsUtl_strToLower(char *string)
{
   char *ptr = string;
   for (ptr = string; *ptr; ptr++)
   {
       *ptr = tolower(*ptr);
   }
}


static UBOOL8 MatchKeyword_STRING(char *src, char *keyword)
{
    char *s = NULL;
    char *k = NULL;
    UBOOL8 ret = FALSE;


    if(src == NULL || keyword == NULL)
        return FALSE;

    s = strdup(src);

    if (s == NULL)
        return FALSE;

    k = strdup(keyword);

    if (k == NULL)
        return FALSE;

    cmsUtl_strToLower(s);
    cmsUtl_strToLower(k);

    if (strstr(s, k) != NULL)
        ret = TRUE;
    else
        ret = FALSE;

    free(s);
    free(k);

    return ret;
}

/*****************************************************************************/
/*                            Test function end                              */
/*****************************************************************************/

/*****************************************************************************/
/*                            Test cases begin                               */
/*****************************************************************************/

static void testSuccess1(void);
static void testSuccess2(void);
static void testSuccess3(void);

static void testFailure1(void);
static void testFailure2(void);
static void testFailure3(void);

static void testFunction1(void);
static void testFunction2(void);
static void testFunction3(void);


static void testSuccess1(void){}
static void testSuccess2(void){}
static void testSuccess3(void){}

static void testFailure1(void)
{
    char *str1_null = NULL;
    char *str2_null = NULL;
    char *const_str1 = "Test1";
    char *const_str2 = "Test2";
    char str1[] = "Test1";
    char str2[] = "Test2";


    MatchKeyword_WORD(NULL, NULL);
    CU_ASSERT(1);
    MatchKeyword_WORD(str1_null, NULL);
    CU_ASSERT(2);
    MatchKeyword_WORD(NULL, str1_null);
    CU_ASSERT(3);
    MatchKeyword_WORD(str1_null, str2_null);
    CU_ASSERT(4);

    MatchKeyword_WORD(const_str1, const_str2);
    CU_ASSERT(5);
    MatchKeyword_WORD(str1, str2);
    CU_ASSERT(6);

}
static void testFailure2(void)
{
    char *str1_null = NULL;
    char *str2_null = NULL;
    char *const_str1 = "Test1";
    char *const_str2 = "Test2";
    char str1[] = "Test1";
    char str2[] = "Test2";


    MatchKeyword_STRING(NULL, NULL);
    CU_ASSERT(1);
    MatchKeyword_STRING(str1_null, NULL);
    CU_ASSERT(2);
    MatchKeyword_STRING(NULL, str1_null);
    CU_ASSERT(3);
    MatchKeyword_STRING(str1_null, str2_null);
    CU_ASSERT(4);

    MatchKeyword_STRING(const_str1, const_str2);
    CU_ASSERT(5);
    MatchKeyword_STRING(str1, str2);
    CU_ASSERT(6);

}
static void testFailure3(void){}

static void testFunction1(void)
{
    UBOOL8 ret = FALSE;

    ret = MatchKeyword_WORD("my iphone", "iphone");
    CU_ASSERT_TRUE(ret);

    ret = MatchKeyword_WORD("my Iphone", "iphone");
    CU_ASSERT_TRUE(ret);

    ret = MatchKeyword_WORD("my iphone", "Iphone");
    CU_ASSERT_TRUE(ret);

    ret = MatchKeyword_WORD("myiphone", "iphone");
    CU_ASSERT_FALSE(ret);

    ret = MatchKeyword_WORD("my phone", "iphone");
    CU_ASSERT_FALSE(ret);

    ret = MatchKeyword_WORD("my i phone", "iphone");
    CU_ASSERT_FALSE(ret);

    ret = MatchKeyword_WORD("my iphone", "iphone ");
    CU_ASSERT_FALSE(ret);

    ret = MatchKeyword_WORD("my iphone", " iphone");
    CU_ASSERT_FALSE(ret);

    ret = MatchKeyword_WORD("my x-box", "x-box");
    CU_ASSERT_TRUE(ret);

    ret = MatchKeyword_WORD("my x box", "x-box");
    CU_ASSERT_FALSE(ret);

    ret = MatchKeyword_WORD("my TV", "TV");
    CU_ASSERT_TRUE(ret);

    ret = MatchKeyword_WORD("my sTV", "TV");
    CU_ASSERT_FALSE(ret);

    ret = MatchKeyword_WORD("my TVs", "TV");
    CU_ASSERT_FALSE(ret);

    ret = MatchKeyword_WORD("my TVs", "TV");
    CU_ASSERT_FALSE(ret);

}
static void testFunction2(void)
{
    UBOOL8 ret = FALSE;

    ret = MatchKeyword_STRING("my iphone", "iphone");
    CU_ASSERT_TRUE(ret);

    ret = MatchKeyword_STRING("my Iphone", "iphone");
    CU_ASSERT_TRUE(ret);

    ret = MatchKeyword_STRING("my iphone", "Iphone");
    CU_ASSERT_TRUE(ret);

    ret = MatchKeyword_STRING("myiphone", "iphone");
    CU_ASSERT_TRUE(ret);

    ret = MatchKeyword_STRING("my phone", "iphone");
    CU_ASSERT_FALSE(ret);

    ret = MatchKeyword_STRING("my i phone", "iphone");
    CU_ASSERT_FALSE(ret);

    ret = MatchKeyword_STRING("my iphone", "iphone ");
    CU_ASSERT_FALSE(ret);

    ret = MatchKeyword_STRING("my iphone", " iphone");
    CU_ASSERT_TRUE(ret);

    ret = MatchKeyword_STRING("my x-box", "x-box");
    CU_ASSERT_TRUE(ret);

    ret = MatchKeyword_STRING("my x box", "x-box");
    CU_ASSERT_FALSE(ret);

    ret = MatchKeyword_STRING("my TV", "TV");
    CU_ASSERT_TRUE(ret);

    ret = MatchKeyword_STRING("my sTV", "TV");
    CU_ASSERT_TRUE(ret);

    ret = MatchKeyword_STRING("my TVs", "TV");
    CU_ASSERT_TRUE(ret);

    ret = MatchKeyword_STRING("my TVs", "TV");
    CU_ASSERT_TRUE(ret);

}
static void testFunction3(void){}


static CU_TestInfo tests_init[] = {
  { "testSuccess1", testSuccess1 },
  { "testSuccess2", testSuccess2 },
  { "testSuccess3", testSuccess3 },
  CU_TEST_INFO_NULL,
};

static CU_TestInfo tests_failure[] = {
  { "testFailure1", testFailure1 },
  { "testFailure2", testFailure2 },
  { "testFailure3", testFailure3 },
  CU_TEST_INFO_NULL,
};

static CU_TestInfo tests_function[] = {
  { "testFunction1", testFunction1},
  { "testFunction2", testFunction2},
  { "testFunction3", testFunction3},
  CU_TEST_INFO_NULL,
};

CU_SuiteInfo PREM_8497_suites[] = {
  { "suite_init",          NULL, NULL, tests_init},
  { "suite_failure",       NULL, NULL, tests_failure },
  { "suite_function",      NULL, NULL, tests_function},
  CU_SUITE_INFO_NULL,
};

/*****************************************************************************/
/*                             Test cases end                                */
/*****************************************************************************/
