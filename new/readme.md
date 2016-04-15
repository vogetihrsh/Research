# RD based CNV detection tool

## Parameters 
There are several paramters both optional and mandatory. The parameter values can be passed through command line as well as config file. 

| CLI FLAG | CONFIG FILE NAME | DESCRIPTION | OPTIONAL/REQUIRED|
| --- | --- | --- | --- |
| -i | input_file | Input file name | required |
| -o | output | Output file prefix | required |
| -z | window_file | A bed file containinginformation about windows chromosome name followed by start and stop. The length of each window should be the same for all entries. This length is taken as the bin/window_size | required |
| -m | mappability_file | Mappability values of the corresponding bins in the window file | required | 
| -c | NA | Configuration file that will be used for paramters. It is important to note that values from config file will overwrite those given through CLI. | optional |
| -p | no_of_procs | Number of segmentation processes that are executed in paralell. The work load is evenly distributed among the processes. Its default value is 32, which is recommended. Segmentation takes time of O(n^2). | optional |
| -u | upper_threshold | This paramater is used to the upper threshold. This factor is multiplied to the average RD value to obtain upper threshold. Default is 1.45 | optional |
| -u | lower_threshold | This paramater is used to the lower threshold. This factor is multiplied to the average RD to obtain lower threshold. Default is 0.55. | optional |



