#include "user.h"
#include "train.h"
#include "booking.h"

void showTrains(int sfd){
    printf("Train details : trainId ----- trainName ------ seatsAvailable ------ active/inactive\n", );
    while(1){
      struct train currTrain;
      read(sfd, currTrain, sizeof(struct train));
      printf("%s %s %d %d \n", currTrain.trainId, currTrain.trainName, currTrain.seatsCount , currTrain.status);
      break;
    }
}

void bookTicket(int sfd){
  // show trains first
  showTrains(sfd);

  // ask user it's choices
  char trainid[10];
  int seatsToBeBooked;
  printf("Enter train id to book a ticket : \n");
  scanf("%s", trainid);
  printf("Enter number of tickets to be booked : \n");
  scanf("%d", &seatsToBeBooked);

  // send  details to server
  write(sfd, trainid, sizeof(trainid));
  write(sfd, &seatsToBeBooked, sizeof(seatsToBeBooked));

  // read info from server
  int status;
  read(status, &status, sizeof(status));

  if(status==1){
    printf("Seats booked Successfully\n");
  }
  else{
    printf("Couldn't book seats!!!\n");
  }
  handleUserMenu(sfd);
}

void handleUserMenu(int sfd){
  printf("Enter 1 to book a ticket\n");
  printf("Enter 2 to delete a booked ticket\n");
  printf("Enter 3 to view your Previous bookings\n");
  printf("Enter 4 to update a booked ticket\n");
  printf("Enter 0 to exit\n");
  /// take user's choice
  char ch[1];
  scanf("%s", ch);
  write(sfd, ch, sizeof(ch));

  if(ch[0]=='1'){
    bookTicket(sfd);
  }
  else if(ch[0]=='2'){

  }
  else if(ch[0]=='3'){

  }
  else if(ch[0]=='4'){

  }
  else{

  }
}

void handleUserClient(int sfd){
  struct user currUser;
  int status;
  printf("Enter your user name\n");
  scanf("%s", currUser.userName);
  printf("Enter your password\n");
  scanf("%s", currUser.password);

  // send details to server
  write(sfd, &currUser,sizeof(struct user));

  // check for Successful login
  read(sfd, &status, sizeof(status));

  if(status==1){
    printf("Successfully logged in!!!\n");
    handleUserMenu(sfd);
  }
  else{
    printf("Error in your details\n");
  }
}

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
      printf("----------------Delete User Account Menu--------------\n");
      printf("Enter the unique user id of the User account:\n");
      scanf("%s", currUser.userId);
      write(sfd, &currUser,sizeof(struct user));
      char buff[200];
      read(sfd, buff,sizeof(buff));
      printf("%s\n",buff);
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
      scanf("%d", &currTrain.seatsCount);

      write(sfd, &currTrain,sizeof(struct train));
      char buff[100];
      read(sfd, buff,sizeof(buff));
      printf("%s\n",buff);
    }
    else if(choice[0] == '2'){ // Delete a Train
      printf("----------------Delete a Train Menu--------------\n");
      printf("Enter the Train Name:\n");
      scanf("%s", currTrain.trainName);
      write(sfd, &currTrain,sizeof(struct train));
      char buff[200];
      read(sfd, buff,sizeof(buff));
      printf("%s\n",buff);
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
