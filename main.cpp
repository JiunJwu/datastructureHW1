#include <iostream>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// Insert at the end
struct Costumerdata{
	int id;
	int time; //剩餘處理時間 
	struct Costumerdata *next; 
};

void insertAtEnd(struct Costumerdata** head_ref, int new_id, int new_t, int new_no) {
  struct Costumerdata* new_node = (struct Costumerdata*)malloc(sizeof(struct Costumerdata));
  struct Costumerdata* last = *head_ref[new_no]; 

  new_node->id = new_id;
  new_node->time = new_t;
  new_node->next = NULL;

  if (*head_ref[new_no]==NULL) {
  *head_ref[new_no] = new_node;
  return;
  }

  while (last->next != NULL) last = last->next;

  last->next = new_node;
  return;
}

// Sort the linked list
void sortLinkedList(struct Costumerdata** head_ref) {
  struct Costumerdata *current = *head_ref, *index = NULL;
  int temp;

  if (head_ref == NULL) {
  return;
  } else {
  while (current != NULL) {
    // index points to the node next to current
    index = current->next;

    while (index != NULL) {
    if (current->time > index->time) {
      temp = current->time;
      current->time = index->time;
      index->time = temp;
      temp = current->id;
      current->id = index->id;
      index->id = temp;  
    }
    else if (current->time == index->time) {
	    if (current->id > index->id) {
	      temp = current->time;
	      current->time = index->time;
	      index->time = temp;
	      temp = current->id;
	      current->id = index->id;
	      index->id = temp; 		   
	    }
    }
    index = index->next;
    }
    current = current->next;
  }
  }
  
}


// Delete nodes
void deleteNode(struct Costumerdata* head_ref, int key) {
  struct Costumerdata *temp = head_ref, *prev;
  if (temp != NULL && temp->time == key) {
	  head_ref = temp->next;
	  free(temp);
	  return;
  }
  // Find the key to be deleted
  while (temp != NULL && temp->time != key) {
  prev = temp;
  temp = temp->next;
  }

  // If the key is not present
  if (temp == NULL) return;

  // Remove the node
  prev->next = temp->next;

  free(temp);
}


void outputList(struct Costumerdata** head_ref ,int costums) {
	struct Costumerdata *node = *head_ref;
	int *outputlist = (int*)malloc(costums * sizeof(int));
	int i,j,k;
    int smallTime=head_ref[0]->time;
    for(i=1;i<costums;i++){            //找到最小的出關時間
	    if(head_ref[i]->id!=0){
	    	if(smallTime>head_ref[i]->time){
    			smallTime=head_ref[i]->time;
			}
		}
	}
	k=0;
	for(i=0;i<costums;i++){
		if (node[i].id != 0) {
			node[i].time=node->time-smallTime;
		}
		if(node[i].time <= 0){
			outputlist[k]=node->id;
			deleteNode(head_ref[i], 0);
			k++;
		}
	}
	int a;
	for(i=0;i<k-1;i++){
		for(j=i+1;j<k;j++){
			if(outputlist[i] >= outputlist[j]){
				a=outputlist[j];
				outputlist[j]=outputlist[i];
				outputlist[i]=a;
			}
		}
	}
	for(i=0;i<k;i++){
		printf("output:%d\n",outputlist[i]);
	}
	free(outputlist);
	free(node);
}


void outputRest(struct Costumerdata* node) {
  while (node != NULL) {
	printf("output:%d\n",node->id);
  	node = node->next;
  }
}

int main(int argc, char** argv) {
	int costums = 0 ; //海關數量 
	printf("costums num:");
	scanf("%d",&costums);
	
	int i;
	int *costumlist;
	int tmpTime;
	costumlist = (int*)malloc(costums * sizeof(int));
	printf("costums times:");
	for(i=0; i < costums; i++)
	{
		scanf("%d", &tmpTime);
	    costumlist[i]=tmpTime;
	}
	int commands=0;  //指令數量 
	printf("commands num:");
	scanf("%d",&commands);
	
	char action[10];
	const char *enq = "en";
    const char *deq = "de";
    
    int j=0;
    int k,q;
    int tmpid,tmpno;
    Costumerdata* head;   
	head = (struct Costumerdata*)calloc(costums, sizeof(struct Costumerdata));    //每個海關口都是一個柱列 
	
	for(i=0;i<commands;i++){
		printf("command%d input:",i);
		scanf("%s",action);
		if(strcmp(action, enq) == 0){
			scanf("%d",&tmpid);
			scanf("%d",&tmpno);
			insertAtEnd(&head, tmpid,costumlist[tmpno-1],tmpno-1);
			//sortLinkedList(&head);
		}else if(strcmp(action, deq) == 0){
  			outputList(&head,costums);			
		}
		else{
			printf("commands failed");
		}
	}
	outputRest(head);
	system("pause");
	return 0;
}


