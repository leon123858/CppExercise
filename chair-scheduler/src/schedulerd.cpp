#define HUMAN_COUNT 25
#define CHAIR_COUNT 5

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t chair[CHAIR_COUNT]; // define chairs

void *tfn(void *arg) {
  int64_t human_id = (int64_t)arg; // human id

  srand(time(NULL));

  // schedule
  while (1) {
    int target_chair = human_id % CHAIR_COUNT;
    pthread_mutex_lock(&chair[target_chair]);
    // if (pthread_mutex_trylock(&chair[human_id]) == 0) {
    printf("chair %d is human %d\n", human_id, target_chair);
    //   pthread_mutex_unlock(&chair[human_id]);
    // }
    pthread_mutex_unlock(&chair[target_chair]);
    sleep(rand() % 5);
  }

  return NULL;
}

int main(void) {
  int i;
  pthread_t human[HUMAN_COUNT]; // 定義人, 由人搶椅子

  for (i = 0; i < CHAIR_COUNT; i++)
    pthread_mutex_init(&chair[i], NULL);

  for (i = 0; i < HUMAN_COUNT; i++)
    pthread_create(&human[i], NULL, tfn, (void *)i);

  for (i = 0; i < HUMAN_COUNT; i++)
    pthread_join(human[i], NULL);

  for (i = 0; i < CHAIR_COUNT; i++)
    pthread_mutex_destroy(&chair[i]);

  return 0;
}
