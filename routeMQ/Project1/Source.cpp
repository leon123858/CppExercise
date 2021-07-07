#include <iostream>
#include "pthread.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>//#include <unistd.h>//Sleep(WINDOWS) vs sleep(LINUX)
#include <string> 
using namespace std;
#define providerCount 4
#define consumerCount 4
#define messageCount 4
/* LINUX C的 jash_thread 轉WINDOWS */

class node {
public:
	int value;
	node* next;

	node(int v) {
		this->value = v;
		this->next = nullptr;
	}
};

class MQ {
public:
	node* firstNode, * endNode;
	pthread_mutex_t first_mutex, end_mutex;

	MQ() {
		firstNode = endNode = nullptr;
		pthread_mutex_init(&first_mutex, NULL);
		pthread_mutex_init(&end_mutex, NULL);
	}

	int pushNode(int value) {
		node* n = new node(value);
		if (!n)
			return 1;
		//pthread_mutex_lock(&first_mutex);
		if (endNode == nullptr || firstNode == nullptr) {
			endNode = firstNode = n;
		}
		else {
			endNode->next = n;
			endNode = n;
		}
		//pthread_mutex_unlock(&first_mutex);
	}

	int popNode() {
		if (endNode == nullptr || firstNode == nullptr) {
			return 0;//empty
		}
		//pthread_mutex_lock(&end_mutex);
		int reValue;
		if (endNode == firstNode) {
			reValue = firstNode->value;
			delete firstNode;
			endNode = firstNode = nullptr;
		}
		else {
			reValue = firstNode->value;
			node* header_node = firstNode;
			firstNode = header_node->next;
			delete header_node;
		}
		//pthread_mutex_unlock(&end_mutex);
		return reValue;
	}

	~MQ() {
		free();
	}
private:
	void free() {
		delete firstNode;
		delete endNode;
	}
};

class msg {
public:
	MQ* MQ_ptr;
	int value;
	int index;
	msg(MQ* ptr, int v, int i) {
		MQ_ptr = ptr;
		value = v;
		index = i;
	}
};


void* push_thread(void* push_msg)
{
	msg* ptr = (msg*)push_msg;
	cout << "thread" + to_string(ptr->index) + " : I want to push" << endl;
	ptr->MQ_ptr->pushNode(ptr->value);
	cout << "thread" + to_string(ptr->index) + " : I push success" << endl;
	delete push_msg;
	pthread_exit(NULL);
	return NULL;
}

void* push_threads(void* MQ_list) {
	MQ* list = (MQ*)MQ_list;
	const int messageNum = messageCount;
	for (int i = 0; i < messageNum; ++i) {
		cout << "thread 0: I want to push" << endl;
		list[i % consumerCount].pushNode(i + 1);
		cout << "thread 0 : I push into" + to_string(i % consumerCount) + " success" << endl;
	}
	pthread_exit(NULL);
	return NULL;
}

/* This thread reads ints from the queue and frees them */
void* pop_thread(void* pop_msg)
{
	msg* ptr = (msg*)pop_msg;
	while (true)
	{
		cout << "thread" + to_string(ptr->index) + " : I want to pop\n";
		int popValue = ptr->MQ_ptr->popNode();
		cout << "thread" + to_string(ptr->index) + " : I pop  " + to_string(popValue) + " success\n";
		if (popValue == -1) break;
	}
	delete pop_msg;
	pthread_exit(NULL);
	return NULL;
}

void threads_wait(int count, pthread_t* list)
{
	/*等待線程結束*/
	for (int i = 0; i < count; i++)
	{
		pthread_join(list[i], NULL);
		printf("線程%d已經結束\n", i);
	}
}

void thread_wait(pthread_t* thread) {
	pthread_join(*thread, NULL);
	printf("線程0已經結束\n");
}

void Pause()
{
	printf("Press Enter key to continue...");
	fgetc(stdin);
}

int main()
{
	cout << "Start !!!" << endl;
	pthread_t* provider, * consumers;
	MQ* message_queue;
	message_queue = new MQ[consumerCount];
	provider = new pthread_t();
	consumers = new pthread_t[consumerCount];

	if ((pthread_create(provider, NULL, push_threads, message_queue)) != 0)
		printf("Error creating push thread 0\n");

	for (int i = 0; i < consumerCount; ++i) {
		msg* pop_msg = new msg(&message_queue[i], 0, i);
		if ((pthread_create(&consumers[i], NULL, pop_thread, pop_msg)) != 0)
			printf("Error creating pop thread %i\n", i);
	}

	thread_wait(provider);

	/* Push kill signals */
	for (int i = 0; i < consumerCount; ++i) {
		message_queue[i].pushNode(-1);
	}

	threads_wait(consumerCount, consumers);

	delete provider;
	delete[]consumers;
	delete[]message_queue;
	Pause();
	return 0;
}
