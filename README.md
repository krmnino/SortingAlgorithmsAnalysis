# CS240A Group Project
### Requirements
The aim of this project is to use multiple sorting algorithms to test their performance using datasets of different sizes. Datasets are generated using a script and stored in a text file, one data point per line. We will evaluate the number of comparisons, swap, and execution time between algorithms when sorting datasets. An application for this project is universities attempting to determine class rankings and other statistics used to differentiate students. Our program clearly shows which sorting algorithm is best for unviresities of different sizes.
- C++ 17
- Python3
  - matplotlib & numpy

## Results:
 ![](/docs/Shell_sort_terminal.png).         ![](/docs/Quick_sort_terminal.png)
 ![](/docs/shell_sort_time_plot.png).        ![](/docs/quick_sort_time_plot.png)
 ![](/docs/shell_sort_swaps_comps_plot.png). ![](/docs/quick_sort_swaps_comps_plot.png)

## Results explanation:
  [Insert Explanation]
## How to Execute Program
- step 1: make
- step 2: in command line type ./data-sorting
- step 3: enter commands as desired
- Possible Commands (ALL COMMANDS MUST END WITH ";"):
  - generate - Generates dataset within a given range with random values
    - run - Test all algorithms using generated datasets
  - show_res - Display performance resuls of a specific algorithm
    - Usage: show_res [SORT_RESULTS_FLAG];
  - save_res - Save performance resuls of a specific algorithm given a directory path
    - Usage: save_res [SORT_RESULTS_FLAG] [FULL_DIRECTORY_PATH];
  - save_all_res - Save performance resuls of all algorithm given a directory path
    - Usage: save_res [FULL_DIRECTORY_PATH];
  - delete_res - Deletes ALL performance results
    - Usage: delete_res;
  - set_pathSet - directory path where the program will read/write datasets
    - Usage: set_path [FULL_DIRECTORY_PATH];
  - show_path - Show directory path where the program will read/write datasets
    - Usage: show_path;
  - help - Display program menu with command definitions
    - Usage: help;
  - exit - Exit the program
    - Usage: exit;

## Participants
- Ethan Breban 
- Korhan Citlak 
- Kurt Manrique-Niño
