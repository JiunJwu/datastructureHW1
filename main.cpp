#include <iostream>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// Insert at the end
struct CostumerData {
	int id;
	int time; //剩餘處理時間
	struct CostumerData *next;
};

void add_queue(struct CostumerData** head_ref, int gateWay, int new_id, int new_time) {
	struct CostumerData* new_node = (struct CostumerData*)malloc(sizeof(struct CostumerData));
	struct CostumerData* last = head_ref[gateWay];

	new_node->id = new_id;
	new_node->time = new_time;
	new_node->next = NULL;

	if ( last == NULL) {
		head_ref[gateWay] = new_node;
		//printf("queue header [%d-%d]\n", head_ref[gateWay]->id,  head_ref[gateWay]->time);
		return;
	}
	
	//printf("queue last [%d-%d]\n", new_node->id,  new_node->time);
	
	while (last->next != NULL) last = last->next;

	last->next = new_node;
	return;
}

// Delete nodes
CostumerData* popout_queue(struct CostumerData** head_ref, int costum_size) {
	
	bool isEmpty = true;
	
	//find min process time in first node of each queue
	CostumerData *temp = NULL;
	int min_proc_time = 999999;
	
	for( int i = 0 ;  i< costum_size; i ++ ){
		temp = head_ref[i];
		if(temp == NULL){
			continue;
		}
		
		min_proc_time = min_proc_time > temp->time ? temp->time:min_proc_time;
	}

	
	CostumerData* result = NULL; 
	CostumerData *last_node = NULL;
	
	for( int i = 0 ;  i< costum_size; i ++ ){
		temp = head_ref[i];
		if(temp == NULL){
			continue;
		}
		if(temp->time == min_proc_time){
			head_ref[i] = temp -> next;
			
			if(result == NULL){
				result = temp;
				result -> next = NULL;
				last_node = result;
			}else{
				last_node = result;
				while (last_node->next != NULL) last_node = last_node -> next;
				last_node -> next = temp;
				temp -> next = NULL;
			}
		}else{
			temp -> time = temp -> time - min_proc_time;
		}
	}
	return result;
}


void outputRest(struct CostumerData* node) {
	while (node != NULL) {
		printf("output:%d\n",node->id);
		node = node->next;
	}
}

bool isAllQueueEmpty(struct CostumerData** head_ref, int costum_size){
	for( int i = 0 ;  i < costum_size; i ++ ){
		if( head_ref[i] != NULL){
			return false;
		}
	}
	
	return true;
}

int main(int argc, char** argv) {
	int costum_size = 0 ; //海關數量
	printf("costoms num:");
	scanf("%d", &costum_size);

	int i;
	int tmpTime;
	
	int *costum_process_time_array = (int*)malloc(costum_size * sizeof(int));
	printf("costoms comsume time:");
	
	for( i = 0 ; i < costum_size; i++) {
		scanf("%d", &tmpTime);
		costum_process_time_array[i] = tmpTime;
	}
	int commands=0;  //指令數量
	printf("commands num:");
	scanf("%d", &commands);

	char action[32];
	const char *enqueue = "enqueue";
	const char *dequeue = "dequeue";

	int j=0;
	int k,q;
	int customer_id, custom_no;
	//CostumerData *head = (struct CostumerData*) calloc(costum_size, sizeof(struct CostumerData*));    //每個海關口都是一個柱列
	CostumerData *head[costum_size] = {};
	CostumerData *result = NULL, *last_node = NULL;
	for( i = 0; i < commands; i++) {
		
		printf("command%d input:", i);
		scanf("%s", action);
		
		if(strcmp(action, enqueue) == 0) {
			scanf("%d", &customer_id);
			scanf("%d", &custom_no);
			add_queue(head, custom_no-1 , customer_id, costum_process_time_array[custom_no-1]);
		} else if(strcmp(action, dequeue) == 0) {
		   CostumerData* tempResult = popout_queue(head, costum_size);
		   if(result == NULL)
		   		result = tempResult;
		   	else{
		   		last_node = result;
		   		while (last_node->next != NULL) last_node = last_node->next;
		   		last_node -> next = tempResult; 
			}
		}
	}
	
	while(!isAllQueueEmpty(head, costum_size)){
		 CostumerData* tempResult = popout_queue(head, costum_size);
		   if(result == NULL)
		   		result = tempResult;
		   	else{
		   		last_node = result;
		   		while (last_node->next != NULL) last_node = last_node->next;
		   		last_node -> next = tempResult; 
			}
	}
	
	outputRest(result);
	free(result);
	system("pause");
	return 0;
}


