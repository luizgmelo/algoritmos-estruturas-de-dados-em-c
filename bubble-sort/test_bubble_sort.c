#include <CUnit/Basic.h>
#include "bubble_sort.c"

void bubble_test() {
  int actual[Max] = {5, 3, 2, 1, 4};
  int expected[Max] = {1, 2, 3, 4, 5};
  bubble_sort(actual);
  for (int i = 0; i < Max; i++) {
    CU_ASSERT_EQUAL(actual[i], expected[i]);
  }
}

int main() {
  // Initialize CUnit test registry
  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  CU_pSuite pSuite = NULL;

  // add a suite to registry
  pSuite = CU_add_suite("bubble_test_suite", 0, 0);

  // Always check if was successful
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Add the test to the suite
  if (NULL == CU_add_test(pSuite, "bubble_test", bubble_test)) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  
  // Sets the basic run mode, CU_BRM_VERBOSE will show maximum output of run details
  CU_basic_set_mode(CU_BRM_VERBOSE);
  
  // Run the tests and show the run summary
  CU_basic_run_tests();
  return CU_get_error();
}

