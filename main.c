#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "rs232.h"
#include "uart.h"

int main(int argc, char const *argv[])
{
  int n; //index
  pthread_t t; // thread t 
  n = com_init(115200);
  t = com_read(n);
  com_write(n);
  com_close(n, t);

  return 0;
}