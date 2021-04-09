#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SIZE 16

void print_stack(void);
void push(void);
void add(void);
void sub(void);
int pop(void);
void stack_underflow(void);
void stack_overflow(void);
bool is_empty(void);
bool is_full(void);

int stack[STACK_SIZE] = {0};
int sp = 0;


int main(void) {
  char ch;

  printf("Stack visualization (available memory address shown at the bottom):\n");
  printf("For simplicity the following rules are enforced:\n");
  printf("1. Only constant values are permitted\n");
  printf("2. User can directly push constants onto the stack: 'push 10' etc.\n");
  printf("3. Only addition and subtraction operations are permitted\n");
  printf("4. Stack is fixed-length (16).\n");
  printf("5. Each memory location in stack was pre-initialized to 0 ");
  printf("for better visibility.\n\n");

  do {
    printf("0. exit\n");
    printf("1. push\n");
    printf("2. pop\n");
    printf("3. add\n");
    printf("4. sub\n");
    printf("5. display stack\n");
    printf("Enter option: ");
    scanf(" %c", &ch);
    if (ch == '0') break;
    if (ch == '1') push();
    if (ch == '2') pop();
    if (ch == '3') add();
    if (ch == '4') sub();
    if (ch == '5') print_stack();
    
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

  print_stack();
}

/*
 * Pop and return top most element off stack
 */
int pop(void) {
  if (is_empty()) {
    stack_underflow();
  }

  --sp;
  printf("\n");
  printf("Popping %d\n", stack[sp]);
  printf("This value will still 'exist' on the stack until it gets overwritten ");
  printf("by the next value during 'push' operation.\n");

  print_stack();

  return stack[sp];
}

/*
 * Pop two top most items; add them together;
 * and save the result on the stack
 */
void add(void) {
  int val_1 = pop();
  int val_2 = pop();

  stack[sp] = val_1 + val_2;
  sp++;
  print_stack();
}

/*
 * Pop two top most items; subtract top most item from
 * second top most;
 * and save the result on the stack
 */
void sub(void) {
  int val_1 = pop();
  int val_2 = pop();

  stack[sp] = val_2 - val_1;
  sp++;
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
  for (int i = 0; i < STACK_SIZE; i++) {
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
  for (int i = 0; i < 50; i++)
    printf("-");
  printf("\n");
}
