/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]		: simple_hospital_system.c
 *
 * [AUTHOR]			: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]	: 24 - 7 - 2021
 *
 * [DESCRIPTION]	: Program to handle patients of hospital
 * ---------------------------------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Preprocessor Directives
#define MAX_NAME_SIZE 50
#define MAX_COMMAND_SIZE 10

// Structure to store the patient data
struct Patient{
	int ID;
	char name[MAX_NAME_SIZE];
	int weight;
};

// structure to implement the linked list
struct node{
	struct Patient patientData;
	struct node* next;
};

void getPatientData(const struct Patient *data);
void search(int ID);
void printPatientData(int ID);
void deleteWholeList(void);


struct node *head = NULL;

int main(void) {
	setvbuf(stdout, NULL,_IONBF, 0);
	setvbuf(stderr, NULL,_IONBF, 0);

	char command[MAX_COMMAND_SIZE];
	int ID;
	struct Patient data;
	while(1){
		printf("Enter the Command: (insert, search, print or end to end the program)\n");
		scanf("%s", command);
		if(!strcmp(command, "insert")){
			printf("Enter Patient Name: \n");
			scanf("%s",data.name);
			printf("Enter Patient ID: \n");
			scanf("%d",&data.ID);
			printf("Enter Patient Weight: \n");
			scanf("%d", &data.weight);
			getPatientData(&data);
		}
		else if(!strcmp(command, "search")){
			printf("Enter the ID: \n");
			scanf("%d", &ID);
			search(ID);
		}
		else if(!strcmp(command, "print")){
			printf("Enter the ID: (Enter 0 to print data for all patients)\n");
			scanf("%d", &ID);
			printPatientData(ID);
		}
		else if(!strcmp(command, "end")){
			deleteWholeList();
			printf("Program ended!\n");
			break;
		}
		else{
			printf("Undefined Command!!\n\n");
		}

	}
	return EXIT_SUCCESS;
}



void getPatientData(const struct Patient *data){
	struct node *ptr = malloc(sizeof(struct node));
	struct node *temp = NULL;
	ptr -> patientData.ID = data->ID;
	ptr -> patientData.weight = data->weight;
	strcpy(ptr -> patientData.name, data->name);
	ptr -> next = NULL;
	if(head == NULL){
		head = ptr;
		return;
	}
	temp = head;
	for(; temp -> next != NULL; temp = temp -> next);
	temp -> next = ptr;
}
void search(int ID){
	struct node *temp = head;
	if(temp == NULL){
		printf("ID not found!!!\n\n");
		return;
	}

	for(; temp != NULL; temp = temp -> next){
		if(temp -> patientData.ID == ID){
			printf("ID found\n");
			printf("node Name: %s \nPatient Weight: %d \n\n", temp -> patientData.name, temp -> patientData.weight);
			return;
		}
	}
	printf("ID not found!!!\n\n");

}
void printPatientData(int ID){
	struct node *temp = head;
	if(ID == 0){
		if(temp == NULL){
			printf("NO Patients\n");
			return;
		}
		printf("ID\tName\t Weight\n");
		for(; temp != NULL; temp = temp -> next){
			printf("%d-\t%s\t%d\n", temp -> patientData.ID, temp -> patientData.name, temp -> patientData.weight);
		}
	}
	else{
		if(temp == NULL){
			printf("ID not found!!!\n");
			return;
		}
		for(; temp != NULL; temp = temp -> next){
			if(temp -> patientData.ID == ID){
				printf("%d-\t%s\t%d\n", temp -> patientData.ID, temp -> patientData.name, temp -> patientData.weight);
				return;
			}
		}
		printf("ID not found!!!\n");
	}
}

void deleteWholeList(void){
	struct node *temp = NULL;
	for(; head != NULL; ){
		temp = head -> next;
		free(head);
		head = temp;
	}
}
