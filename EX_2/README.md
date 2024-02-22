## Exercise 2: implementing MPI collective communication algorithm and comparing them to openMPI implementations.

This is the README file for the first exercise of the HPC course @ UniTs. The exercise asked to implement a number of algorithms that perform one MPI collective communication, and to compare them against the default implementations provided by openMPI. The collective communication of choice is the broadcast, while the algorithms are the flat tree, chain tree and binary tree algorithms. 

The repository contains the c file that implements the algorithms, compares them with the MPI implementations and ouptuts the result. It is provided a ```build.sh``` build file which must be run as ```./build.sh <numprocs, warmup, iters, size, algo>"```. Numprocs, warmup and iters are self explanatory, size represents the size of the array of integers to be broadcasted (of course multiplying by four returns the total size of the buffer), and algo can accept either the numbers 1, 2, or 5, which represent the flat tree, chain tree and binary tree algorithms respectively, following the values used by openMPI.

The repository also includes the Rmd file with the code for the statistical analysis of the results as well as the plots of the data. 

What follows is the overall structure of the project.

```
.
├── Broadcast.c
├── HPC_EX2.Rmd
├── INSAGHI_report.pdf
├── README.md
├── build.sh
├── data
│   ├── data_binary_tree.csv
│   ├── data_chain_tree.csv
│   ├── data_flat_tree.csv
│   ├── data_size_core.csv
│   └── data_size_node.csv
├── data_attempts
│   ├── data
│   │   ├── binomial_tree_data.csv
│   │   ├── chain_tree_data.csv
│   │   ├── default_data.csv
│   │   └── flat_tree_data.csv
│   ├── data1
│   │   ├── binomial_tree_data.csv
│   │   ├── chain_tree_data.csv
│   │   ├── default_data.csv
│   │   └── flat_tree_data.csv
│   └── data2
│       ├── data_binary_tree.csv
│       ├── data_chain_tree.csv
│       └── data_flat_tree.csv
├── plots
│   ├── binary_tree.pdf
│   ├── chain_tree.pdf
│   ├── flat_tree.pdf
│   ├── strong_scaling_core.pdf
│   └── strong_scaling_node.pdf
└── scripts
    ├── get_data_binomial_tree.sh
    ├── get_data_chain_tree.sh
    ├── get_data_default.sh
    └── get_data_flat_tree.sh
```

The folders ```/data``` and ```/data_attempts``` contain most of the data collected for the exercise, but only the files inside the ```/data``` folder are used for the analysis as the others were unreliable or uninteresting results. More on this in the report. 

The ```/plots``` folder of course contains the graphical results of the analysis and the ```/scripts``` folder contains the files used to actually collect the data.

The details on how the data is collected and the thought process behind my choices are included in the final report. Hopefully everything is fine, but in any case I leave here my personal e-mail should any suggestion, doubt or correction come to mind to the reader. [edoardo.insaghi@gmail.com]

