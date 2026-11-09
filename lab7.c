#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUT 100

typedef struct {
  int line_number;
  int value;
} Input;

typedef struct {
  int line_number;
  int doubled_value;
} IntermediateInput;

typedef struct {
  int doubled_value;
  int line_numbers[MAX_INPUT];
  int count;
} Output;

void map(Input *input, IntermediateInput *intermediate_input);
void groupByKey(IntermediateInput *input, Output *output, int *result_count);
void reduce(Output *output);

int main() {

  Input input_data[MAX_INPUT];
  int input_size = 0;
  int value;

  printf("Enter values (one per line). Type 'end' to finish:\n");

  while (input_size < MAX_INPUT) {

    char buffer[100];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      break;
    }

    if (sscanf(buffer, "%d", &value) == 1) {

      input_data[input_size].line_number = input_size + 1;
      input_data[input_size].value = value;

      input_size++;
    } else if (strcmp(buffer, "end\n") == 0 || strcmp(buffer, "end") == 0) {
      break;
    } else {
      printf("Invalid input. Try again.\n");
    }
  }

  // Step 1: Map

  IntermediateInput mapped_results[MAX_INPUT] = {0};

  for (int i = 0; i < input_size; i++) {
    map(&input_data[i], &mapped_results[i]);
  }

  // Step 2: Group

  Output output_results[MAX_INPUT] = {0};
  int result_count = 0;

  for (int i = 0; i < input_size; i++) {
    groupByKey(&mapped_results[i], output_results, &result_count);
  }

  // Step 3: Reduce

  for (int i = 0; i < result_count; i++) {
    reduce(&output_results[i]);
  }

  return 0;
}

void map(Input *input, IntermediateInput *intermediate_input) {

  intermediate_input->line_number = input->line_number + 1;
  intermediate_input->doubled_value = input->value * 2;
}

void groupByKey(IntermediateInput *input, Output *output, int *result_count) {

  int found = 0;

  for (int i = 0; i < *result_count; i++) {

    if (output[i].doubled_value == input->doubled_value) {

      output[i].line_numbers[output[i].count] = input->line_number;
      output[i].count++;

      found = 1;
      break;
    }
  }

  if (found == 0) {

    output[*result_count].doubled_value = input->doubled_value;
    output[*result_count].line_numbers[0] = input->line_number;
    output[*result_count].count = 0;

    *result_count = *result_count + 1;
  }
}

void reduce(Output *output) {

  printf("(%d, [", output->doubled_value);

  for (int i = 0; i < output->count; i++) {

    printf("%d", output->line_numbers[i]);

    if (i < output->count) {
      printf(", ");
    }
  }

  printf("])\n");
}
