/*
o Input: The algorithm receives as a file input containing a list of ECG values (one below the other).
o Output: The algorithm calculates and delivers as a file output containing a list of RR values ​​according to the ECG values ​​input.
In order to calculate the RR values, ​​we need to differentiate between the different ECG signal waves ("PQRST complex" waves) and identify the R waves.
Given the ECG values ​​of ECG measurement, the algorithm identify the R waves and after finding the maximum values ​​for the R waves, it calculates the distances (the "interval RR time") between each of two adjacent R waves, and we find the different RR values ​​for the ECG measurement.
*/

void funcalgoRR1() {

	//average max point of the Ecg sample
	float MaxSamples;

	//number of ECG samples
	const int NumSamples = 30000;

	//The time slots should be selected according to the physiological movment clusters
	//relaxing cluster:70-120 ; EasyWalk cluster:60-110; FastWalk cluster:60-80
	//EasyRun cluster:60-100; FastRun cluster:25-60; 
	const float TimeSlot = 25;

	float Input1, Input2, Input3, Time = 0, Skip = 0, numRR = 0, temp = 0, NumOfNumAvg = 0;
	int IndexFinalMax = 0, IndexMaxV = 0;
	float arrV[NumSamples];//array of Ecg Samples [V]
	float arrT[NumSamples];//array of Time Samples [t]
	float ArrayMaxV[NumSamples];//array of Max Ecg Samples [V]
	float ArrayMaxT[NumSamples];//array of Time Max Ecg Samples [t]
	float arrRR[NumSamples];//array of result calculation RR from Ecg Samples [t]

	ofstream txtout;//output file - contains the algorithm calculation result RR 

	txtout.open("C:\\Users\\Owner\\Desktop\\textforC++\\ResultRR\\ResultStep2\\Eliav\\RESEliavRR.txt");


	ifstream file;//input file - ECG sample ( after multiplication by 1000)

	file.open("C:\\Users\\Owner\\Desktop\\textforC++\\RRStep2\\ECG_Eliav.txt");

	if (!file)
	{
		cout << "error, file did not opened";
		exit(-1);
	}


	//Finding the average max point of the Ecg sample.

	for (int i = 0; i <= NumSamples / 10; i++)
	{
		for (int j = 0; j < NumSamples / 10; j++)
		{
			//Swapping element in if statement
			if (arrV[i] > arrV[i + 1])
			{
				temp = arrV[i];
				arrV[i] = arrV[i + 1];
				arrV[i + 1] = temp;
			}
		}
	}
	while (NumSamples / 10 != 0)
		NumOfNumAvg++;

	for (int i = NumSamples; i < NumSamples - NumOfNumAvg; i++)
		MaxSamples += arrV[i];

	MaxSamples /= NumOfNumAvg;
	MaxSamples -= MaxSamples / NumOfNumAvg;





	while (!file.eof() && Time <= NumSamples)
	{
		file >> Input1;
		if (Input1 > MaxSamples)//check if the Ecg input is greater than the threshold(maximum values)
		{
			arrV[IndexMaxV] = Input1;
			arrT[IndexMaxV] = Time;
			IndexMaxV++;
		}
		Time++;
	}

	file.close();






	for (int i = 0; i < IndexMaxV; i = i + Skip)
	{

		//case 1:the Ecg wave has one maximum
		if (arrT[i] < arrT[i + 1] - TimeSlot)
		{
			Input1 = arrV[i];
			ArrayMaxV[IndexFinalMax] = Input1;
			ArrayMaxT[IndexFinalMax] = arrT[i];
			Skip = 1;
			IndexFinalMax++;
		}

		//case 2:the Ecg wave has two maximum
		else if (arrT[i] < arrT[i + 2] - TimeSlot)
		{
			Input1 = arrV[i];
			Input2 = arrV[i + 1];
			if (Input1 > Input2)
			{
				ArrayMaxV[IndexFinalMax] = Input1;
				ArrayMaxT[IndexFinalMax] = arrT[i];
			}
			else
			{
				ArrayMaxV[IndexFinalMax] = Input2;
				ArrayMaxT[IndexFinalMax] = arrT[i + 1];
			}
			Skip = 2;
			IndexFinalMax++;
		}

		//case 3:the Ecg wave has three maximum
		else if (arrT[i] < arrT[i + 3] - TimeSlot)
		{
			Input1 = arrV[i];
			Input2 = arrV[i + 1];
			Input3 = arrV[i + 2];
			if ((Input1 > Input2) && (Input1 > Input3))
			{
				ArrayMaxV[IndexFinalMax] = Input1;
				ArrayMaxT[IndexFinalMax] = arrT[i];
			}
			if ((Input2 > Input1) && (Input2 > Input3))
			{
				ArrayMaxV[IndexFinalMax] = Input2;
				ArrayMaxT[IndexFinalMax] = arrT[i + 1];
			}
			if ((Input3 > Input1) && (Input3 > Input2))
			{
				ArrayMaxV[IndexFinalMax] = Input3;
				ArrayMaxT[IndexFinalMax] = arrT[i + 2];
			}

			IndexFinalMax++;
			Skip = 3;
		}
		//case 4:the Ecg wave has more than three maximum(usually an Error value)
		else
		{
			int index = i;
			int j = i;
			int max = 0;
			Skip = 1;
			while ((arrV[j] > MaxSamples) && (arrT[j] > arrT[j + 1] - TimeSlot))
			{

				if (arrV[j] > max)
				{
					max = arrV[j];
					index = j;
				}
				j++;
				Skip++;
			}
			Input1 = max;
			ArrayMaxV[IndexFinalMax] = Input1;
			ArrayMaxT[IndexFinalMax] = arrT[index];
			IndexFinalMax++;
		}


	}


	//array of calculation results final RR 
	for (int i = 0; i < IndexFinalMax; i++)
	{
		arrRR[i] = ArrayMaxT[i + 1] - ArrayMaxT[i];
		numRR++;
	}

	//Representation RR per minute
	for (int i = 0; i < numRR; i++)
	{
		arrRR[i] *= 0.01;
	}


	//output to file results of final RR
	for (int i = 0; i < numRR; i++)
	{
		txtout << arrRR[i] << " " << endl;
		//bpm: 60 / arrRR[i]
	}



	txtout.close();

}