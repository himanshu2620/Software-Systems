#include "user.h"
#include "train.h"
#include "booking.h"

void handleMainMenu(int);
void handleUserMenu(int,int);
void handleAdminUserMenu(int);
void handleAdminTrainMenu(int);
void handleAgentUserMenu(int,int);

void showTrains(int sfd){
    struct train currTrain;
    int stillRead;
    printf("-----------------Available Trains --------------\n");
    printf("trainId ----- trainName ------ seatsAvailable ------ active/inactive\n");
    while(1){
      read(sfd, &stillRead, sizeof(stillRead));
      if(stillRead==0){
        break;
      }
      read(sfd, &currTrain, sizeof(struct train));
      printf("%d %s %d %d \n", currTrain.trainId, currTrain.trainName, currTrain.seatsCount , currTrain.status);
    }
    printf("\n");
}

void bookUserTicket(int sfd, int uid){
  // show trains first
  showTrains(sfd);

  // ask user it's choices
  struct booking currBooking;
  int trainid;
  int seatsToBeBooked;
  currBooking.userId = uid;
  printf("Enter train id to book a ticket : \n");
  scanf("%d", &currBooking.trainId);
  printf("Enter number of tickets to be booked : \n");
  scanf("%d", &currBooking.seatsBooked);
  // send  details to server
  write(sfd, &currBooking, sizeof(struct booking));
  // read info from server
  int status;
  read(sfd, &status, sizeof(status));
  if(status==1){
    printf("Seats booked Successfully\n");
  }
  else{
    printf("Couldn't book seats!!!\n");
  }
  handleUserMenu(sfd, uid);
}

void deleteBookedTicket(int sfd, int uid){
  struct booking bookedTicket;
  printf("Enter booking id to delete the booked ticket\n");
  scanf("%d", &bookedTicket.bookingId);
  write(sfd, &bookedTicket, sizeof(struct booking));
  int status;
  read(sfd, &status, sizeof(status));
  if(status == 1){
    printf("Tickets deleted Successfully\n");
  }
  else{
    printf("Error in deleting the booked ticket\n");
  }
  handleUserMenu(sfd,uid);
}

void viewUserBookings(int sfd, int uid){
  int status;
  struct booking userBookings;
  userBookings.userId = uid;
  write(sfd, &userBookings, sizeof(struct booking));
  read(sfd, &status, sizeof(status));
  if(status==1){
    printf("Booking details :\n userId-------trainId------bookingID----- trainName ------ seatsBooked ------ status\n");
    int stillRead;
    while(1){
      read(sfd, &stillRead, sizeof(stillRead));
      if(stillRead==0){
        break;
      }
      read(sfd, &userBookings, sizeof(struct booking));
      printf("%d %d %d %s %d %d \n", userBookings.userId, userBookings.trainId, userBookings.bookingId, userBookings.trainName, userBookings.seatsBooked , userBookings.status);
    }
  }
  else{
    printf("Can't find user bookings\n");
  }
  handleUserMenu(sfd,uid);
}

void updateBookedTickets(int sfd, int uid){
    struct booking bookedTicket;
    printf("Enter booking id to update booked tickets\n");
    scanf("%d", &bookedTicket.bookingId);
    printf("Enter new number of seats to be booked\n");
    scanf("%d", &bookedTicket.seatsBooked);

    write(sfd, &bookedTicket, sizeof(struct booking));

    int status;
    read(sfd, &status, sizeof(status));
    if(status == 1){
      printf("Tickets Updated Successfully\n");
    }
    else{
      printf("Error in updating the booked tickets\n");
    }
    handleUserMenu(sfd,uid);
}

void handleUserMenu(int sfd, int uid){
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
    bookUserTicket(sfd, uid);
  }
  else if(ch[0]=='2'){
    deleteBookedTicket(sfd, uid);
  }
  else if(ch[0]=='3'){
    viewUserBookings(sfd, uid);
  }
  else if(ch[0]=='4'){
    updateBookedTickets(sfd, uid);
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

  if(status!=0){
    int uid = status;
    printf("Successfully logged in!!!\n");
    handleUserMenu(sfd,uid);
  }
  else{
    printf("Error in your details\n");
  }
}

void deleteUserAccount(int sfd){
  struct user currUser;
  printf("----------------Delete User Account Menu--------------\n");
  printf("Enter the userName for the account that you want to delete:\n");
  scanf(" %[^\n]", currUser.userName);
  write(sfd, &currUser,sizeof(struct user));
  int status;
  read(sfd, &status,sizeof(status));
  if(status==1){
    printf("Successfully deleted the user account\n");
  }
  else{
    printf("Error in deleting!!!\n");
  }
  handleAdminUserMenu(sfd);
}

void updateUserAccount(int sfd){
  struct user currUser;
  printf("----------------Update User Account Menu--------------\n");
  printf("Enter the user id for the account that you want to update\n");
  scanf("%d", &currUser.userId);
  printf("Enter the new userName for the account that you want to update:\n");
  scanf(" %[^\n]", currUser.userName);

  write(sfd, &currUser,sizeof(struct user));
  int status;
  read(sfd, &status,sizeof(status));
  if(status==1){
    printf("Successfully updated the new user name\n");
  }
  else{
    printf("Error in updating !!!\n");
  }
  handleAdminUserMenu(sfd);
}

void searchUserAccount(int sfd){
  struct user currUser;
  printf("Enter the userName for the account that you want to search:\n");
  scanf(" %[^\n]", currUser.userName);
  write(sfd, &currUser,sizeof(struct user));
  int status;
  read(sfd, &status,sizeof(status));
  if(status==1){
    struct user currUser;
    read(sfd, &currUser, sizeof(struct user));
    printf("User with the name found and the details are: \n");
    printf("UserId ------- userName -------- password -------- Active/inactive--------Agent(1)/Normal User(0)\n");
    printf("%d %s %s %d %d\n", currUser.userId, currUser.userName, currUser.password, currUser.status, currUser.type);
  }
  else{
    printf("Can't find any account with the entered user name !!!\n");
  }
  handleAdminUserMenu(sfd);
}

void addTrain(int sfd){
  struct train currTrain;
  printf("----------------Add a Train Menu--------------\n");
  printf("Enter a unique train id:\n");
  scanf("%d", &currTrain.trainId);
  printf("Enter the train name\n");
  scanf(" %[^\n]", currTrain.trainName);
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
  handleAdminTrainMenu(sfd);
}

void deleteTrain(int sfd){
  struct train currTrain;
  printf("----------------Delete a Train Menu--------------\n");
  printf("Enter the Train Name that you want to delete:\n");
  scanf(" %[^\n]", currTrain.trainName);
  write(sfd, &currTrain,sizeof(struct train));
  int status;
  read(sfd, &status,sizeof(status));
  if(status==1){
    printf("Successfully deleted the train\n");
  }
  else{
    printf("Error in deleting the train!!!\n");
  }
  handleAdminTrainMenu(sfd);
}

void updateTrain(int sfd){
  struct train currTrain;
  printf("----------------Update a Train Menu--------------\n");
  printf("Enter the train id for which you want to update the details\n");
  scanf("%d", &currTrain.trainId);
  printf("Enter the new train name:\n");
  scanf(" %[^\n]", currTrain.trainName);
  write(sfd, &currTrain,sizeof(struct train));
  int status;
  read(sfd, &status,sizeof(status));
  if(status==1){
    printf("Successfully Updated the train name\n");
  }
  else{
    printf("Error!!!\n");
  }
  handleAdminTrainMenu(sfd);
}

void searchTrain(int sfd){
  struct train currTrain;
  printf("----------------Search for a Train--------------\n");
  printf("Enter the train name:\n");
  scanf(" %[^\n]", currTrain.trainName);
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
  handleAdminTrainMenu(sfd);
}

void handleAdminUserMenu(int sfd){
  printf("Enter 1 to delete a User account\n");
  printf("Enter 2 to modify a User account\n");
  printf("Enter 3 to search for a User account\n");
  char choice[1];
  scanf("%s", choice);
  write(sfd, choice, sizeof(choice));


  if(choice[0] == '1'){ // Delete a user account
      deleteUserAccount(sfd);
  }
  else if(choice[0] == '2'){ // Update a user account
      updateUserAccount(sfd);
  }
  else if(choice[0] == '3'){ // search for a user account
      searchUserAccount(sfd);
  }
}

void handleAdminTrainMenu(int sfd){
  printf("Enter 1 to add a Train \n");
  printf("Enter 2 to delete a Train\n");
  printf("Enter 3 to update a Train\n");
  printf("Enter 4 to search for a Train\n");
  char choice[1];
  scanf("%s", choice);
  write(sfd, choice, sizeof(choice));


  if(choice[0]=='1'){ // Add a train
      addTrain(sfd);
  }
  else if(choice[0] == '2'){ // Delete a Train
      deleteTrain(sfd);
  }
  else if(choice[0] == '3'){ // Update a Train
      updateTrain(sfd);
  }
  else if(choice[0] == '4'){ // search for a Train
      searchTrain(sfd);
  }
}

void handleAdminClient(int sfd){
  char userName[30];
  char password[30];
  printf("Enter admin's username to login: \n");
  scanf("%s", userName);
  printf("Enter password: \n");
  scanf("%s", password);
  int status;
  write(sfd, userName, sizeof(userName));
  write(sfd, password, sizeof(password));
  read(sfd, &status, sizeof(status));
  if(status==1){
    printf("---------------Welcome Admin---------------\n");
    printf("Enter 1 to modify/delete User Details \n");
    printf("Enter 2 to add/modify/delete Train Details \n");
    char ch[1];
    scanf("%s", ch);
    write(sfd, ch, sizeof(ch)); //
    if(ch[0]=='1'){
      handleAdminUserMenu(sfd);
    }
    else if(ch[0]=='2'){ // modify train details
      handleAdminTrainMenu(sfd);
    }
  }
  else{
    printf("Enter Correct Input\n");
  }
}
void handleUserSignUp(int sfd){
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

void handleAgentSignup(int sfd){
  struct user currUser;
  printf("----------------Add Agent Account Menu--------------\n");
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

void bookAgentTicket(int sfd, int uid){
  // show trains first
  showTrains(sfd);

  // ask user it's choices
  struct booking currBooking;
  int trainid;
  int seatsToBeBooked;
  currBooking.userId = uid;
  printf("Enter train id to book a ticket : \n");
  scanf("%d", &currBooking.trainId);
  printf("Enter number of tickets to be booked : \n");
  scanf("%d", &currBooking.seatsBooked);
  // send  details to server
  write(sfd, &currBooking, sizeof(struct booking));
  // read info from server
  int status;
  read(sfd, &status, sizeof(status));
  printf("I'm here\n");
  if(status==1){
    printf("Seats booked Successfully\n");
  }
  else{
    printf("Couldn't book seats!!!\n");
  }
  handleAgentUserMenu(sfd, uid);
}

void deleteAgentBookedTicket(int sfd, int uid){
  struct booking bookedTicket;
  printf("Enter booking id to delete the booked ticket\n");
  scanf("%d", &bookedTicket.bookingId);
  write(sfd, &bookedTicket, sizeof(struct booking));
  int status;
  read(sfd, &status, sizeof(status));
  if(status == 1){
    printf("Tickets deleted Successfully\n");
  }
  else{
    printf("Error in deleting the booked ticket\n");
  }
  handleAgentUserMenu(sfd,uid);
}

void viewAgentUserBookings(int sfd, int uid){
  int status;
  struct booking userBookings;
  userBookings.userId = uid;
  write(sfd, &userBookings, sizeof(struct booking));
  read(sfd, &status, sizeof(status));
  if(status==1){
    printf("Booking details :\n userId-------trainId------bookingID----- trainName ------ seatsBooked ------ status\n");
    int stillRead;
    while(1){
      read(sfd, &stillRead, sizeof(stillRead));
      if(stillRead==0){
        break;
      }
      read(sfd, &userBookings, sizeof(struct booking));
      printf("%d %d %d %s %d %d \n", userBookings.userId, userBookings.trainId, userBookings.bookingId, userBookings.trainName, userBookings.seatsBooked , userBookings.status);
    }
  }
  else{
    printf("Can't find user bookings\n");
  }
  handleAgentUserMenu(sfd,uid);
}

void updateAgentBookedTickets(int sfd, int uid){
  struct booking bookedTicket;
  printf("Enter booking id to update booked tickets\n");
  scanf("%d", &bookedTicket.bookingId);
  printf("Enter new number of seats to be booked\n");
  scanf("%d", &bookedTicket.seatsBooked);

  write(sfd, &bookedTicket, sizeof(struct booking));

  int status;
  read(sfd, &status, sizeof(status));
  if(status == 1){
    printf("Tickets Updated Successfully\n");
  }
  else{
    printf("Error in updating the booked tickets\n");
  }
  handleAgentUserMenu(sfd,uid);
}

void handleAgentUserMenu(int sfd, int uid){
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
    bookAgentTicket(sfd, uid);
  }
  else if(ch[0]=='2'){
    deleteAgentBookedTicket(sfd, uid);
  }
  else if(ch[0]=='3'){
    viewAgentUserBookings(sfd, uid);
  }
  else if(ch[0]=='4'){
    updateAgentBookedTickets(sfd, uid);
  }
}

void handleAgentClient(int sfd){
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

  if(status!=0){
    int uid = status;
    printf("Successfully logged in!!!\n");
    handleAgentUserMenu(sfd,uid);
  }
  else{
    printf("Error in your details\n");
  }
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
      handleAgentClient(sfd);
  }
  else if(ch[0]=='3'){ // Admin
    handleAdminClient(sfd);
  }
}

void handleSignUp(int sfd){
  printf("Enter 1 to Signup As a User\n");
  printf("Enter 2 to Signup As a Agent\n");
  char choice[1];
  scanf("%s", choice);
  write(sfd, choice, sizeof(choice));
  if(choice[0]=='1'){
    handleUserSignUp(sfd);
  }
  else if(choice[0]=='2'){
    handleAgentSignup(sfd);
  }
  else{
    printf("Error you didn't enter a valid input\n");
  }
}

void handleMainMenu(int sfd){
  printf("Enter 1 to Signup As a User/Agent\n");
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
