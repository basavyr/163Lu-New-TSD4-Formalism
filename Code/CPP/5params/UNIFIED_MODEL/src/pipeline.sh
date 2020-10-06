g++ -std=c++11 execution_pipeline1.cc -o exe1.out  
g++ -std=c++11 execution_pipeline2.cc -o exe2.out  
g++ -std=c++11 execution_pipeline3.cc -o exe3.out  
g++ -std=c++11 execution_pipeline4.cc -o exe4.out
nohup ./exe1.out
nohup ./exe2.out
nohup ./exe3.out
nohup ./exe4.out