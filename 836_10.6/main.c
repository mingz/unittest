/*
 *  CUnit - A Unit testing framework library for C.
 *  Copyright (C) 2004  Anil Kumar, Jerry St.Clair
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
#include <unistd.h>
#include <CUnit.h>
#include <CUnit/Basic.h>
#include <assert.h>

#include "suite.h"

static void AddSuites(CU_SuiteInfo *suites);

static void AddTests()
{
    AddSuites(PREM_8497_suites);
}

static void AddSuites(CU_SuiteInfo *suites)
{

  assert(NULL != CU_get_registry());
  assert(!CU_is_test_running());

	/* Register suites. */
	if (CU_register_suites(suites) != CUE_SUCCESS) {
		fprintf(stderr, "suite registration failed - %s\n",
			CU_get_error_msg());
		exit(EXIT_FAILURE);
	}

}


int main(int argc, char* argv[])
{
  CU_BasicRunMode mode = CU_BRM_VERBOSE;
  CU_ErrorAction error_action = CUEA_IGNORE;
  int ch;

  setvbuf(stdout, NULL, _IONBF, 0);

  while ((ch = getopt(argc, argv, "ifAsnvp:")) != -1)
  {
      switch (ch)
      {
          case 'i':
              error_action = CUEA_IGNORE;
              break;
          case 'f':
              error_action = CUEA_FAIL;
              break;
          case 'A':
              error_action = CUEA_ABORT;
              break;
          case 's':
              error_action = CU_BRM_SILENT;
              break;
          case 'n':
              error_action = CU_BRM_NORMAL;
              break;
          case 'v':
              error_action = CU_BRM_VERBOSE;
              break;
          case 'p':
              printf("Running test PREM-%s.", optarg);
              sleep(2);
              break;
          default:
              printf("\nUsage:  BasicTest [options]\n\n"
                      "Options:   -i   ignore framework errors [default].\n"
                      "           -f   fail on framework error.\n"
                      "           -A   abort on framework error.\n\n"
                      "           -s   silent mode - no output to screen.\n"
                      "           -n   normal mode - standard output to screen.\n"
                      "           -v   verbose mode - max output to screen [default].\n\n"
                      "           -p   print certain test suite.\n"
                      "           -h   print this message and exit.\n\n");
      }
  }

  if (CU_initialize_registry()) {
      printf("\nInitialization of Test Registry failed.");
  }
  else {
      AddTests();
      CU_basic_set_mode(mode);
      CU_set_error_action(error_action);
    printf("\nTests completed with return value %d.\n", CU_basic_run_tests());
    CU_cleanup_registry();
  }

  return 0;
}
