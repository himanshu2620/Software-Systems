#include "user.h"
#include "train.h"
#include "booking.h"


void handleAdminClient(int sfd){
  printf("Enter 1 to add/modify/delete User Details \n");
  printf("Enter 2 to add/modify/delete Train Details \n");
  char ch[1];
  scanf("%s", ch);
  write(sfd, ch, sizeof(ch)); //
  if(ch[0]=='1'){
    printf("Enter 1 to add a User account\n");
    printf("Enter 2 to delete a User account\n");
    printf("Enter 3 to modify a User account\n");
    printf("Enter 4 to search for a User account\n");
    char choice[1];
    scanf("%s", choice);
    write(sfd, choice, sizeof(choice));
    struct user currUser;

    if(choice[0] == '1'){ // Add a User Account
        printf("----------------Add User Account Menu--------------\n");
        printf("Enter a unique user id:\n");
        scanf("%s", currUser.userId);
        printf("Enter your user name\n");
        scanf("%s", currUser.userName);
        printf("Enter your password\n");
        scanf("%s", currUser.password);
        for(int i=0;i<100;i++){
           currUser.bookings[i] = 0; // Initialize the bookings array
        }
        currUser.count = 0;
        write(sfd, &currUser,sizeof(struct user));
        char buff[100];
        read(sfd, buff,sizeof(buff));
        printf("%s\n",buff);
    }
    else if(choice[0] == '2'){ // Delete a user account

    }
    else if(choice[0] == '3'){ // Update a user account

    }
    else if(choice[0] == '4'){ // search for a user account

    }
  }
  else if(ch[0]=='2'){ // modify train details
    printf("Enter 1 to add a Train \n");
    printf("Enter 2 to delete a Train\n");
    printf("Enter 3 to update a Train\n");
    printf("Enter 4 to search for a Train\n");
    char choice[1];
    scanf("%s", choice);
    write(sfd, choice, sizeof(choice));
    struct train currTrain;

    if(choice[0]=='1'){ // Add a train
      printf("----------------Add a Train Menu--------------\n");
      printf("Enter a unique train id:\n");
      scanf("%s", currTrain.trainId);
      printf("Enter the train name\n");
      scanf("%s", currTrain.trainName);
      printf("Enter the Seats available\n");
      scanf("%s", currTrain.seatsCount);
      
      write(sfd, &currUser,sizeof(struct user));
      char buff[100];
      read(sfd, buff,sizeof(buff));
      printf("%s\n",buff);
    }
    else if(choice[0] == '2'){ // Delete a Train

    }
    else if(choice[0] == '3'){ // Update a Train

    }
    else if(choice[0] == '4'){ // search for a Train

    }
  }
  else{
    printf("Enter Correct Input\n");
  }
}
