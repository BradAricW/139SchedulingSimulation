//Brad Waechter CSC 139 A2
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char fileName[8];
	char schedType[4];
	int quantum, interval = 0, totalProcessCount = 0, currentProcessIteration = 0, arrive = 0, system_time = 0;
	FILE *fp;
	int pid[20], arrival_time[20], burst_time[20];
	int pidTest, arrivalTest, burstTest;
	int queue[20];
	int cpu = 0, wait = 0, response = 0, turnaround = 0;
	int doneCount = 0, timeCheck = 0, populate = 0, best = 100, bestCount = 0, holdValue = 0;
	int responseCount[20];
	int intervalCount[20];
	int totalBurst[20];
	int intervalCheck = 0, queueTest = 0, currentIteration2 = 0;
	
	//check arguments and set values accordingly
	int test = 0;
	if (argc < 3 || argc > 4)
	{
		perror("Invalid number of arguments.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		while (test < 8)
		{
			fileName[test] = argv[1][test];
			test++;
		}
		test = 0;
		while (test <4)
		{
			schedType[test] = argv[2][test];
			test++;
		}	
		if (argc > 3)
		{
			quantum = atoi(argv[3]);
		}
	}
	
	//open the file
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	
	//read the file
	while (fscanf(fp, "%d %d %d", &pidTest, &arrivalTest, &burstTest) == 3)
	{
		pid[totalProcessCount] = pidTest;
		arrival_time[totalProcessCount] = arrivalTest;
		burst_time[totalProcessCount] = burstTest;
		totalProcessCount++;
	}
	
	printf("\nScheduling algorithm: %c%c%c%c\n", schedType[0], schedType[1], schedType[2], schedType[3]);
	printf("Total %i tasks are read from \"%s\". Press 'enter' to start\n", totalProcessCount, fileName);
	printf("===================================================================");
	
	if(getchar() == 10)
	{
		//First Come First Serve
		if (schedType[0] == 'F' && schedType[1] == 'C' && schedType[2] == 'F' && schedType[3] == 'S')
		{
			while (arrive < 20)
				{	
				while (currentProcessIteration < totalProcessCount)
				{
					if (arrival_time[currentProcessIteration] <= system_time && burst_time[currentProcessIteration] != 0)
					{
						response += (system_time - arrival_time[currentProcessIteration]);
						wait += (system_time - arrival_time[currentProcessIteration]);
						//printf("%d \n", wait);
						//printf("%d \n", response);
						while (burst_time[currentProcessIteration] != 0)
						{
							printf("<system time    %i> process    %i is running\n", system_time, pid[currentProcessIteration]);
							system_time++;
							cpu+=100;
							burst_time[currentProcessIteration]--;
						}
						doneCount++;
						printf("<system time    %i> process    %i is finished.......\n", system_time, pid[currentProcessIteration]);
						turnaround += (system_time - arrival_time[currentProcessIteration]);
						timeCheck++;
						//printf("%d \n", turnaround);
					}
					currentProcessIteration++;
				}
				if (doneCount == totalProcessCount)
				{
					arrive = 20;
					break;
				}
				if(timeCheck == 0)
				{
					system_time++;
				}
				else
				{
					timeCheck = 0;
				}
				currentProcessIteration = 0;
				arrive++;
			}
			//printf("Test FCFS\n"); //test statement to check path
		}
		
		//Round Robin
		else if (schedType[0] == 'R' && schedType[1] == 'R')
		{
			while (populate < 20)
			{
				responseCount[populate] = 0;
				queue[populate] = 150;
				populate++;
			}
			while (currentProcessIteration < totalProcessCount)
			{
				totalBurst[currentProcessIteration] = burst_time[currentProcessIteration];
				currentProcessIteration++;
			}
			while (arrive < 80)
			{
//				while (currentProcessIteration < totalProcessCount)
//				{
					//populate queue
					while (currentIteration2 < totalProcessCount)
					{
						if(system_time == arrival_time[currentIteration2] && burst_time[currentIteration2] != 0 && arrive == 0)
						{
							while (queueTest < 20)
							{
								if(queue[queueTest] == 150)
								{
									queue[queueTest] = currentIteration2;
									//printf("Initital Queue Placement: %d  Queue Value: %d\n", queueTest, queue[queueTest]);
									break;
								}
								else
								{
									queueTest++;
								}
							}
							queueTest = 0;
						}
						currentIteration2++;
					}
					currentIteration2 = 0;
					
					//run for quantum length
					while (interval < quantum)
					{
						if (burst_time[queue[0]] != 0)
						{
							if (responseCount[queue[0]] == 0)
							{
								response += (system_time - arrival_time[queue[0]]);
								responseCount[queue[0]] = 1;
							}
							printf("<system time    %i> process    %i is running\n", system_time, pid[queue[0]]);
							system_time++;
							cpu+=100;
							//check to see if new process has arrived, add to queue if so
							while (currentIteration2 < totalProcessCount)
							{
								if(system_time == arrival_time[currentIteration2])
								{
									while (queueTest < 20)
									{
										if(queue[queueTest] == 150)
										{
											queue[queueTest] = currentIteration2;
											//printf("Additional Queue Placement: %d  Queue Value: %d\n", queueTest, queue[queueTest]);
											break;
										}
										else
										{
											queueTest++;
										}
									}
									queueTest = 0;
								}
								currentIteration2++;
							}
							currentIteration2 = 0;
							burst_time[queue[0]]--;
							if (burst_time[queue[0]] == 0)
							{
								wait += (system_time - totalBurst[queue[0]] - arrival_time[queue[0]]);
							}
							//printf("Value of Queue[0]: %d\n", queue[0]);
							//printf("Value of Burst: %d\n", burst_time[queue[0]]);
						}
						interval++;
					}
					interval = 0;
										
					//check if process is finished
					if (burst_time[queue[0]] == 0)
					{
						//wait += (system_time - arrival_time[queue[0]] - (quantum + 1));
						doneCount++;
						printf("<system time    %i> process    %i is finished.......\n", system_time, pid[queue[0]]);
						turnaround += (system_time - arrival_time[queue[0]]);
						queue[0] = 150;
					}
					timeCheck++;
					//shift queue
					holdValue = queue[0];
					while (queueTest < 19)
					{
						queue[queueTest] = queue[queueTest + 1];
						//printf("Shifting Queue Placement: %d  Queue Value: %d\n", queueTest, queue[queueTest]);						
						queueTest++;						
					}
					queueTest = 0;
					//place current process at end of queue
					while (queueTest < 20)
					{
						if(queue[queueTest] == 150)
						{
							queue[queueTest] = holdValue;
							break;
						}
						else
						{
							queueTest++;
						}
						//printf("Final Queue Placement: %d  Queue Value: %d\n", queueTest, queue[queueTest]);
					}
					queueTest = 0;
//					currentProcessIteration++;
//				}
//				currentProcessIteration = 0;
				if (queue[0] == 150)
				{
					arrive = 80;
					break;
				}
				if(timeCheck == 0)
				{
					system_time++;
				}
				else
				{
					timeCheck = 0;
				}
				arrive++;
			}
			//printf("Test RR\n"); //test statement to check path
		}
		
		//Shortest Remaining Time First
		else if (schedType[0] == 'S' && schedType[1] == 'R' && schedType[2] == 'T' && schedType[3] == 'F')
		{
			while (populate < 20)
			{
				responseCount[populate] = 0;
				populate++;
			}
			while (arrive < 80)
			{
				while (currentProcessIteration < totalProcessCount)
				{
					if(burst_time[currentProcessIteration] != 0)
					{
						if (arrival_time[currentProcessIteration] <= system_time && burst_time[currentProcessIteration] < best)
						{
							best = burst_time[currentProcessIteration];
							bestCount = currentProcessIteration;
						}
					}
					currentProcessIteration++;
				}
				while (intervalCheck < 20)
				{
					if (intervalCheck == bestCount && intervalCount[intervalCheck] > 0)
					{
						intervalCount[intervalCheck]++;
					}
					else if (intervalCheck == bestCount && intervalCount[intervalCheck] == 0)
					{
						intervalCount[bestCount] = 1;
					}
					else
					{
						intervalCount[intervalCheck] = 0;
					}
					//printf("Best Count: %d Interval Check: %d Interval Count %d\n", bestCount, intervalCheck, intervalCount[intervalCheck]);
					intervalCheck++;
				}
				intervalCheck = 0;
				currentProcessIteration = 0;
				if (responseCount[bestCount] == 0)
				{
					response += (system_time - arrival_time[bestCount]);
					responseCount[bestCount] = 1;
				}
				if (burst_time[bestCount] != 0)
				{
					printf("<system time    %i> process    %i is running\n", system_time, pid[bestCount]);
					system_time++;
					cpu+=100;
					burst_time[bestCount]--;
					best = 100;
				}	
				//printf("Burst Time: %d PID: %d\n", burst_time[bestCount], pid[bestCount]);
				if (burst_time[bestCount] == 0)
				{
					//printf("is it 0?\n");
					wait += (system_time - arrival_time[bestCount] - intervalCount[bestCount]);
					doneCount++;
					printf("<system time    %i> process    %i is finished.......\n", system_time, pid[bestCount]);
					turnaround += (system_time - arrival_time[bestCount]);
				}
				//printf("%d \n", turnaround);
				timeCheck++;
				if (doneCount == totalProcessCount)
				{
					arrive = 80;
					break;
				}
				if(timeCheck == 0)
				{
					system_time++;
				}
				else
				{
					timeCheck = 0;
				}
				arrive++;
			}
			//printf("Test SRTF\n"); //test statement to check path
		}
		
		//invalid input
		else
		{
			perror("Invalid input error. Please use 'FCFS' 'RR' or 'SRTF' as your argument.\n");
			exit(EXIT_FAILURE);
		}
	
	}
	if(system_time != 0 && totalProcessCount != 0)
	{
		cpu = cpu / system_time;
		response = response / totalProcessCount;
		wait = wait / totalProcessCount;
		turnaround = turnaround / totalProcessCount;
	}
	printf("<system time    %i> All processes finished.........................\n", system_time);		
	printf("===================================================================\n");
	printf("Average CPU Usage      : %d \%\n", cpu);
	printf("Average Waiting Time   : %d \n", wait);
	printf("Average Response Time  : %d \n", response);
	printf("Average Turnaround Time: %d \n", turnaround);
	printf("===================================================================\n");
	
	//close the file
	fclose(fp);
}