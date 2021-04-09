#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SIZE 16

void print_stack(void);
void push(void);
void pop(void);
void stack_underflow(void);
void stack_overflow(void);
bool is_empty(void);
bool is_full(void);

int stack[STACK_SIZE];
int sp = 0;
int sp_copy = 0;


int main(void) {
  char ch;

  printf("Stack visualization (available memory address shown at the bottom):\n");
  printf("For simplicity the following rules are enforced:\n");
  printf("1. Only constant values are permitted\n");
  printf("2. Only addition and subtraction operations are permitted\n");
  printf("3. Stack is fixed-length (16).\n\n");

  do {
    printf("0. exit\n");
    printf("1. push\n");
    printf("2. pop\n");
    printf("3. display stack\n");
    printf("Enter option: ");
    scanf(" %c", &ch);
    if (ch == '0') break;
    if (ch == '1') push();
    if (ch == '2') pop();
    if (ch == '3') print_stack();
    
    while ((ch = getchar()) != '\n')
      if (ch == '0') break;

  } while(ch != '0');

  return 0;
}


/*
 * Push new element onto the stack
 */
void push(void) {
  if (is_full()) {
    stack_overflow();
  }

  int x;

  printf("Enter constant number to push: ");
  scanf("%d", &x);

  stack[sp] = x;
  sp++;

  if (sp_copy <= sp) sp_copy++;

  print_stack();
}

/*
 * Pop and return top most element off stack
 */
void pop(void) {
  if (is_empty()) {
    stack_underflow();
  }

  printf("\n");
  printf("Popping %d\n", stack[--sp]);
  printf("Usually this value would be returned and  saved in some other memory segment.\n");
  printf("This value will still 'exist' on the stack until it gets overwritten ");
  printf("by the next value during 'push' operation.\n\n");

  print_stack();
}

/*
 * Check if stack is empty
 */
bool is_empty(void) {
  return sp == 0;
}

/*
 * Check if stack is full
 */
bool is_full(void) {
  return sp == STACK_SIZE;
}

/*
 * Handle stack underflow
 */
void stack_underflow(void) {
  printf("Trying to retrieve item from an empty stack. This would result in ");
  printf("stack underflow.\n");
  printf("Terminating.\n");
  exit(0);
}

/*
 * Handle stack overflow
 */
void stack_overflow(void) {
  printf("Next call would exceed stack bound resulting in stack overflow.\n");
  printf("Terminating\n");
  exit(0);
}

/*
 * Print stack to the shell
 */
void print_stack(void) {
  printf("\n");
  printf("Stack pointer points at -> %d\n", sp);
  for (int i = 0; i < sp_copy + 1; i++) {
    for (int j = 0; j < 22; j++)
      printf(" ");
    for (int j = 0; j < 6; j++) {
      printf("-");
    }
    printf("\n");
    printf("Memory address: %#3x", i);
    for (int j = 0; j < 2; j++)
      printf(" ");
    printf("|");
    for (int j = 0; j < 5; j++) {
      if (j == 2)
        printf("%d", stack[i]);
      else
        printf(" ");
    }
    if (i == sp)
      printf(" <-- stack pointer");
    printf("\n");
  }
  for (int j = 0; j < 22; j++)
    printf(" ");
  for (int j = 0; j < 6; j++) {
    printf("-");
  }
  printf("\n");
}
