//Matthew Taylor
//COP4610: Computer Operating Systems, Fall 2019
//CPU Scheduler Programming Assignment

#include "stdafx.h"
#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

//all processes, process goes {CPU burst, I/O time, CPU burst, I/O time, CPU burst, I/O time,........, last CPU burst}
list<int> process1 = { 5, 27, 3, 31, 5, 43, 4, 18, 6, 22, 4, 26, 3, 24, 4, 0, -1 };
list<int> process2 = { 4, 48, 5, 44, 7, 42, 12, 37, 9, 76, 4, 41, 9, 31, 7, 43, 8, 0, -2 };
list<int> process3 = { 8, 33, 12, 41, 18, 65, 14, 21, 4, 61, 15, 18, 14, 26, 5, 31, 6, 0, -3 };
list<int> process4 = { 3, 35, 4, 41, 5, 45, 3, 51, 4, 61, 5, 54, 6, 82, 5, 77, 3, 0, -4 };
list<int> process5 = { 16, 24, 17, 21, 5, 36, 16, 26, 7, 31, 13, 28, 11, 21, 6, 13, 3, 11, 4, 0, -5 };
list<int> process6 = { 11, 22, 4, 8, 5, 10, 6, 12, 7, 14, 9, 18, 12, 24, 15, 30, 8, 0, -6 };
list<int> process7 = { 14, 46, 17, 41, 11, 42, 15, 21, 4, 32, 7, 19, 16, 33, 10, 0, -7 };
list<int> process8 = { 4, 14, 5, 33, 6, 51, 14, 73, 16, 87, 6, 0, -8 };
vector<list<int>>processQueue = { process1, process2, process3, process4, process5, process6, process7, process8 }; //creates a list of processes


class fcfs {
public:
	fcfs();
	void setCurrProcess();
	int getCurrProcess();
	double getCpuU();
	double getAvgWaitingTime();
	double getAvgTurnaroundTime();
	double getAvgResponseTime();
	void enqueueWaitingTime(int i, int & ioTime);
	void dequeueWaitingTime();
	void setCurrentWaitingTime();
	int getCurrentWaitingTime();
	void newCurrentWaitingTime(int & newTime);
	void nextWaitingTime();
	void updateCurrentWaitingTime(int & processingTime);
	void initiateScheduler();
private:
	list<int> currProcess;
	double cpuU;
	double avgWaitingTime;
	double avgTurnaroundTime;
	double avgResponseTime;
	int waitingTimes1[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int currentWaitingTime;
};

fcfs::fcfs() {
}

void fcfs::setCurrProcess() {
	currProcess = processQueue.front();
}

int fcfs::getCurrProcess() {
	return currProcess.front();
}

double fcfs::getCpuU() {
	return cpuU;
}

void fcfs::enqueueWaitingTime(int i, int & ioTime) {
	cout << "Added: " << ioTime << endl;
	//waitingTimes[i] = ioTime;
}

void fcfs::dequeueWaitingTime() {
	//waitingTimes.pop();
}

void fcfs::nextWaitingTime() {
	//cout << waitingTimes.size() << endl;
}

void fcfs::updateCurrentWaitingTime(int & processingTime) {
	currentWaitingTime = currentWaitingTime - processingTime;
	if (currentWaitingTime <= 0) {
		currentWaitingTime = getCurrentWaitingTime();
	}
}


void fcfs::setCurrentWaitingTime() {
	//currentWaitingTime = waitingTimes.front();
	//waitingTimes.pop();
}

int fcfs::getCurrentWaitingTime() {
	if (currentWaitingTime > 0) {
		return currentWaitingTime;
	}
	else {
		//currentWaitingTime = waitingTimes.front();
		//waitingTimes.pop();
		return currentWaitingTime;
	}
}

void fcfs::initiateScheduler() {

}

int main() {
	int k = 0;
	int y = 0;
	fcfs processor;
	int waitingTimes[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int finalWaitingTimes[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int readyQueue[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	double processingTime = 0;
	double totalProcessingTime = 0;
	double waitTime;
	double totalWaitTime = 0;
	double totalTime = 0;
	double cpuU;
	double totalTimeWaiting = 0;
	double avgTimeWaiting;
	deque<int>sjfProcesses;
	deque<int>sjfProcessOrder;
	deque<int>printTemp;
	/*
	{

	for (int p = 0; p < processQueue.size(); p++) {
	readyQueue[p] = processQueue[p].front();
	}

	while (processQueue.size() > 0) {
	for (int i = 0; i < processQueue.size(); i++) {

	if (waitingTimes[i] == 0) {
	readyQueue[i] = processQueue[i].front();
	}
	if (waitingTimes[i] < 0) {
	waitingTimes[i] = 0;
	readyQueue[i] = 0;
	}
	else if (waitingTimes[i] > 0) {
	cout << "P" << i+1 << " aint ready bc wait is: " << waitingTimes[i] << endl;
	readyQueue[i] = -1;
	finalWaitingTimes[i] = finalWaitingTimes[i] + waitingTimes[i];
	i++;
	if (i == processQueue.size()) {
	i = 0;
	cout << endl;
	}
	}
	////PROGRAM OUTPUT - DISPLAYED FOR EACH CONTEXT SWITCH
	cout << "--------------------------------------------------------------" << endl;
	cout << "CONTEXT SWITCH" << endl;
	cout << "--------------------------------------------------------------" << "\n\n";

	cout << "Current execution time: " << totalProcessingTime << endl;
	cout << "P" << i + 1 << ": " << processQueue[i].front() << endl;
	cout << "Ready queue, burst time: " << endl;
	for (int k = 0; k < 8; k++) {
	if (readyQueue[k] >= 0) {
	cout << "P" << k + 1 << ": " << readyQueue[k] << endl;
	}
	}
	cout << "Processes in I/O, burst time: " << endl;
	for (int a = 0; a < 8; a++) {
	if (waitingTimes[a] > 0) {
	cout << "P" << a + 1 << ": " << waitingTimes[a] << endl;
	}
	}
	//////////////////////////////////////////////////////

	if (processQueue[i].front() < 0) {
	cout << endl << "!--------------- Process " << processQueue[i].front() * -1 << " complete. ----------------------!" << endl;
	if (processQueue.size() == 1) {
	processQueue.erase(processQueue.begin() + i);
	break;
	}
	else {
	processQueue.erase(processQueue.begin() + i);
	if (i >= processQueue.size()) {
	break;
	}
	}
	}
	if (processQueue[i].size() < 2) {
	break;
	}
	processingTime = processQueue[i].front();
	totalProcessingTime = totalProcessingTime + processingTime;
	processQueue[i].pop_front();
	waitTime = processQueue[i].front();
	totalWaitTime = totalWaitTime + waitTime;
	waitingTimes[i] = waitingTimes[i] + waitTime;
	processQueue[i].pop_front();

	for (int j = 0; j < processQueue.size(); j++) {
	if (readyQueue[j] >= 0) {
	readyQueue[j] = processQueue[j].front();
	}
	if (j == i) {
	j++;
	}
	if (waitingTimes[i] == 0) {
	readyQueue[i] = processQueue[i].front();
	}
	else if (waitingTimes[j] < 0) {
	waitingTimes[j] = 0;
	}
	else if (waitingTimes[j] > 0) {
	waitingTimes[j] = waitingTimes[j] - processingTime;
	}
	}
	}

	cout << endl;
	}

	cout << "--------------------------------------------------------------" << endl;
	cout << "END FCFS SIMULATION" << endl;
	cout << "--------------------------------------------------------------" << "\n\n";

	for (int k = 0; k < 8; k++) { //calculates total time any process had to wait to run because of I/O
	totalTimeWaiting = finalWaitingTimes[k] + totalTimeWaiting;
	}
	totalTime = totalTimeWaiting + totalProcessingTime;
	cout << "Total time needed to complete all 8 processes: " << totalProcessingTime << endl;

	cpuU = totalProcessingTime / totalTime * 100;
	cout << "CPU utilization - [%] (U): " << cpuU << "%" << endl;

	cout << "Waiting times for each process: " << endl;
	for (int k = 0; k < 8; k++) { //calculates total time any process had to wait to run because of I/O
	cout << "P" << k + 1 << ": " << finalWaitingTimes[k] << endl;
	}

	cout << "Average waiting time for all processes(Tw): " << totalTimeWaiting / 8 << endl;

	cout << "Turnaround time for each process and the average turnaround time.(Ttr): " << endl;
	cout << "Response time for each process and the average response time (Tr): " << endl;





	}
	*/
	//SJF

	for (int j = 0; j < processQueue.size(); j++) { //readies up first set of CPU bursts
		sjfProcesses.push_back(processQueue[j].front());
		waitingTimes[j] = -100;
	}
	while (processQueue.size() > 0) {
		if (k >= 8) {
			k = 0;
		}
		if (waitingTimes[k] == -100) {
			cout << "";
			waitingTimes[k] = 0;
		}
		else if (waitingTimes[k] <= 0) { //IO over, moving to ready queue
			sjfProcesses.push_back(processQueue[k].front());
			sjfProcessOrder.push_back(processQueue[k].back() * -1);
			cout << "P" << sjfProcessOrder.front() << " moving to ready queue." << endl;
		}
		else {
			cout << "Process " << processQueue[k].back() * -1 << " is still waiting on I/O. Running next process." << endl;
		}
		if (sjfProcesses.size() > 0) {
			sort(sjfProcesses.begin(), sjfProcesses.begin() + sjfProcesses.size());
			for (int z = 0; z < sjfProcesses.size(); z++) {
				while (y < 8) {
					if (sjfProcesses[z] == processQueue[y].front()) {
						sjfProcessOrder.push_back(processQueue[y].back() * -1);
					}
					else {
						y++;
					}
				}
				y = 0;
			}
		}
		else {
			//break;
		}
		////PROGRAM OUTPUT - DISPLAYED FOR EACH CONTEXT SWITCH
		cout << "--------------------------------------------------------------" << endl;
		cout << "CONTEXT SWITCH" << endl;
		cout << "--------------------------------------------------------------" << "\n\n";

		cout << "Current execution time: " << totalProcessingTime << endl;
		cout << "P" << sjfProcessOrder[k] << ": " << sjfProcesses[k] << endl;
		cout << "Ready queue, burst time: " << endl;
		for (int b = 0; b < processQueue.size(); b++) {
			if (sjfProcesses[b] >= 0) {
				cout << "P" << sjfProcessOrder[b] << ": " << sjfProcesses[b] << endl;
			}
		}
		cout << "Processes in I/O, burst time: " << endl;
		for (int a = 0; a < 8; a++) {
			if (waitingTimes[a] > 0) {
				cout << "P" << sjfProcessOrder[a] << ": " << waitingTimes[a] << endl;
			}
		}
		//////////////////////////////////////////////////////
		processingTime = sjfProcesses.front();
		totalProcessingTime = totalProcessingTime + processingTime;
		sjfProcesses.pop_front();
		waitTime = sjfProcesses.front();
		totalWaitTime = totalWaitTime + waitTime;
		waitingTimes[k] = waitingTimes[k] + waitTime;
		sjfProcesses.erase(sjfProcesses.begin(), sjfProcesses.begin() + k);
		sjfProcessOrder.erase(sjfProcessOrder.begin(), sjfProcessOrder.begin() + k);
		for (int j = 0; j < processQueue.size(); j++) {
			if (j == k) {
				j++;
			}
			if (waitingTimes[j] < 0) {
				waitingTimes[j] = 0;
			}
			else if (waitingTimes[j] > 0) {
				waitingTimes[j] = waitingTimes[j] - processingTime;
			}
		}
		k++;
	}






























	/*
	while (processQueue.size() > 0) {
	for (int j = 0; j < processQueue.size(); j++) {
	sjfProcesses.at(j) = processQueue[j].front();
	}

	sort(sjfProcesses.begin(), sjfProcesses.begin() + sjfProcesses.size()); //sorts the ready queue by shortest CPU burst

	for (int i = 0; i < 8; i++) {
	cout << sjfProcesses.at(i) << endl;
	}

	for (int i = 0; i < processQueue.size(); i++) {

	if (waitingTimes[i] == 0) {
	readyQueue[i] = processQueue[i].front();
	}
	if (waitingTimes[i] < 0) {
	waitingTimes[i] = 0;
	readyQueue[i] = 0;
	}
	else if (waitingTimes[i] > 0) {
	cout << "P" << i + 1 << " aint ready bc wait is: " << waitingTimes[i] << endl;
	readyQueue[i] = -1;
	finalWaitingTimes[i] = finalWaitingTimes[i] + waitingTimes[i];
	i++;
	if (i == processQueue.size()) {
	i = 0;
	cout << endl;
	}
	}
	////PROGRAM OUTPUT - DISPLAYED FOR EACH CONTEXT SWITCH
	cout << "--------------------------------------------------------------" << endl;
	cout << "CONTEXT SWITCH" << endl;
	cout << "--------------------------------------------------------------" << "\n\n";

	cout << "Current execution time: " << totalProcessingTime << endl;
	cout << "P" << i + 1 << ": " << processQueue[i].front() << endl;
	cout << "Ready queue, burst time: " << endl;
	for (int k = 0; k < 8; k++) {
	if (readyQueue[k] >= 0) {
	cout << "P" << k + 1 << ": " << readyQueue[k] << endl;
	}
	}
	cout << "Processes in I/O, burst time: " << endl;
	for (int a = 0; a < 8; a++) {
	if (waitingTimes[a] > 0) {
	cout << "P" << a + 1 << ": " << waitingTimes[a] << endl;
	}
	}
	//////////////////////////////////////////////////////

	if (processQueue[i].front() < 0) {
	cout << endl << "!--------------- Process " << processQueue[i].front() * -1 << " complete. ----------------------!" << endl;
	if (processQueue.size() == 1) {
	processQueue.erase(processQueue.begin() + i);
	break;
	}
	else {
	processQueue.erase(processQueue.begin() + i);
	if (i >= processQueue.size()) {
	break;
	}
	}
	}
	if (processQueue[i].size() < 2) {
	break;
	}
	processingTime = processQueue[i].front();
	totalProcessingTime = totalProcessingTime + processingTime;
	processQueue[i].pop_front();
	waitTime = processQueue[i].front();
	totalWaitTime = totalWaitTime + waitTime;
	waitingTimes[i] = waitingTimes[i] + waitTime;
	processQueue[i].pop_front();

	for (int j = 0; j < processQueue.size(); j++)
	{
	if (readyQueue[j] >= 0) {
	readyQueue[j] = processQueue[j].front();
	}
	if (j == i) {
	j++;
	}
	if (waitingTimes[i] == 0) {
	readyQueue[i] = processQueue[i].front();
	}
	else if (waitingTimes[j] < 0) {
	waitingTimes[j] = 0;
	}
	else if (waitingTimes[j] > 0) {
	waitingTimes[j] = waitingTimes[j] - processingTime;
	}
	}
	}

	cout << endl;
	}

	cout << "--------------------------------------------------------------" << endl;
	cout << "END FCFS SIMULATION" << endl;
	cout << "--------------------------------------------------------------" << "\n\n";

	for (int k = 0; k < 8; k++) { //calculates total time any process had to wait to run because of I/O
	totalTimeWaiting = finalWaitingTimes[k] + totalTimeWaiting;
	}
	totalTime = totalTimeWaiting + totalProcessingTime;
	cout << "Total time needed to complete all 8 processes: " << totalProcessingTime << endl;

	cpuU = totalProcessingTime / totalTime * 100;
	cout << "CPU utilization - [%] (U): " << cpuU << "%" << endl;

	cout << "Waiting times for each process: " << endl;
	for (int k = 0; k < 8; k++) { //calculates total time any process had to wait to run because of I/O
	cout << "P" << k + 1 << ": " << finalWaitingTimes[k] << endl;
	}

	cout << "Average waiting time for all processes(Tw): " << totalTimeWaiting / 8 << endl;

	cout << "Turnaround time for each process and the average turnaround time.(Ttr): " << endl;
	cout << "Response time for each process and the average response time (Tr): " << endl;
	*/

}