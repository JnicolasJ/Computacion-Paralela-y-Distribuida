#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

int main(void) {

  int my_rank, comm_sz;
  char my_question[MAX_STRING];

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if (my_rank != 0) {
     /* Create message */
     sprintf(my_question, "Process %d of %d > Does anyone have a toothpick?\n",
           my_rank, comm_sz);
     /* Send message to process 0 */
     MPI_Send(my_question, strlen(my_question)+1, MPI_CHAR, 0, 0,
           MPI_COMM_WORLD);
  } else {
     /* Print my message */
     printf("Process %d of %d > Does anyone have a toothpick? \n", my_rank, comm_sz);
     for (int q = 1; q < comm_sz; q++) {
        /* Receive message from process q */
        MPI_Recv(my_question, MAX_STRING, MPI_CHAR, q,
           0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        /* Print message from process q */
        printf("%s", my_question);
     }
  }
  MPI_Finalize();
  return 0;
}  /* main */
