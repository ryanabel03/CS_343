#include <stdlib.h>
#include <stdio.h>

// A C implementation of map, that allows maps from ints to ints only.
int* int_map( int(*fn)(int), int* inputs, int size) {
  int* answer = malloc(sizeof(int)*size);
  int i;
  for (i = 0; i < size; i++) {
    answer[i] = fn(inputs[i]);
  }
  return answer;
}

// A more general implementation of map
void* map( void(*fn)(void*, void*), void* inputs, size_t input_num, size_t input_size, size_t output_size) {

  void* answer = malloc(input_num*output_size);
  void* answerp = answer;
  int i;
  for (i = 0; i < input_num; i++) {
    fn(inputs, answerp);
    inputs += input_size;
    answerp += output_size;
  }
  return answer;
}

int print_int(int i) {
  return printf("%5d ", i);
}

void print_double(void* d, void* i) {
  *((int*)i) = printf("%5.1f ", *((double*)d));
}

typedef struct {
  char name[100];
  double gpa;
  int credits;
} Student;


int main(void) {

  int size1 = 8;
  int array1[] = {1, 3, 5, 7, 9, 11, 15, 22};
 
  //
  // Using map_int
  // 
  int f1(int p) {
    return p * 2;
  }
 
  int* output1 = int_map(f1, array1, size1);
  free(int_map(print_int, output1, size1));
  puts("");
  free(output1);

  //
  // using map
  //

  void f2(void* in, void* out) {
    int i = *((int*)in);
    int* out2 = (int*)out;
    *out2 = i*3;
  }

  int* output2 = (int*) map(f2, array1, size1, sizeof(int), sizeof(int));
  free(int_map(print_int, output2, size1));
  puts("");

  void f3(void* in, void* out) {
    int i = *((int*)in);
    double* out2 = (double*)out;
    *out2 = (double)i / 2.0;
  }

  double* output3 = (double*) map(f3, array1, size1, sizeof(int), sizeof(double));
  free(map(print_double, output3, size1, sizeof(double), sizeof(int)));
  puts("");
  free(output3);

  void get_gpas(void* in, void* out) {
    *((double*)out) = ((Student*)in)->gpa;
  }


  int num_students = 3;
  Student students[] = {{"Bob", 3.821, 15}, {"Mary", 3.994, 33}, {"Nikki", 1.092, 13}};

  double* gpas = map(get_gpas,students, num_students, sizeof(Student), sizeof(double));
  free(map(print_double, gpas, num_students, sizeof(double), sizeof(int)));
  puts("");
  free(gpas);

  void get_credits(void* in, void* out) {
    Student* inp = *((Student**)in);
    *((int*)out) = inp->credits;
  }


  Student* student_pointers[] = {&students[0], &students[1], &students[2]};
  int* credits = map(get_credits, student_pointers, num_students, sizeof(Student*), sizeof(int));
  free(int_map(print_int, credits, num_students));
  puts("");
  free(credits);


  return 3;
}
  
