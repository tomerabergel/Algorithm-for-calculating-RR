# Algorithm for calculating RR (convertion from ECG values)
A smart and efficient general algorithm for calculating RR
According to ECG values

Input: 
The algorithm receives as a file input containing a list of ECG values (one below the other).


Output: 
The algorithm calculates and delivers as a file output containing a list of RR values according to the ECG values input.
In order to calculate the RR values, we need to differentiate between the different ECG signal waves ("PQRST complex" waves) and identify the R waves.
Given the ECG values of ECG measurement, the algorithm identify the R waves and after finding the maximum values for the R waves, it calculates the distances (the "interval RR time") between each of two adjacent R waves, and we find the different RR values for the ECG measurement.

