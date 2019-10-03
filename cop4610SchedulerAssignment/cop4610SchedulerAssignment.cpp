//Matthew Taylor
//COP4610: Computer Operating Systems, Fall 2019
//CPU Scheduler Programming Assignment

#include <iostream>
#include <list>
#include <vector>
#include <queue>

using namespace std;

//all processes, process goes {CPU burst, I/O time, CPU burst, I/O time, CPU burst, I/O time,........, last CPU burst}
list<int> process1 = { 5, 27, 3, 31, 5, 43, 4, 18, 6, 22, 4, 26, 3, 24, 4 };
list<int> process2 = { 4, 48, 5, 44, 7, 42, 12, 37, 9, 76, 4, 41, 9, 31, 7, 43, 8 };
list<int> process3 = { 8, 33, 12, 41, 18, 65, 14, 21, 4, 61, 15, 18, 14, 26, 5, 31, 6 };
list<int> process4 = { 3, 35, 4, 41, 5, 45, 3, 51, 4, 61, 5, 54, 6, 82, 5, 77, 3 };
list<int> process5 = { 16, 24, 17, 21, 5, 36, 16, 26, 7, 31, 13, 28, 11, 21, 6, 13, 3, 11, 4 };
list<int> process6 = { 11, 22, 4, 8, 5, 10, 6, 12, 7, 14, 9, 18, 12, 24, 15, 30, 8 };
list<int> process7 = { 14, 46, 17, 41, 11, 42, 15, 21, 4, 32, 7, 19, 16, 33, 10 };
list<int> process8 = { 4, 14, 5, 33, 6, 51, 14, 73, 16, 87, 6 };
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
	void enqueueWaitingTime(int & ioTime);
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
	queue<int> waitingTimes;
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

void fcfs::enqueueWaitingTime(int & ioTime) {
	cout << "Added: " << ioTime << endl;
	waitingTimes.push(ioTime);
}

void fcfs::dequeueWaitingTime() {
	waitingTimes.pop();
}

void fcfs::nextWaitingTime() {
	cout << waitingTimes.size() << endl;
}

void fcfs::updateCurrentWaitingTime(int & processingTime) {
	currentWaitingTime = currentWaitingTime - processingTime;
	if (currentWaitingTime <= 0) {
		currentWaitingTime = getCurrentWaitingTime();
	}
}


void fcfs::setCurrentWaitingTime() {
	currentWaitingTime = waitingTimes.front();
	waitingTimes.pop();
}

int fcfs::getCurrentWaitingTime() {
	if (currentWaitingTime > 0) {
		return currentWaitingTime;
	}
	else {
		currentWaitingTime = waitingTimes.front();
		waitingTimes.pop();
		return currentWaitingTime;
	}
}

void fcfs::initiateScheduler() {

}

int main() {
	fcfs processor;
	int i = 1;
	int numProcessesCompleted = 0;

	for (int j = 0; j < processQueue.size(); j++) {
		processQueue[j].pop_front();
		processor.enqueueWaitingTime(processQueue[j].front());
		processQueue[j].pop_front();
		i = j;
		while (processQueue[j].size() > 0) {
			while (processQueue[i].front() <= processor.getCurrentWaitingTime()) {
				cout << "Current process: " << i + 1 << " --- Waiting time: " << processor.getCurrentWaitingTime() << " --- Current burst time: " << processQueue[i].front() << endl;
				processor.updateCurrentWaitingTime(processQueue[i].front()); //subtracts burst time from waiting time
				if (processQueue[i].size() == 1) {
					processQueue.erase(processQueue.begin() + i);
					cout << "PROCESS " << i + 1 << " COMPLETE!" << endl;
					i = 1;
					break;
				}
				processQueue[i].pop_front(); //burst time complete
				processor.enqueueWaitingTime(processQueue[i].front()); //queues up next IO time bc {burst time, IO time, burst time}
				cout << "Num of IO times in queue: ";
				processor.nextWaitingTime();
				cout << endl;
				processQueue[i].pop_front(); //removes IO time
				i++;
				if (i >= processQueue.size()) {
					i = j;
				}
			}
			processor.setCurrentWaitingTime();
			cout << "-------------------------------------------------" << "\n\n";
		}
		processQueue.erase(processQueue.begin() + j);
		cout << "PROCESS " << j << " COMPLETE!" << endl;
	}
}