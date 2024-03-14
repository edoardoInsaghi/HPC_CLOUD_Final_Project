## Exercise 1: modeling the latency of mpi collective communication algorithms

This is the README file for the first exercise of the HPC course @ UniTs. The exercise asked to use the osu benchmark to observe how the latency of the communication varies with the number of processes involved in the communication, together with other possible covariates (size of the data and allocation of the computational resources). 

In order to complete the assignment, the version 7.3 of the osu-micro-benchmarks was downloaded and compiled following the instruction found on the Github repository of the course. After playing around with the benchmarks until I felt familiar enough with the library, I wrote a number of bash scripts to run the executables and extract the data through the use of some regular expressions. These scripts provide a csv file which I loaded into Rstudio to produce the plots and build the linear models. 

I opted to use the gnu distribution of mpi, which can be easily loaded on ORFEO with the following command 

```module load openMPI/4.1.5/gnu/12.2.1```. 

The repository also includes the Rmd file with the code for the statistical analysis of the results as well as the plots of the data. 

What follows is the overall structure of the project.

```
.
├── HPC_EX_1.Rmd
├── INSAGHI_report.pdf
├── MSGSIZE_DATA
│   ├── bcast_scripts
│   │   ├── get_data_binomial.sh
│   │   ├── get_data_linear.sh
│   │   └── get_data_pipeline.sh
│   ├── data_bcast_binomial.csv
│   ├── data_bcast_linear.csv
│   ├── data_bcast_pipeline.csv
│   ├── data_reduce_binomial.csv
│   ├── data_reduce_linear.csv
│   ├── data_reduce_pipeline.csv
│   └── reduce_scripts
│       ├── get_data_binomial.sh
│       ├── get_data_linear.sh
│       └── get_data_pipeline.sh
├── NPROC_DATA
│   ├── bcast_scripts
│   │   ├── get_data_binomial.sh
│   │   ├── get_data_linear.sh
│   │   └── get_data_pipeline.sh
│   ├── data_bcast_binomial.csv
│   ├── data_bcast_linear.csv
│   ├── data_bcast_pipeline.csv
│   ├── data_reduce_binomial.csv
│   ├── data_reduce_linear.csv
│   ├── data_reduce_pipeline.csv
│   └── reduce_scripts
│       ├── get_data_binomial.sh
│       ├── get_data_linear.sh
│       └── get_data_pipeline.sh
├── README.md
└── plots
    ├── Broadcast_Binomial_Node.png
    ├── Broadcast_Binomial_Socket.png
    ├── Broadcast_Linear_Node.png
    ├── Broadcast_Linear_Socket.png
    ├── Broadcast_Pipeline_Node.png
    ├── Broadcast_Pipeline_Socket.png
    ├── Reduce_Binomial_Node.png
    ├── Reduce_Binomial_Socket.png
    ├── Reduce_Linear_Node.png
    ├── Reduce_Linear_Socket.png
    ├── Reduce_Pipeline_Node.png
    ├── Reduce_Pipeline_Socket.png
    ├── bcast_binomial.pdf
    ├── bcast_linear.pdf
    ├── bcast_pipeline.pdf
    ├── bcast_plot.pdf
    ├── reduce_binomial.pdf
    ├── reduce_linear.pdf
    ├── reduce_pipeline.pdf
    └── reduce_plot.pdf
```

This is quite messy but I decided to try to model a number of different aspects that could be interesting in predicting the latency of the communications and this resulted in a significant amount of data and plots. The ```/NPROC_DATA``` folder contains the data and the scripts relative to the data in which the number of processors varies while the size of the data stays small and fixed, while the ```/MSGSIZE_DATA``` contains the same kind of files, except that this time the size of the data varies with the number of processes. The ```/plots``` folder of course contains the graphical results of the analysis, some of which have been left out from the report for the sake of space.

The details on how the data is collected and the thought process behind my choices are included in the final report. Hopefully everything is fine, but in any case I leave here my personal e-mail should any suggestion, doubt or correction come to mind to the reader. [edoardo.insaghi@gmail.com]



