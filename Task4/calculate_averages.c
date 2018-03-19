#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
  // Arguements:
  // {num_students, num_chapters, num_homeworks_per_chapter}
  // Default values in assignment: 10, 5, 2
  int num_students = (argc == 4) ? atoi(argv[1]) : 10; // num_students
  int num_chapters = (argc == 4) ? atoi(argv[2]) : 5; // num_chapters
  int num_hw_per_chapter = (argc == 4) ? atoi(argv[3]) : 2; // num_hw_per_chapter

  // Input file containing the scores as formatted in the assignment
  // Each score is written using two characters for easy seeking
  int input_file = open("scores.csv", O_RDONLY);
  char input_from_file[2];
  int file_length = lseek(input_file, 0, SEEK_END);
  off_t offset_to_start = lseek(input_file, 0, SEEK_SET);
  lseek(input_file, offset_to_start, SEEK_SET);

  // Output file and variables to prepare output
  // The char[] and output length are left empty to be filled by worker
  int output_file = open("averages.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
  char output_to_file[40]; // Output buffer for results
  int output_length = 0; // Length of content of output buffer for write

  // Variables for the children
  int curr_chapter = 0; // Chapter of manager/worker
  int curr_homework = 0; // Homework number for worker
  int curr_count = 0; // Count of number of scores averaged (for running average)
  float curr_average = 0; // Running average of the scores
  int curr_position = 0; // Worker's position in the file

  printf("- Director starting assignment of work!\n");

  for(int i = 0; i < num_chapters; i++){
    // Fork a manager for each chapter
    if (fork()) {
      curr_chapter = i;
      printf("-- Manager Chapter %d starting assignment of work\n", curr_chapter);

      for(int j = 0; j < num_hw_per_chapter; j++){
        // Fork a worker for each homework in the chapter
        if (fork()) {

          // Assign variables needed for the function of the worker
          curr_homework = j;
          curr_position = (curr_chapter * num_hw_per_chapter * 3) + (curr_homework * 3);

          // Print to terminal to signal start of this worker's work
          printf("--- Worker Chapter %d Homework %d starting work\n", curr_chapter + 1, curr_homework + 1);

          // Calculating the running average of the scores
          // Continue doing so as long as the curr_position is in the file
          lseek(input_file, curr_position, SEEK_SET);
          while (curr_position < file_length){
              read(input_file, input_from_file, 2);
              // printf("Worker Chapter %d Homework %d score %s\n", curr_chapter + 1, curr_homework + 1, input_from_file);
              int prev_count = curr_count;
              curr_count++;
              curr_average = (((prev_count * curr_average) + atoi(input_from_file)) / curr_count);
              curr_position += ((num_chapters * num_hw_per_chapter * 3) + 1);
              lseek(input_file, curr_position, SEEK_SET);
          }

          // Formatting output into a char[] and writing it to file
          output_length += sprintf(output_to_file, "Chapter %d Homework %d: Average: %.3f\n", curr_chapter + 1, curr_homework + 1, curr_average);
          write(output_file, output_to_file, output_length);

          // Print to terminal to signal start of this worker's work
          printf("--- Worker Chapter %d Homework %d finished work\n", curr_chapter + 1, curr_homework + 1);

          close(input_file);
          close(output_file);
          return 0;
        }
      }

      printf("-- Manager Chapter %d finished assigning work\n", curr_chapter);

      return 0;
    }
  }

  printf("- Director finished assigning work!\n");

  return 0;
}
