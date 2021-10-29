#include "user.h"
#include "train.h"
#include "booking.h"

void handleMainMenu(int);
void handleUserMenu(int);
void showTrains(int sfd){
    printf("Train details : trainId ----- trainName ------ seatsAvailable ------ active/inactive\n");
    while(1){
      struct train currTrain;
      read(sfd, &currTrain, sizeof(struct train));
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

void deleteBookedTicket(int sfd){
  char bookingId[10];
  printf("Enter booking id to delete the booked ticket\n");
  scanf("%s", bookingId);
  write(sfd, bookingId, sizeof(bookingId));
  int status;
  read(sfd, &status, sizeof(status));
  if(status == 1){
    printf("Tickets deleted Successfully\n");
  }
  else{
    printf("Error in deleting the booked ticket\n");
  }
  handleUserMenu(sfd);
}

void viewUserBookings(int sfd){
  char userid[10];
  printf("Enter your userId to view your booked tickets\n");
  scanf("%s", userid);
  write(sfd, userid, sizeof(userid));
  printf("Booking details : userId-------trainId------bookingID----- trainName ------ seatsBooked ------ status\n");
  while(1){
    struct booking userBookings;
    read(sfd, &userBookings, sizeof(struct booking));
    printf("%s %s %s %s %d %d \n", userBookings.userId, userBookings.trainId, userBookings.bookingId, userBookings.trainName, userBookings.seatsBooked , userBookings.status);
    break;
  }
}

void updateBookedTickets(int sfd){
    char bookingid[10];
    int newSeatsToBook;
    printf("Enter booking id to update booked tickets\n");
    scanf("%s", bookingid);
    printf("Enter new number of seats to be booked\n");
    scanf("%d\n", &newSeatsToBook);

    write(sfd, bookingid, sizeof(bookingid));
    write(sfd, &newSeatsToBook, sizeof(newSeatsToBook));

    int status;
    read(sfd, &status, sizeof(status));
    if(status == 1){
      printf("Tickets Updated Successfully\n");
    }
    else{
      printf("Error in updating the booked tickets\n");
    }
    handleUserMenu(sfd);
}

void handleUserMenu(int sfd){
  printf("Enter 1 to book a ticket\n");
  printf("Enter 2 to cancel a booked ticket\n");
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
    deleteBookedTicket(sfd);
  }
  else if(ch[0]=='3'){
    viewUserBookings(sfd);
  }
  else if(ch[0]=='4'){
    updateBookedTickets(sfd);
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
  printf("Enter 1 to modify/delete User Details \n");
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
        scanf("%d", &currUser.userId);
        printf("Enter your user name\n");
        scanf("%s", currUser.userName);
        printf("Enter your password\n");
        scanf("%s", currUser.password);

        write(sfd, &currUser,sizeof(struct user));
        char buff[100];
        read(sfd, buff,sizeof(buff));
        printf("%s\n",buff);
    }
    else if(choice[0] == '2'){ // Delete a user account
      printf("----------------Delete User Account Menu--------------\n");
      printf("Enter the unique user id of the User account:\n");
      scanf("%d", &currUser.userId);
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


    if(choice[0]=='1'){ // Add a train
      struct train currTrain;
      printf("----------------Add a Train Menu--------------\n");
      printf("Enter a unique train id:\n");
      scanf("%d", &currTrain.trainId);
      printf("Enter the train name\n");
      scanf("%s", currTrain.trainName);
      printf("Enter the Seats available\n");
      scanf("%d", &currTrain.seatsCount);

      write(sfd, &currTrain,sizeof(struct train));
      int status;
      read(sfd, &status,sizeof(status));
      if(status==1){
        printf("Successfully added the train\n");
      }
      else{
        printf("Error!!!\n");
      }
    }
    else if(choice[0] == '2'){ // Delete a Train
      struct train currTrain;
      printf("----------------Delete a Train Menu--------------\n");
      printf("Enter the Train Name that you want to delete:\n");
      scanf("%s", currTrain.trainName);
      write(sfd, &currTrain,sizeof(struct train));
      int status;
      read(sfd, &status,sizeof(status));
      if(status==1){
        printf("Successfully deleted the train\n");
      }
      else{
        printf("Error in deleting the train!!!\n");
      }
    }
    else if(choice[0] == '3'){ // Update a Train
      struct train currTrain;
      printf("----------------Update a Train Menu--------------\n");
      printf("Enter the train id for which you want to update the details\n");
      scanf("%d", &currTrain.trainId);
      printf("Enter the new train name:\n");
      scanf("%s", currTrain.trainName);
      write(sfd, &currTrain,sizeof(struct train));
      int status;
      read(sfd, &status,sizeof(status));
      if(status==1){
        printf("Successfully Updated the train name\n");
      }
      else{
        printf("Error!!!\n");
      }
    }
    else if(choice[0] == '4'){ // search for a Train
      struct train currTrain;
      printf("----------------Search for a Train--------------\n");
      printf("Enter the train name:\n");
      scanf("%s", currTrain.trainName);
      write(sfd, &currTrain,sizeof(struct train));
      int status;
      read(sfd, &status,sizeof(status));
      if(status==1){
        read(sfd, &currTrain, sizeof(struct train));
        printf("Train with the name found and the details are: \n");
        printf("TrainId ------- trainName -------- seatsAvailable -------- Active/inactive\n");
        printf("%d %s %d %d\n", currTrain.trainId, currTrain.trainName, currTrain.seatsCount, currTrain.status);
      }
      else{
        printf("Train with the given name not found !!!\n");
      }
    }
  }
  else{
    printf("Enter Correct Input\n");
  }
}
void handleSignUp(int sfd){
  struct user currUser;
  printf("----------------Add User Account Menu--------------\n");
  printf("Enter your unique user name\n");
  scanf("%s", currUser.userName);
  printf("Enter your password\n");
  scanf("%s", currUser.password);

  write(sfd, &currUser,sizeof(struct user));

  int status;
  read(sfd, &status, sizeof(status));
  printf("%d\n", status);
  if(status==1){
    printf("Signed Up Successfully\n");
  }
  else{
    printf("Couldn't signUp, user already exists!!!\n");
  }
  handleMainMenu(sfd);
}

void handleLogin(int sfd){
  char welcomeMenu[] = "Login as:\n1.Normal Account User\n2.Agent Account User\n3.Administrator\n4.Exit\nPlease enter your choice:";
  printf("%s", welcomeMenu);

  char ch[1];
  scanf("%s", ch);
  write(sfd, ch, sizeof(ch));
  if(ch[0]=='1'){ // User
      handleUserClient(sfd);
  }
  else if(ch[0]=='2'){ // Agent
      //handleAgentClient(sfd);
  }
  else if(ch[0]=='3'){ // Admin
    handleAdminClient(sfd);
  }
}

void handleMainMenu(int sfd){
  printf("Enter 1 to Signup As a user\n");
  printf("Enter 2 to Login as an Admin/User/Agent\n");
  char choice[1];
  scanf("%s", choice);
  write(sfd, choice, sizeof(choice));
  if(choice[0]=='1'){
    handleSignUp(sfd);
  }
  else if(choice[0]=='2'){
    handleLogin(sfd);
  }
  else{
    printf("Error you didn't enter a valid input\n");
  }
}
