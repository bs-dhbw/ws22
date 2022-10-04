#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <cassert>

constexpr int NR_OF_THREADS{5};

uint64_t counter{0};
std::atomic_uint64_t atomicCounter{0};

void myThread(void) {
  for (int i = 0; i < 1000; i++) {
    counter++;
    atomicCounter++;
  }
}

int main(void) {
  std::cout << "Start..." << std::endl;

  std::vector<std::thread> threads;

  for (int i = 0; i < NR_OF_THREADS; i++) {
    threads.push_back(std::thread(myThread));
  }

  for (auto &th : threads) {
    th.join();
  }

  std::cout << "Counter value " << counter << std::endl;
  std::cout << "Atomic counter value " << atomicCounter << std::endl;
  assert(counter == atomicCounter);


  exit(EXIT_SUCCESS);
}