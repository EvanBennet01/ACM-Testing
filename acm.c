#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// decide what type ACM to use, look in the handout for pseudo-code

char slots[3][22]; // 3 slots each 22 chars long
const int LUT[3][3] = { { 1, 2 , 1}, { 2, 0 , 0}, { 1, 0 , 1}};
int w= 0;	// write frame
int r= 1;	// read frame
int l= 2; 	// last frame
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

void
reader_thread ()
{
  while(1)  // reader loop; includes a delay to reduce the output data rate
    {
		pthread_mutex_lock(&mutex);
		if(l != r){
		  r = l;
		  pthread_mutex_unlock(&mutex);
		  printf ("%s", slots[r]); // access slot; slots[i] points to slots[i][0]
		  fflush(stdout);
		  usleep(440000);    				// 50 cps
		  } else {
		  pthread_mutex_unlock(&mutex);
	  }
    }
}

char input() // getchar()
{
  char c = getchar();		// get char from inputstream
  if(c==EOF) exit(0); 		// exit process if input ends
  return c;
}

int
main ()
{
	pthread_t readerTh;
	pthread_create(&readerTh, NULL, (void*) &reader_thread, NULL);	// create reader thread

  while (1)  // writer loop
	{
		int j = 0;	// writes into slot j
		while ((slots[w][j++] = input()) != '*'); // computation inside the condition
		slots[w][j] = 0;
		pthread_mutex_lock(&mutex);
		l = w;						// update last write slot
		w = LUT[r][l];				// update written slot
		pthread_mutex_unlock(&mutex);
    }

  return 0;
}
