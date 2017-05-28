/* assert_true.c
 * Nigel Robbins
 * A helper method which logs success and failure rather than exiting the suite
 */
#include"assert_true.h"
#include<stdio.h>

void assertTrue(int result, char* success, char* failure) {
  if (result) {
    if (success[0] == '\0') {
      printf("Success\n");
    } else {
      printf(success);
    }
  } else {
    printf("TEST FAILURE: ");
    printf(failure);
    printf("\n");
  }
}

