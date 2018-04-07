#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#define EXP 9

using namespace std;
struct Reference{
	string addr;
	struct Reference *next;
	struct Reference *prev;
};
class dictionary{
public:
	string addr;
	Reference *listAddr;
	dictionary(){};
	dictionary(string ref){
		addr = ref;
		listAddr = NULL;
	}
};
class HashTable{
public:
	int size;
	vector<list<dictionary> > table;

	HashTable(){};
	HashTable(int size){
		this->size = size;
		this->table.resize(size);
	}
	int GetKey(string str);
	int GetIndex(string str);
	void Insert(dictionary data);
	void Delete(string key);
	Reference *Search(string key);
	void DisplayTable();
};

int HashTable::GetKey(string str){
	int sum = 0, p = 1, i;
	for(i = (int)str.size()-1; i >= 0; i--){
		sum += (str[i] * p);
		p *= EXP;
	}
	return sum;
};

int HashTable::GetIndex(string str){
	return (GetKey(str) % (this->size));
}

void HashTable::Insert(dictionary data){
	int index = GetIndex(data.addr);
	table[index].push_front(data);
}

void HashTable::Delete(string key){
	int index = GetIndex(key);
	for(list<dictionary>::iterator itr = table[index].begin(); itr != table[index].end(); itr++){
		if((*itr).addr == key){
			//free((*itr).listAddr);
			table[index].erase(itr);
		}
	}
}
Reference *HashTable::Search(string key){
	int index = GetIndex(key);
	for(list<dictionary>::iterator itr = table[index].begin(); itr != table[index].end(); itr++){
		if((*itr).addr == key){
			return (*itr).listAddr;
		}
	}
	return NULL;
}

void HashTable::DisplayTable(){
	int i = 0;
	for(; i < table.size(); i++){
		cout << "slot" << i << ":";
		for(list<dictionary>::iterator itr = table[i].begin(); itr != table[i].end(); itr++){
			cout << (*itr).addr << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void PrintLinkedList(Reference *r){
	cout << "Link : ";
	while(r){
		cout << r->addr << " ";
		r = r->next;
	}
	cout << endl;
}

int main(int argc, char **argv){
	fstream f;
	int frameNum;
	cout << "--------------FIFO--------------" << endl;
	for(frameNum = 64; frameNum <= 512; frameNum *= 2){
		f.open("trace.txt", ios::in);
		string temp, ref;
		unsigned long int misscount = 0, hitcount = 0;
		HashTable hash(frameNum); // Initialize hash table size
		Reference *head, *tail;
		head = NULL;
		tail = NULL;
		while(getline(f, temp)){
			ref = temp.substr(3,5);
			dictionary dict(ref);
			if(!head){
				Reference *tmp;
				tmp = new Reference;
				tmp->addr = ref;
				tmp->next = NULL;
				head = tmp;
				tail = tmp;
				misscount++;
				dict.listAddr = tmp;
				hash.Insert(dict);
			}
			else{
				if(misscount < frameNum && hash.Search(ref) == NULL){
					Reference *tmp;
					tmp = new Reference;
					tmp->addr = ref;
					tmp->next = NULL;
					tail->next = tmp;
					tail = tail->next;
					misscount++;
					dict.listAddr = tail;
					hash.Insert(dict);
				}
				else{
					if(hash.Search(ref) != NULL){
						hitcount++;
					}
					else{
						hash.Delete(head->addr);
						Reference *tmp;
						tmp = head;
						head = head->next;
						free(tmp);
						Reference *tmp2;
						tmp2 = new Reference;
						tmp2->addr = ref;
						tmp2->next = NULL;
						tail->next = tmp2;
						tail = tail->next;
						misscount++;
						dict.listAddr = tail;
						hash.Insert(dict);
					}
				}
			}
		}
		cout << "frame size = " << frameNum << endl;
		cout << "misscount : " << misscount << endl << "hitcount : " << hitcount << endl << "page fault ratio : ";
		printf("%.9lf\n", ((double)misscount/(double)(misscount+hitcount)));
		if(frameNum != 512) cout << endl;
		f.close();
	}
	cout << "--------------------------------" << endl;
	cout << "---------------LRU--------------" << endl;
	for(frameNum = 64; frameNum <= 512; frameNum *= 2){
		f.open("trace.txt", ios::in);
		string temp, ref;
		unsigned long int misscount = 0, hitcount = 0;
		HashTable hash(frameNum); // Initialize hash table size
		Reference *head, *tail;
		head = NULL;
		tail = NULL;
		while(getline(f, temp)){
			ref = temp.substr(3,5);
			dictionary dict(ref);
			if(!head){
				Reference *tmp;
				tmp = new Reference;
				tmp->addr = ref;
				tmp->next = NULL;
				tmp->prev = NULL;
				head = tmp;
				tail = tmp;
				misscount++;
				dict.listAddr = tmp;
				hash.Insert(dict);
			}
			else{
				if(misscount < frameNum && hash.Search(ref) == NULL){
					Reference *tmp;
					tmp = new Reference;
					tmp->addr = ref;
					tmp->next = NULL;
					tmp->prev = tail;
					tail->next = tmp;
					tail = tail->next;
					misscount++;
					dict.listAddr = tail;
					hash.Insert(dict);
				}
				else{
					Reference *del; // find deleted node
					if((del = hash.Search(ref)) != NULL){
						bool adjHead = true, adjTail = true;
						if(del == head){ // if the deleted node is head node
							if(head->next != NULL){ // more than one node in linked list
								Reference *t;
								t = head;
								head = head->next;
								head->prev = NULL;
								free(t);
								hash.Delete(ref);
							}
							else adjHead = false; // only one node in linked list
						}
						else{
							if(del != tail){
								Reference *prv;
								prv = del->prev;
								prv->next = prv->next->next;
								prv->next->prev = prv;
								free(del);
								hash.Delete(ref);
							}
							else adjTail = false;
						}
						if(adjHead && adjTail){
							Reference *tmp;
							tmp = new Reference;
							tmp->addr = ref;
							tmp->next = NULL;
							tmp->prev = tail;
							tail->next = tmp;
							tail = tail->next;
							dict.listAddr = tail;
							hash.Insert(dict);
						}
						hitcount++;
					}
					else{
						hash.Delete(head->addr);
						Reference *tmp;
						tmp = head;
						head = head->next;
						head->prev = NULL;
						free(tmp);
						Reference *tmp2;
						tmp2 = new Reference;
						tmp2->addr = ref;
						tmp2->next = NULL;
						tmp2->prev = tail;
						tail->next = tmp2;
						tail = tail->next;
						misscount++;
						dict.listAddr = tail;
						hash.Insert(dict);
					}
				}
			}
		}
		cout << "frame size = " << frameNum << endl;
		cout << "misscount : " << misscount << endl << "hitcount : " << hitcount << endl << "page fault ratio : ";
		printf("%.9lf\n", ((double)misscount/(double)(misscount+hitcount)));
		if(frameNum != 512) cout << endl;
		f.close();
	}
	cout << "--------------------------------" << endl;
	return 0;
}
