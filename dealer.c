#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define LEN 30



struct car{
    char make[LEN+1];
    char model[LEN+1];
    char color[LEN+1];
    int year;
    int city_mpg;
    int highway_mpg;
    int quantity;
    struct car *next;
};

struct car *append_to_list(struct car *list);

void find_car(struct car *list);

void printList(struct car *list);

void clearList(struct car *list);

struct car *delete_from_list(struct car *list);

int read_line(char str[], int n);
/**********************************************************
*  main: Prompts the user to enter an operation code,     *
*  then calls a function to perform the requested   *
*  action. Repeats until the user enters the        *
*  command 'q'. Prints an error message if the user *
*  enters an illegal code.                          *
**********************************************************/

int main(void)
{
    char code;
    struct car *car_list = NULL;
    printf("Operation Code: a for appending to the list, f for finding a car, p for printing the list, q for quit.\n");

    for (;;)
    {
        printf("Enter operation code: ");
        scanf(" %c", &code);
        while (getchar() != '\n')   /* skips to end of line */
        ;
        switch (code)
        {
                    case 'a': car_list = append_to_list(car_list);
                                break;
                    case 'f': find_car(car_list);
                                break;
                    case 'p': printList(car_list);
                                break;
                    case 'q': clearList(car_list);
                                return 0;
                    case 'd': car_list = delete_from_list(car_list);
                                break;

                    default:  printf("Illegal code\n");
        }
        printf("\n");
    }
}


struct car *append_to_list(struct car *list)
{
    struct car *new_car=NULL;           /*new_car pointer will allocate through the memory of struct car*/

    struct car *current=NULL;           /*The current and previous pointers are for me to go through the linked list.*/

    struct car *previous=NULL;

    new_car=malloc(sizeof(struct car));

     if(new_car==NULL)
        {
            return list;
        }

    printf("Enter the make: ");         /*Here, I am prompting the user for information on the make, model, color, year, mileage, and quantity of the car*/
    read_line(new_car->make,31);

    printf("Enter the model: ");
    read_line(new_car->model,31);

    printf("Enter the color: ");
    read_line(new_car->color,31);

    printf("Enter the year: ");
    scanf("%d", &new_car->year);

    printf("Enter the city miles per gallon: ");
    scanf("%d", &new_car->city_mpg);

    printf("Enter the highway miles per gallon: ");
    scanf("%d", &new_car->highway_mpg);

    printf("Enter the quantity: ");
    scanf("%d", &new_car->quantity);

    if(list==NULL)
        {
            return new_car;
        }

    for(current=list;current!=NULL;current=current->next)               /*This for-loop will check if the car that the user entered already exists within the list.*/
   {
        previous=current;
        if(strcmp(current->make,new_car->make)==0 && strcmp(current->model,new_car->model)==0 && strcmp(current->color,new_car->color)==0 && (current->year==new_car->year))
            {
               printf("That car already exists.");
                return list;
            }



    }



    for(previous=NULL, current=list;current!=NULL;previous=current,current=current->next){
        if(previous==NULL && strcmp(current->make,new_car->make)>0){
            previous->next=new_car;
            new_car->next=current;
            return list;
        }
        else if(strcmp(current->make, new_car->make)>0 && strcmp(previous->make,new_car->make)<0){
            previous->next=new_car;
            new_car->next=current;
            return list;
        }
        else if(strcmp(current->make,new_car->make)==0 && strcmp(previous->make, new_car->make)<0){
            if(strcmp(current->model, new_car->model)>0){
                previous->next=new_car;
                new_car->next=current;
                return list;
            }
        }
    }
    if(strcmp(previous->make, new_car->make)<0 && current==NULL){
            previous->next=new_car;
            new_car->next=NULL;
            return list;
        }



}


void find_car(struct car * list)
{
    struct car *current;

    char make[31];              /*Declaring character arrays to store the strings of make and model*/
    char model[31];

    int length=0;

    printf("Enter the make: ");
    read_line(make,31);

    printf("Enter the model: ");
    read_line(model,31);



    for(current=list;current!=NULL;current=current->next)           /*This for-loop will check through each of the nodes in the linked list to see if the make and model are the same using the string compare function*/
    {
        if(strcmp(current->make, make)==0 && strcmp(current->model, model)==0)
            {
                printf("Color: %s, Year: %d, City MPG: %d, Highway MPG: %d, Quantity: %d", current->color, current->year, current->city_mpg, current->highway_mpg, current->quantity);
                length++;
            }
    }

    if(length==0)
    {
        printf("Car not found.");
    }

}
void printList(struct car *list){

    struct car *current=NULL;



    for(current=list;current!=NULL;current=current->next)      /*The for-loop will go through each of the nodes in the list and display all the information in the nodes.*/
    {
        printf("Make: %s, \tModel: %s, \tColor: %s, \tManufacture Year: %d, \tCity MPG: %d, \tHighway MPG: %d, \tQuantity: %d", current->make, current->model, current->color, current->year, current->city_mpg, current->highway_mpg, current->quantity);
        printf("\n");
    }



}
void clearList(struct car *list)
{
    struct car *current=NULL;
    struct car *previous=NULL;

    for(current=list;current!=NULL; )          /*In the for-loop, I am assigning the previous pointer to the current pointer before I iterate to the next node using current->next.*/
    {
        previous=current;                      /*This way, I do not delete the null at the end of the list when deleting everything.*/
        current=current->next;
        free(previous);
    }


}

struct car *delete_from_list(struct car *list){
    struct car *new_car=NULL;
    struct car *current=NULL;

    char make[31];
    char model[31];
    char color[31];
    int year;

    new_car=malloc(sizeof(struct car));

     if(new_car==NULL)
        {
            return list;
        }

    printf("Please enter the make: ");
    read_line(make,31);

    printf("Please enter the model: ");
    read_line(model,31);

    printf("Please enter the color: ");
    read_line(color,31);

    printf("Please enter the year: ");
    scanf("%d", &year);

    for(current=list; current!=NULL;current=current->next){
        if(strcmp(current->make, make)==0 && strcmp(current->model, model)==0 && strcmp(current->color,color)==0 && current->year==year){
            free(current);
        }
    }
    return list;
}



int read_line(char str[], int n)
{
    int ch, i = 0;
    while (isspace(ch = getchar()))
        ;
    str[i++] = ch;
    while ((ch = getchar()) != '\n') {
        if (i < n)
            str[i++] = ch;
    }
    str[i] = '\0';
    return i;
}
