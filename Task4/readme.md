The assignment for Task 4 was to find the averages for each quiz by creating a director which forks managers for each chapter who in turn fork workers to calculate the averages for each quiz in their own chapter.

The approach taken in this implementation was to use nested for loops to execute the forking at each level. The files, both the input scores.csv and the output averages.txt, are opened in the director (the top parent) and closed in each of the workers. The assumption here is that the file descriptors are included in each of the forks. The variables curr_chapter and the curr_homework are iterated in each respective for loop. Each worker will have a particular pair of these values that details which quiz average they are responsible for calculating and what offset to use when using the lseek syscall to grab each score for that quiz from the file. The average is then written for the assignment by the worker into the output file. This output, as well as the standard output, show the asynchronous nature of this execution.

The data is generated using the C program generate_scores.c (compiled by the makefile into generate_scores). The program writes an appropriate number of random numbers in the format specified in the assignment based on its inputs. These numbers are written using two digits to allow the file to have a known structure and have an easier time seeking through the file using the lseek syscall.

Both files have inputs num_students, num_chapters, and num_hw_per_chapter as parameters (with the generate_scores.c having an additional max_score parameter), however, are written to include the default values stated in the assignment should they not receive the expected number of arguments.