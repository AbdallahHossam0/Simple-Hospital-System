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

#define INSERT_COMMAND 1
#define SEARCH_COMMAND 2
#define PRINT_COMMAND 3
#define END_COMMAND 4

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

char selectCommand(void);
void getPatientData(void);
void search(void);
void printPatientData(void);
void deleteWholeList(void);


struct node *head = NULL;

int main(void) {
	setvbuf(stdout, NULL,_IONBF, 0);
	setvbuf(stderr, NULL,_IONBF, 0);

	int command;

	while(1){
		// for user interface
		command = selectCommand();
		switch(command){
		case INSERT_COMMAND:
			getPatientData();
			break;
		case SEARCH_COMMAND:
			search();
			break;
		case PRINT_COMMAND:
			printPatientData();
			break;
		case END_COMMAND:
			deleteWholeList();
			printf("Program ended!\n");
			return EXIT_SUCCESS;
		default:
			printf("Undefined Command!!\n\n");
		}
	}
	return EXIT_SUCCESS;
}


char selectCommand(void){
	char command[MAX_COMMAND_SIZE];
	printf("Enter the Command: (insert, search, print or end to end the program)\n");
	scanf("%s", command);
	if(!strcmp(command, "insert")){
		return INSERT_COMMAND;
	}
	else if(!strcmp(command, "search")){
		return SEARCH_COMMAND;
	}
	else if(!strcmp(command, "print")){
		return PRINT_COMMAND;
	}
	else if(!strcmp(command, "end")){
		return END_COMMAND;
	}
	else return 0;

}

// function to store the patient data
void getPatientData(){
	struct Patient data;
	printf("Enter Patient Name: \n");
	scanf("%s",data.name);
	printf("Enter Patient ID: \n");
	scanf("%d",&data.ID);
	printf("Enter Patient Weight: \n");
	scanf("%d", &data.weight);
	struct node *ptr = malloc(sizeof(struct node));
	struct node *temp = NULL;
	ptr -> patientData.ID = data.ID;
	ptr -> patientData.weight = data.weight;
	strcpy(ptr -> patientData.name, data.name);
	ptr -> next = NULL;
	if(head == NULL){
		head = ptr;
		return;
	}
	temp = head;
	for(; temp -> next != NULL; temp = temp -> next);
	temp -> next = ptr;
}

// function to search if the user exists or no by ID
void search(){
	int ID;
	printf("Enter the ID: \n");
	scanf("%d", &ID);
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

//Function to print the patient data by ID,
void printPatientData(){
	int ID;
	printf("Enter the ID: (Enter 0 to print data for all patients)\n");
	scanf("%d", &ID);
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

//Function to delete the whole list from the heap after ending the program
void deleteWholeList(void){
	struct node *temp = NULL;
	for(; head != NULL; ){
		temp = head -> next;
		free(head);
		head = temp;
	}
}
