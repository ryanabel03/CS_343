#include <stdio.h>


int main() {
  int bobAge;
  int aliceAge;
  printf("Enter Bob's age: ");
  scanf("%d", &bobAge);
  printf("Enter Alice's age: ");
  scanf("%d", &aliceAge);

  float average = (bobAge + aliceAge) / 2.0;

  printf("The average age of Bob and Alice is %.1f\n", average);

  return 0;
}
