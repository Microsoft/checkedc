// Feature tests of typechecking of uses of Checked C checked scope/function
//
// The following lines are for the LLVM test harness:
//
// RUN: %clang_cc1 -fcheckedc-extension -Wno-unused-value -Wno-pointer-bool-conversion -verify -verify-ignore-unexpected=note %s
//

// Top level scope is a checked scope.
// - By default, global variables are checked type within a checked scope.
// - By default, all functions are checked type within a checked scope.
//   Function parameters & return SHOULD have checked pointer type
//   Function body is also checked scope within checked function
// - By default, all structure/union declarations is checked type
// - To declare function as undeclared, use unchecked function specifier

#include "../../include/stdchecked.h"

// Test for pragma set/clear/set.
#pragma BOUNDS_CHECKED ON
#pragma BOUNDS_CHECKED OFF
#pragma BOUNDS_CHECKED ON

// Test for checked function in top-level checked scope.
// Check if paremeter, return, local variable is checked type
int* checked_func0(ptr<int> p, int *q : itype(ptr<int>), int r[], array_ptr<int> s : count(len), int len) { // expected-error {{return cannot have an unchecked pointer type}} \
                                                                                                            // expected-error {{parameter cannot have an unchecked array type}}
  int a = 5;
  int *upa = &a;  // expected-error {{variable cannot have an unchecked pointer type in a checked scope}}
  int *upb = q;   // expected-error {{variable cannot have an unchecked pointer type in a checked scope}}
  ptr<int> pc = p;
  array_ptr<int> pd = q;
  int e[5][5];    // expected-error {{variable cannot have an unchecked array type}}
  return upa;
}

unchecked int* unchecked_func0(ptr<int> p, int *q : itype(ptr<int>), int r[], array_ptr<int> s : count(len), int len) {
  int a = 5;
  int *upa = &a;
  int *upb = q;
  ptr<int> pc = p;
  array_ptr<int> pd = q;
  int e[5][5];
  return upa;
}


array_ptr<int> checked_func1_checked_body(int *x, int *y) {   // expected-error 2 {{parameter cannot have an unchecked pointer type}}
  int *upa = x; // expected-error {{variable cannot have an unchecked pointer type in a checked scope}}
  int *upb = y; // expected-error {{variable cannot have an unchecked pointer type in a checked scope}}
  return upb;
}

unchecked array_ptr<int> unchecked_func1_checked_body(int *x, int *y) {
#pragma BOUNDS_CHECKED ON
  int *upa = x; // expected-error {{variable cannot have an unchecked pointer type in a checked scope}} \
                // expected-error {{cannot use a parameter with an unchecked type}}
  int *upb = y; // expected-error {{variable cannot have an unchecked pointer type in a checked scope}} \
                // expected-error {{cannot use a parameter with an unchecked type}}
  return upb;
}

unchecked array_ptr<int> unchecked_func1_unchecked_body(int *x, int *y) {
  int *upa = x;
  int *upb = y;
  return upb;
}

array_ptr<int> checked_func1_unchecked_body(int *x, int *y) {  // expected-error 2 {{parameter cannot have an unchecked pointer type}}
#pragma BOUNDS_CHECKED OFF
  int *upa = x;
  int *upb = y;
  return upb;
}


int* checked_func2_checked_parm_checked_ret(int a checked[][5], int b checked[][5]) : itype(ptr<int>) {
}

int* checked_func2_unchecked_parm_checked_ret(int a [][5], int b [][5]) : itype(ptr<int>) { // expected-error 2 {{parameter cannot have an unchecked array type in a checked scope}}
}

int* checked_func2_checked_parm_unchecked_ret(int a checked[][5], int b checked[][5]) {  // expected-error {{return cannot have an unchecked pointer type}}
}

int* checked_func2_unchecked_parm_unchecked_ret(int a [][5], int b [][5]) { // expected-error 2 {{parameter cannot have an unchecked array type in a checked scope}} \
                                                                            // expected-error {{return cannot have an unchecked pointer type}}
}

int* checked_func_check_call(int *a : itype(ptr<int>), int *b : itype(array_ptr<int>)) : itype(array_ptr<int>) {
  int e checked[5][5];
  int f[5][5];                // expected-error {{variable cannot have an unchecked array type in a checked scope}}
  int *upa = checked_func2_checked_parm_checked_ret(e, e);    // expected-error {{variable cannot have an unchecked pointer type in a checked scope}}
  ptr<int> pb = checked_func2_checked_parm_checked_ret(e, e);
  ptr<int> pc = 0;
  pc = checked_func2_unchecked_parm_checked_ret(f, f);
  return upa;
}

int* checked_func_itype(int a[] : itype(int *), char b[] : itype(char *)) : itype(int *) {// expected-error 3 {{type must be a checked type}} \
                                                                                          // expected-error 2 {{parameter cannot have an unchecked array type in a checked scope}} \
                                                                                          // expected-error {{return cannot have an unchecked pointer type}}
}

// Test for checked function with mixed scope in top-level checked scope.
int * checked_func_u(int *p, int *q) unchecked {// expected-error {{return cannot have an unchecked pointer type}} \
                                                // expected-error 2 {{parameter cannot have an unchecked pointer type}}
  int a = 5;
  *p = *q = 0;
  ptr<int> pa = &a;
  int b[5][5];
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      b[i][j] = -1;
    }
  }
  return 0;
}

int * checked_func_u_pragma(int *p, int *q) { // expected-error {{return cannot have an unchecked pointer type}} \
                                              // expected-error 2 {{parameter cannot have an unchecked pointer type}}
#pragma BOUNDS_CHECKED OFF
  int a = 5;
  *p = *q = 0;
  ptr<int> pa = &a;
  int b[5][5];
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      b[i][j] = -1;
    }
  }
  return 0;
}

int * checked_func_uc(int *p, int *q) unchecked { // expected-error {{return cannot have an unchecked pointer type}} \
                                                  // expected-error 2 {{parameter cannot have an unchecked pointer type}}
  int *upa;
  checked {
    int a = 5;
    *p = *q = 0;
    ptr<int> pa = &a;
    int b[5][5];  // expected-error {{variable cannot have an unchecked array type}}
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        b[i][j] = -1;
      }
    }
  }
  return upa;
}

int * checked_func_uc_pragma(int *p, int *q) {// expected-error {{return cannot have an unchecked pointer type}} \
                                              // expected-error 2 {{parameter cannot have an unchecked pointer type}}
#pragma BOUNDS_CHECKED OFF
  int *upa;
#pragma BOUNDS_CHECKED ON
  int a = 5;
  *p = *q = 0;
  ptr<int> pa = &a;
  int b[5][5];  // expected-error {{variable cannot have an unchecked array type}}
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      b[i][j] = -1;
    }
  }
#pragma BOUNDS_CHECKED OFF
  return upa;
}

int * checked_func_uc1(int *p, int *q) unchecked {// expected-error {{return cannot have an unchecked pointer type}} \
                                                  // expected-error 2 {{parameter cannot have an unchecked pointer type}}
  int *upa;
  int a = 5;
  *p = *q = 0;
  ptr<int> pa = &a;
  int b[5][5];
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) checked {
      b[i][j] = -1; // expected-error {{cannot use a variable with an unchecked type}}
    }
  }
  checked {
  return upa; // expected-error {{cannot use a variable with an unchecked type}}
  }
}

int * checked_func_uc1_pragma(int *p, int *q) { // expected-error {{return cannot have an unchecked pointer type}} \
                                                // expected-error 2 {{parameter cannot have an unchecked pointer type}}
#pragma BOUNDS_CHECKED OFF
  int *upa;
  int a = 5;
  *p = *q = 0;
  ptr<int> pa = &a;
  int b[5][5];
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
#pragma BOUNDS_CHECKED ON
      b[i][j] = -1; // expected-error {{cannot use a variable with an unchecked type}}
    }
  }
#pragma BOUNDS_CHECKED ON
  return upa; // expected-error {{cannot use a variable with an unchecked type}}
}

ptr<int> checked_func_u1(int *p, ptr<int> q, array_ptr<int> r, array_ptr<int> s : count(2)) { // expected-error {{parameter cannot have an unchecked pointer type}}
  int a = 5;
  *p = 1;
  *q = 2;
  *r = 3; // expected-error {{expression has no bounds}}
  *s = 4;
  unchecked {
    ptr<int> pa = &a;
    int b checked[5][5];
    for (int i = 0; i < 5; i++) checked {
      for (int j = 0; j < 5; j++) unchecked {
        b[i][j] += *q + *r; // expected-error {{expression has no bounds}}
      }
      b[i][4] += *p + *q + *r + *s;
    }
  }
  return q;
}

ptr<int> checked_func_u1_pragma(int *p, ptr<int> q, array_ptr<int> r, array_ptr<int> s : count(2)) {// expected-error {{parameter cannot have an unchecked pointer type}}
  int a = 5;
  *p = 1;
  *q = 2;
  *r = 3; // expected-error {{expression has no bounds}}
  *s = 4;
#pragma BOUNDS_CHECKED OFF
  ptr<int> pa = &a;
  int b checked[5][5];
  for (int i = 0; i < 5; i++) {
#pragma BOUNDS_CHECKED ON
    for (int j = 0; j < 5; j++) {
#pragma BOUNDS_CHECKED OFF
      b[i][j] += *q + *r; // expected-error {{expression has no bounds}}
    }
    b[i][4] += *p + *q + *r + *s;
  }
#pragma BOUNDS_CHECKED ON
  return q;
}

int * checked_func_uc(void) : itype(array_ptr<int>) unchecked {
  int a = 5;
  int *upa = &a;
  int b[5][5];
  checked {
    int c checked[5][5];
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        b[i][j] += c[i][j];   // expected-error {{cannot use a variable with an unchecked type}}
      }
    }
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) unchecked {
        c[i][j] += b[i][j];
      }
    }
  }
  return upa;
}

int * checked_func_uc_pragma(void) : itype(array_ptr<int>) {
#pragma BOUNDS_CHECKED OFF
  int a = 5;
  int *upa = &a;
  int b[5][5];
#pragma BOUNDS_CHECKED ON
  int c checked[5][5];
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      b[i][j] += c[i][j];   // expected-error {{cannot use a variable with an unchecked type}}
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
#pragma BOUNDS_CHECKED OFF
      c[i][j] += b[i][j];
    }
  }
#pragma BOUNDS_CHECKED OFF
  return upa;
}

int checked_func_ucu1(int *p, int *q, int *r : itype(ptr<int>), int *s : itype(array_ptr<int>)) unchecked { // expected-error 2 {{parameter cannot have an unchecked pointer type}}
  int sum = 0;
  int a = 5;
  int *upa = &a;
  int b[5][5];
  for (int i = 0; i < 5; i++) checked {
    sum += b[i][0] + *upa; // expected-error 2 {{cannot use a variable with an unchecked type}}
    for (int j = 1; j < 5; j++) unchecked {
      sum += b[i][j];
    }
  }
  return sum;
}

int checked_func_ucu1_pragma(int *p, int *q, int *r : itype(ptr<int>), int *s : itype(array_ptr<int>)) { // expected-error 2 {{parameter cannot have an unchecked pointer type}}
#pragma BOUNDS_CHECKED OFF
  int sum = 0;
  int a = 5;
  int *upa = &a;
  int b[5][5];
  for (int i = 0; i < 5; i++) {
#pragma BOUNDS_CHECKED ON
    sum += b[i][0] + *upa; // expected-error 2 {{cannot use a variable with an unchecked type}}
    for (int j = 1; j < 5; j++) {
#pragma BOUNDS_CHECKED OFF
      sum += b[i][j];
    }
  }
  return sum;
}

int checked_func_ucu2(ptr<int> p, int *q) unchecked {  // expected-error {{parameter cannot have an unchecked pointer type}}
  int a = 5;
  int *upa;
  array_ptr<int> pc;
  upa = pc;   // expected-error {{assigning to 'int *' from incompatible type '_Array_ptr<int>'}}
  checked {
    upa = &a; // expected-error {{cannot use a variable with an unchecked type}}
    pc = &a;
    unchecked {
      upa = &a;
      pc = &a;
    }
    upa = &a; // expected-error {{cannot use a variable with an unchecked type}}
    pc = &a;
  }
  ptr<int> pb = p;
  int *upc;
  int *upd;
  return *pb;
}

int checked_func_ucu2_pragma(ptr<int> p, int *q) {// expected-error {{parameter cannot have an unchecked pointer type}}
#pragma BOUNDS_CHECKED OFF
  int a = 5;
  int *upa;
  array_ptr<int> pc;
  upa = pc; // expected-error {{assigning to 'int *' from incompatible type '_Array_ptr<int>'}}
#pragma BOUNDS_CHECKED ON
  upa = &a; // expected-error {{cannot use a variable with an unchecked type}}
  pc = &a;
#pragma BOUNDS_CHECKED OFF
  upa = &a;
  pc = &a;
#pragma BOUNDS_CHECKED ON
  upa = &a; // expected-error {{cannot use a variable with an unchecked type}}
  pc = &a;
#pragma BOUNDS_CHECKED OFF
  ptr<int> pb = p;
  int *upc;
  int *upd;
  return *pb;
}

// Test for unchecked function specifier with top-level scope pragma.
unchecked int * unchecked_func3_unchecked_body(int *p, int q[]) {
  int a = 5;
  *p = *q = 0;
  ptr<int> pa = &a;
  int b[5][5];
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      b[i][j] = -1;
    }
  }
  return 0;
}

unchecked int * unchecked_func3_checked_body(int *p, int q[]) {
#pragma BOUNDS_CHECKED ON
  int a = 5;
  *p = *q = 0;  // expected-error 2 {{cannot use a parameter with an unchecked type}}
  ptr<int> pa = &a;
  int b[5][5];  // expected-error {{variable cannot have an unchecked array type}}
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      b[i][j] = -1;
    }
  }
  return 0;
}

unchecked array_ptr<int> unchecked_func4_unchecked_body(int p[], int q[10], int r[][10]) {
  int *upa;
  int *upb;
  array_ptr<int> pb;
  ptr<int> pc = 0;
  upa = pb;   // expected-error {{assigning to 'int *' from incompatible type '_Array_ptr<int>'}}
  upa = pc;   // expected-error {{assigning to 'int *' from incompatible type '_Ptr<int>'}}
  upb = pb;   // expected-error {{assigning to 'int *' from incompatible type '_Array_ptr<int>'}}
  upb = pc;   // expected-error {{assigning to 'int *' from incompatible type '_Ptr<int>'}}
  return upb; // array_ptr<int> = int *, OK
}

unchecked array_ptr<int> unchecked_func4_checked_body(int p[], int q[10], int r[][10]) {
#pragma BOUNDS_CHECKED ON
  int *upa;   // expected-error {{variable cannot have an unchecked pointer type}}
  int *upb;   // expected-error {{variable cannot have an unchecked pointer type}}
  array_ptr<int> pb;
  ptr<int> pc = 0;
  upa = pb;
  upa = pc;
  upb = pb;
  upb = pc;
  return upb;
}

unchecked int * unchecked_func_cu(int *p, ptr<int> q, array_ptr<int> r, array_ptr<int> s : count(2)) {
#pragma BOUNDS_CHECKED ON
  int a = 5;
  *p = 1; // expected-error {{cannot use a parameter with an unchecked type}}
  *q = 2;
  *r = 3; // expected-error {{expression has no bounds}}
  *s = 4;
#pragma BOUNDS_CHECKED OFF
  ptr<int> pa = &a;
  int b checked[5][5];
  int c[5][5];
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      b[i][j] = *p + *q + *r + *s;  // expected-error {{expression has no bounds}}
    }
  }
  return 0;
}

unchecked int unchecked_func_cu2(int *p, int *q, int *r : itype(ptr<int>), int *s : itype(array_ptr<int>)) {
  int sum = 0;
  int a = 5;
  int *upa = &a;
  int b[5][5];
  for (int i = 0; i < 5; i++) {
#pragma BOUNDS_CHECKED ON
    sum += b[i][0] + *upa; // expected-error 2 {{cannot use a variable with an unchecked type}}
    for (int j = 1; j < 5; j++) {
#pragma BOUNDS_CHECKED OFF
      sum += b[i][j];
    }
  }
  return sum;
}

typedef int unchecked_arr_type[10];
typedef int checked_arr_type[10];

// Test for extern checked function declarations
extern void check_assign(int val, int p[10], int q[], int r checked[10], int s checked[], // expected-error 2 {{parameter cannot have an unchecked array type}}
                         int s2d checked[10][10]) {
}

extern void check_assign_cv(int param[10],  // expected-error {{parameter cannot have an unchecked array type}}
                            int checked_param checked[10],
                            int param_const_ptr[const 10],  // expected-error {{parameter cannot have an unchecked array type}}
                            int checked_param_const_ptr checked[const 10],
                            const int const_param[10],  // expected-error {{parameter cannot have an unchecked array type}}
                            const int const_checked_param checked[10],
                            const int const_param_const_ptr[const 10],  // expected-error {{parameter cannot have an unchecked array type}}
                            const int const_checked_param_const_ptr checked[const 10],
                            volatile int volatile_param[10],  // expected-error {{parameter cannot have an unchecked array type}}
                            volatile int checked_volatile_param checked[10]) {
}

extern void f1(int *p, int y) { // expected-error {{parameter cannot have an unchecked pointer type}}
}

extern void f2(int p[10], int y) {  // expected-error {{parameter cannot have an unchecked array type}}
}

extern void f3(int p checked[10], int y) {
  *p = y;
}

extern void f4(int **p, int y) {  // expected-error {{parameter cannot have an unchecked pointer type}}
}

extern void f5(int(*p)[10], int y) {  // expected-error {{parameter cannot have an unchecked pointer type}}
}

extern void f6(ptr<int[10]> p, int y) { // expected-error {{parameter cannot have an unchecked array type}} \
                                        // ptr<unchecked array> not OK in checked scope
}

extern void f7(array_ptr<int[10]> p, int y) { // expected-error {{parameter cannot have an unchecked array type}} \
                                              // array_ptr<unchecked array> not OK in checked scope
}

extern void f8(int(*p) checked[10], int y) {  // expected-error {{parameter cannot have an unchecked pointer type}}
}

extern void f9(ptr<int checked[10]> p, int y) {
}

extern void f10(array_ptr<int checked[10]> p, int y) {
}

extern void f11(int p[10][10], int y) { // expected-error {{parameter cannot have an unchecked array type}}
}

extern void f12(int p checked[10][10],int y) {
}

extern void f13(_Bool p, int y) {
}

extern void f1_void(void *p, int y) { // expected-error {{parameter cannot have an unchecked pointer type}}
}

extern void f2_void(ptr<void> p, int y) {
}

extern void f3_void(array_ptr<void> p, int y) {
}

extern void f1_const(const int p[10], int y) {  // expected-error {{parameter cannot have an unchecked array type}}
}

extern void f2_const(const int p checked[10], int y) {
}

extern void g1(int y, int *p) { // expected-error {{parameter cannot have an unchecked pointer type}}
}

extern void g2(int y, int p[10]) {  // expected-error {{parameter cannot have an unchecked array type}}
  *p = y;
}

extern void g3(int y, int p checked[10]) {
  *p = y;
}

// Test for global variables in top-level checked scope
int *a1 : itype(ptr<int>) = 0;
int *a2 : itype(array_ptr<int>) = 0;
int **a3 : itype(ptr<ptr<int>>) = 0;
int **a4 : itype(ptr<array_ptr<int>>) = 0;
int **a5 : itype(array_ptr<ptr<int>>) = 0;
int **a6 : itype(array_ptr<array_ptr<int>>) = 0;
int ***a7 : itype(ptr<ptr<ptr<int>>>) = 0;
int a8[10] : itype(int checked[10]);
extern int a9[] : itype(int checked[]);
#pragma BOUNDS_CHECKED OFF
int *a10;
#pragma BOUNDS_CHECKED ON
int **a11;        // expected-error {{variable cannot have an unchecked pointer type}}
#pragma BOUNDS_CHECKED OFF
int ***a12;
#pragma BOUNDS_CHECKED ON
int a13[10];      // expected-error {{variable cannot have an unchecked array type}}
#pragma BOUNDS_CHECKED OFF
extern int a14[];

#pragma BOUNDS_CHECKED ON
int global[10]; // expected-error {{variable cannot have an unchecked array type}}
int checked_global checked[10];
int global_arr1[10];  // expected-error {{variable cannot have an unchecked array type}}

int *h3(void) {   // expected-error {{return cannot have an unchecked pointer type}}
  return global;
}

ptr<int> h4(void) {
  return global;
}

array_ptr<int> h5(void) {
  return global;
}

int *h6(void) { // expected-error {{return cannot have an unchecked pointer type}}
  return checked_global;  // expected-error {{incompatible result type}}
}

ptr<int> h7(void) {
  return checked_global; // ptr<T> = array_ptr<T> OK
}

array_ptr<int> h8(void) {
  return checked_global;
}

int *h9(int arr[10]) {  // expected-error {{return cannot have an unchecked pointer type}} \
                        // expected-error {{parameter cannot have an unchecked array type}}
  return arr;
}

ptr<int> h10(void) {
  return global_arr1;
}

array_ptr<int> h11(int arr checked[10]) {
  return arr;
}

int *h12(int arr checked[10]) {   // expected-error {{return cannot have an unchecked pointer type}}
  return arr;  // expected-error {{incompatible result type}}
}

ptr<int> h13(int arr checked[10]) {
  return arr;  // ptr<T> = array_ptr<T> OK
}

array_ptr<int> h14(int arr checked[10]) {
  return arr;
}

int *h15(int arr checked[]) {   // expected-error {{return cannot have an unchecked pointer type}}
  return arr;  // expected-error {{incompatible result type}}
}

ptr<int> h17(int arr checked[]) {
  return arr;  // ptr<T> = array_ptr<T> OK, expected-error {{expression has no bounds}}
}

array_ptr<int> h18(int arr checked[]) {
  return arr;
}

// h19 is a function that returns a pointer to a 10-element array of integers.
int(*h19(int arr[10][10]))[10]{   // expected-error {{return cannot have an unchecked pointer type}} expected-error {{parameter cannot have an unchecked array type}}
  return arr;
}

int global_arr2[10][10];  // expected-error {{variable cannot have an unchecked array type}}
ptr<int[10]> h20(void) {  // expected-error {{return cannot have an unchecked array type}}
  return global_arr2;
}

array_ptr<int[10]> h21(int arr[10][10]) { // expected-error {{return cannot have an unchecked array type}} \
                                          // expected-error {{parameter cannot have an unchecked array type}}
  return arr;
}

// h22 is a function that returns a pointer to a 10-element array of integers.
int (*h22(int arr checked[10][10]))[10] { // expected-error {{return cannot have an unchecked pointer type}}
  return arr;  // expected-error {{incompatible result type}}
}

ptr<int[10]> h23(int arr checked[10][10]) { // expected-error {{return cannot have an unchecked array type}}
  return arr;  // expected-error {{incompatible result type}}
}

array_ptr<int[10]> h24(int arr checked[10][10]) { // expected-error {{return cannot have an unchecked array type}}
  return arr;  // expected-error {{incompatible result type}}
}

// h25 is a function that returns a pointer to 10-element array of integers.
int (*h25(int arr checked[10][10])) checked[10]{  // expected-error {{return cannot have an unchecked pointer type}}
  return arr;  // expected-error {{incompatible result type}}
}

ptr<int checked[10]> h26(int arr checked[10][10]) {
  return arr;  // ptr<T> = array_ptr<T> OK
}

array_ptr<int checked[10]> h27(int arr checked[10][10]) {
  return arr;
}

// Test for structure members in top-level checked scope
struct S0 {
  float *data1 : itype(ptr<float>);
  float *data2 : itype(array_ptr<float>);
  float **data3 : itype(ptr<ptr<float>>);
  float **data4 : itype(ptr<array_ptr<float>>);
  float **data5 : itype(array_ptr<ptr<float>>);
  float ***data6 : itype(ptr<ptr<ptr<float>>>);
  float data7[4] : itype(float checked[4]);
  float data8[] : itype(float checked[]);   // expected-error {{field has incomplete type}}
  float data9[];  // expected-error {{member cannot have an unchecked array type}}
  float data10[4];// expected-error {{member cannot have an unchecked array type}}
  float *data11;  // expected-error {{member cannot have an unchecked pointer type}}
  float **data12; // expected-error {{member cannot have an unchecked pointer type}}
  float ***data13;// expected-error {{member cannot have an unchecked pointer type}}
  float *data14 : itype(float *); // expected-error {{type must be a checked type}} \
                                  // expected-error {{member cannot have an unchecked pointer type}}

};

typedef struct _S1 {
#pragma BOUNDS_CHECKED ON
  int *a;       // expected-error {{member cannot have an unchecked pointer type}}
#pragma BOUNDS_CHECKED OFF
#pragma BOUNDS_CHECKED ON
  char *b;      // expected-error {{member cannot have an unchecked pointer type}}
  ptr<int> pc;
  array_ptr<int> pd : count(len);
#pragma BOUNDS_CHECKED OFF
#pragma BOUNDS_CHECKED ON
  short e[10];  // expected-error {{member cannot have an unchecked array type}}
  char f[10];   // expected-error {{member cannot have an unchecked array type}}
  int len;
} S1;

typedef struct _S2 {
#pragma BOUNDS_CHECKED OFF
#pragma BOUNDS_CHECKED ON
#pragma BOUNDS_CHECKED OFF
  int *a;
  char *b;
  ptr<int> pc;
  array_ptr<int> pd : count(len);
  short e[10];
  char f[10];
  int len;
} S2;

int checked_func_with_checked_struct(void) {
  struct local_checked_s {
#pragma BOUNDS_CHECKED OFF
#pragma BOUNDS_CHECKED ON
    int *a;       // expected-error {{member cannot have an unchecked pointer type}}
    char *b;      // expected-error {{member cannot have an unchecked pointer type}}
    ptr<int> pc;
    array_ptr<int> pd : count(len);
    short e[10];  // expected-error {{member cannot have an unchecked array type}}
    char f[10];   // expected-error {{member cannot have an unchecked array type}}
    int len;
  } a;
  return 0;
}

int checked_func_with_unchecked_struct(void) {
  struct local_unchecked_s {
#pragma BOUNDS_CHECKED OFF
    int *a;
    char *b;
    ptr<int> pc;
    array_ptr<int> pd : count(len);
    short e[10];
    char f[10];
    int len;
  } a;
  typedef struct _S {
#pragma BOUNDS_CHECKED ON
    int *a; // expected-error {{member cannot have an unchecked pointer type}}
  } S;
  typedef struct _SS {
#pragma BOUNDS_CHECKED OFF
    int *a;
  } *SS;
  S b;
  SS c; // expected-error {{variable cannot have an unchecked pointer type}}
  return 0;
}

#pragma BOUNDS_CHECKED OFF
extern void variadic_func0(int cnt, ...) {
  for (int i = 0; i < cnt; i++) {}
}

extern void variadic_func1(int cnt, ptr<int> p, array_ptr<int> q, ...) {
}

extern void variadic_func2(int cnt, ptr<int> p, ...) {
}

#pragma BOUNDS_CHECKED ON
extern void variadic_func3(int cnt, ...) {  // expected-error {{variable arguments function cannot be made}}
}

extern void variadic_func4(int cnt, ptr<int> p, array_ptr<int> q, ...) {  // expected-error {{variable arguments function cannot be made}}
}

extern void variadic_func5(int cnt, ptr<int> p, ...) {  // expected-error {{variable arguments function cannot be made}}
}


#pragma BOUNDS_CHECKED ON
void checked_func_call_variadic(void) {
  ptr<int> a = 0;
  array_ptr<int> b;
  printf("check function call variadic %d\n", *a);  // expected-error {{cannot use a variable arguments function}} \
                                                    // expected-warning {{implicitly declaring library function}}
#pragma BOUNDS_CHECKED OFF
  printf("check function call variadic %d\n", *a);
#pragma BOUNDS_CHECKED ON
  printf("check function call variadic %d\n", *a);  // expected-error {{cannot use a variable arguments function}}
#pragma BOUNDS_CHECKED ON
  variadic_func0(10);  // expected-error {{cannot use a variable arguments function}}
  variadic_func1(10, a, b);  // expected-error {{cannot use a variable arguments function}}
  variadic_func2(10, a, a, a);  // expected-error {{cannot use a variable arguments function}}
}

#pragma BOUNDS_CHECKED ON
ptr<void(int , ...)> fptr0;                             // expected-error {{variable cannot have variable arguments}}
ptr<void(int , ptr<int>, array_ptr<int> , ...)> fptr1;  // expected-error {{variable cannot have variable arguments}}
void (*fptr2)(int , ...); // expected-error {{variable cannot have an unchecked pointer type}}

#pragma BOUNDS_CHECKED OFF
typedef struct _S3 {
#pragma BOUNDS_CHECKED ON
#pragma BOUNDS_CHECKED OFF
#pragma BOUNDS_CHECKED ON
  int ((*gptr0)(int, ...));                               // expected-error {{member cannot have an unchecked pointer type}}
  ptr<int*(int, ptr<int>, array_ptr<int>, ...)> gptr1;    // expected-error {{member cannot have an unchecked pointer type}}
  ptr<int(int, ptr<int>, ...)> gptr2;                     // expected-error {{member cannot have variable arguments in a checked scope}}
  ptr<int(int, ...)> gptr3;                               // expected-error {{member cannot have variable arguments in a checked scope}}
  ptr<int(int, ptr<int(int, ptr<int(int, ...)>)>)> gptr4; // expected-error {{member cannot have variable arguments in a checked scope}}
} S3;

#pragma BOUNDS_CHECKED ON
void checked_check_variadic(void) {
  ptr<int> a = 0;
  array_ptr<int> b;
  fptr0 = &variadic_func0;  // expected-error {{cannot use a variable arguments function}}
  fptr1 = &variadic_func1;  // expected-error {{cannot use a variable arguments function}}
  fptr2 = &variadic_func2;  // expected-error {{cannot use a variable arguments function}}

  (*fptr0)(5, a, a, b, b, b);
  (*fptr1)(5, a, b, a, a, b);
}

void check_checked_constructed_type_variadic(void) {
#pragma BOUNDS_CHECKED ON
  ptr<int> pa = 0;
  array_ptr<int> apa;

  ptr<void(int,int)> a = 0;
  ptr<int(int,int)> b = 0;
  ptr<int(int, ptr<int>, ...)> c = 0;           // expected-error {{variable cannot have variable arguments}}
  ptr<int(int, ptr<int(int, ...)>)> d = 0;      // expected-error {{variable cannot have variable arguments}}
  ptr<int(int, ptr<int(int,int)>, ...)> e = 0;  // expected-error {{variable cannot have variable arguments}}
  ptr<int(int, ptr<int(int,...)>, ...)> f = 0;  // expected-error {{variable cannot have variable arguments}}
  int (*g)(int, ...);                           // expected-error {{variable cannot have an unchecked}}
  ptr<int*(int, int)> h = 0;                    // expected-error {{variable cannot have an unchecked}}

#pragma BOUNDS_CHECKED OFF
  {
  ptr<int(int,...)> var_b = 0;
  ptr<int(int,ptr<int>,...)> var_c = 0;
  ptr<int(int,ptr<int(int,...)>)> var_d = 0;
  ptr<int(int,ptr<int(int,ptr<int>,...)>, ...)> var_e = 0;
  ptr<int(int,ptr<int(int,ptr<int(int,...)>)>,ptr<int(int,ptr<int(int,ptr<int>,...)>, ...)>,...)> var_f = 0;
  int (*g)(int, ...);
  ptr<int*(int, int)> h = 0;
  (*var_c)(2, pa, pa);
  (*var_d)(3, var_b);
  (*var_e)(4, var_c, var_d);
  (*var_f)(6, var_d, var_e, a, b, g, h);
  (*h)(10,10);
#pragma BOUNDS_CHECKED ON
  (*var_c)(2, pa, pa);  // expected-error {{cannot use a variable having variable arguments}}
  (*var_d)(3, var_b);   // expected-error 2 {{cannot use a variable having variable arguments}}
  (*var_e)(4, var_c, var_d);  // expected-error 3 {{cannot use a variable having variable arguments}}
  (*var_f)(6, var_d, var_e, a, b, g, h);  // expected-error 3 {{cannot use a variable having variable arguments}} \
                                          // expected-error 2 {{cannot use a variable with an unchecked type}}
  }
}
