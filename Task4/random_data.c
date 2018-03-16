// This script is used to create the random quiz results that are used
// for the remainder of this assignment. An array of numbers from zero
// to arg4 (max_score) with arg1 * arg2 * arg3 (num_students *
// num_chapters * num_homeworks_per_chapter) is written to a file.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
  // Arguements:
  // {num_students, num_chapters, num_homeworks_per_chapter, max_score}
  // Default values in assignment: 10, 5, 2, 100
  int arg1 = (argc == 5) ? atoi(argv[1]) : 10; // num_students
  int arg2 = (argc == 5) ? atoi(argv[2]) : 5; // num_chapters
  int arg3 = (argc == 5) ? atoi(argv[3]) : 2; // num_homeworks_per_chapter
  int arg4 = (argc == 5) ? atoi(argv[4]) : 100; // max_score

  char* data_file_path = "scores.csv";

  int num_scores = arg1 * arg2 * arg3;
  int *data = (int*) malloc(num_scores * sizeof(int));
  for (int i = 0; i < num_scores; i++){
    data[i] = rand() % arg4;
  }

  int data_file = open(data_file_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);

  int num_cols = arg2 * arg3;
  char temp[arg1 * num_cols * 3];
  int size = 0;
  for (int i = 0; i < arg1; i++){
    for (int j = 0; j < num_cols; j++){
      printf("%02d,", data[j + (i * num_cols)]);
      size += sprintf(temp+size, "%02d,", data[j + (i * num_cols)]);
    }
    printf("\n");
    size += sprintf(temp+size, "\n");
  }

  write(data_file, temp, size);

  close(data_file);
  free(data);

  return 0;
}
