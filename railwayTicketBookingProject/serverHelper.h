#include "user.h"
#include "train.h"
#include "booking.h"



void handleAdminUser(int);
void handleAdminTrain(int);
void handleNormalUser(int);
void handleLoggedInUser(int);

void showTrains(int nsd){

}

void bookUserTicket(int nsd){
    //showTrains(nsd);
    struct booking currBooking;
    printf("I'm here 3\n");
    read(nsd, &currBooking, sizeof(struct booking));
    printf("I'm here 2\n");
    currBooking.bookingId = ((rand()%3097)*2) + 1000;
    printf("I'm here 1\n");
    int fd = open("database/trains.dat", O_RDWR);
    printf("I'm here 0\n");
    struct train tempTrain;
    int status = 0;
    printf("FD: %d\n",fd);
    while(read(fd, &tempTrain, sizeof(struct train))){
      if(tempTrain.trainId == currBooking.trainId){
        if(tempTrain.seatsCount >= currBooking.seatsBooked){ // check for the trainId and Available seats
          printf("Heyyyyyyyyyyyyyyy\n");
          tempTrain.seatsCount = tempTrain.seatsCount - currBooking.seatsBooked; // decrement the available seats
          strcpy(currBooking.trainName,tempTrain.trainName);
          lseek(fd, -sizeof(struct train), SEEK_CUR);
          write(fd , (char *)&tempTrain, sizeof(struct train));

          status = 1;
          int fd1 = open("database/bookings.dat", O_CREAT | O_APPEND | O_RDWR , 0666);
          write(fd1, &currBooking, sizeof(struct booking));
          close(fd1);
          break;
        }
      }
    }
    write(nsd, &status, sizeof(status));
    close(fd);
    handleLoggedInUser(nsd);
}

void viewUserBookings(int nsd){
    struct booking userBookings;
    read(nsd, &userBookings, sizeof(struct booking));
    struct booking temp;
    int status = 0;
    int fd = open("database/bookings.dat", O_RDWR , 0666);
    while(read(fd, &temp, sizeof(struct booking))!=0){
      if(temp.userId == userBookings.userId){
        status = 1;
        write(nsd, &status, sizeof(status));
        write(nsd, &temp, sizeof(struct booking));
        break;
      }
    }
    if(status==0){
      write(nsd, &status, sizeof(status));
    }
    close(fd);
    handleLoggedInUser(nsd);
}

int checkUserExists(int nsd, char userName[]){
  struct user currUser;
  int flag = 0;
  int fd = open("database/users.dat", O_RDWR , 0666);
  while(read(fd, (char* )&currUser, sizeof(struct user))){
    if(strcmp(userName, currUser.userName)==0){
      flag = 1;
      break;
    }
  }
  close(fd);
  return flag;
}

int checkValidUser(int nsd, char userName[], char password[]){
  struct user currUser;
  int flag = 0;
  int fd = open("database/users.dat", O_RDWR , 0666);
  while(read(fd, (char* )&currUser, sizeof(struct user))){
    if(strcmp(userName, currUser.userName)==0 && strcmp(password, currUser.password)==0){
      flag = currUser.userId;
      break;
    }
  }
  close(fd);
  return flag;
}

void handleLoggedInUser(int nsd){
  char ch[1];
  read(nsd,ch,sizeof(ch));
  if(ch[0]=='1'){ // book  a ticket
    bookUserTicket(nsd);
  }
  else if(ch[0]=='2'){ // delete a booked ticket

  }
  else if(ch[0]=='3'){ // view bookings
    viewUserBookings(nsd);
  }
  else if(ch[0]=='4'){ // update a booked ticket

  }
}

void handleNormalUser(int nsd){
  struct user currUser;
  read(nsd, &currUser, sizeof(struct user));
  int flag = checkValidUser(nsd, currUser.userName, currUser.password);
  int uid = flag;
  printf("%d\n",flag);
  write(nsd, &flag, sizeof(flag));
  if(flag){
    handleLoggedInUser(nsd);
  }
  else{
    //handleNormalUser(nsd);
  }
}

void deleteUserAccount(int nsd){
  struct user currUser;
  read(nsd,&currUser,sizeof(struct user));
  int fd = open("database/users.dat", O_RDWR);

  struct user tempUser;
  int status = 0;
  while(read(fd, &tempUser, sizeof(struct user))!=0){
    if(strcmp(tempUser.userName,currUser.userName) == 0 ){
        tempUser.status = 0;
        status = 1;
        write(fd , &tempUser, sizeof(struct user));
    }
  }
  write(nsd, &status, sizeof(status));
  close(fd);
  handleAdminUser(nsd);
}
void updateUserAccount(int nsd){
  struct user currUser;
  read(nsd,&currUser,sizeof(struct user));
  int fd = open("database/users.dat", O_RDWR);

  struct user tempUser;
  int status = 0;
  while(read(fd, &tempUser, sizeof(struct user))!=0){
    if(tempUser.userId == currUser.userId){
        strcpy(tempUser.userName,currUser.userName);
        status = 1;
        write(fd , &tempUser, sizeof(struct user));
    }
  }
  write(nsd, &status, sizeof(status));
  close(fd);
  handleAdminUser(nsd);
}

void searchUserAccount(int nsd){
  struct user currUser;
  read(nsd,&currUser,sizeof(struct user));
  int fd = open("database/users.dat", O_RDWR);

  struct user tempUser;
  int status = 0;
  while(read(fd, &tempUser, sizeof(struct user))!=0){
    if(strcmp(tempUser.userName,currUser.userName) == 0 ){
        status = 1;
        write(nsd, &status, sizeof(status));
        write(nsd , &tempUser, sizeof(struct user));
        break;
    }
  }
  if(status == 0){
    write(nsd, &status, sizeof(status));
  }
  close(fd);
  handleAdminUser(nsd);
}

void addTrain(int nsd){
  int status = 1;
  struct train currTrain;
  read(nsd, &currTrain, sizeof(struct train));
  currTrain.status = 1; // train is up and running
  int fd = open("database/trains.dat", O_CREAT | O_APPEND | O_RDWR , 0666);
  write(fd, (char* )&currTrain, sizeof(struct train));
  write(nsd, &status, sizeof(status));
  close(fd);
  handleAdminTrain(nsd);
}

void deleteTrain(int nsd){
    struct train currTrain;
    read(nsd,&currTrain,sizeof(struct train));
    int fd = open("database/trains.dat", O_RDWR);

    struct train tempTrain;
    int stat = 0;
    while(read(fd, &tempTrain, sizeof(struct train))!=0){
      if(strcmp(tempTrain.trainName,currTrain.trainName) == 0 ){
          int newStatus = 0;
          tempTrain.status = newStatus;
          stat = 1;
          write(fd , &tempTrain, sizeof(struct train));
      }
    }
    write(nsd, &stat, sizeof(stat));
    close(fd);
    handleAdminTrain(nsd);
}

void updateTrain(int nsd){
  struct train currTrain;
  read(nsd,&currTrain,sizeof(struct train));
  int fd = open("database/trains.dat", O_RDWR);

  struct train tempTrain;
  int status = 0;
  while(read(fd, &tempTrain, sizeof(struct train))!=0){
    if(tempTrain.trainId == currTrain.trainId){
        strcpy(tempTrain.trainName, currTrain.trainName);
        status = 1;
        write(fd , &tempTrain, sizeof(struct train));
    }
  }
  write(nsd, &status, sizeof(status));
  close(fd);
  handleAdminTrain(nsd);
}

void searchTrain(int nsd){
  struct train currTrain;
  read(nsd,&currTrain,sizeof(struct train));
  int fd = open("database/trains.dat", O_RDWR);

  struct train tempTrain;
  int status = 0;
  while(read(fd, &tempTrain, sizeof(struct train))!=0){
    if(strcmp(tempTrain.trainName,currTrain.trainName) == 0 ){
        status = 1;
        write(nsd, &status, sizeof(status));
        write(nsd, &tempTrain, sizeof(struct train));
        break;
    }
  }
  if(status==0){
    write(nsd, &status, sizeof(status));
  }
  close(fd);
  handleAdminTrain(nsd);
}

void handleAdminUser(int nsd){
  char choice[1];
  read(nsd,choice,sizeof(choice));
  if(choice[0]=='1'){ // delete account
      deleteUserAccount(nsd);
  }
  else if(choice[0]=='2'){ // update account
      updateUserAccount(nsd);
  }
  else if(choice[0]=='3'){ // search for an account
      searchUserAccount(nsd);
  }
}

void handleAdminTrain(int nsd){
  char choice[1];
  read(nsd,choice,sizeof(choice));
  if(choice[0]=='1'){ // Add a train account
      addTrain(nsd);
  }
  else if(choice[0]=='2'){ // delete a train
      deleteTrain(nsd);
  }
  else if(choice[0]=='3'){ // update train details
      updateTrain(nsd);
  }
  else if(choice[0]=='4'){ // search for a train
      searchTrain(nsd);
  }
}

void handleAdmin(int nsd){
    char ch[1];
    read(nsd,ch,sizeof(ch));
    if(ch[0]=='1'){ // for modifying User accounts
        handleAdminUser(nsd);
    }
    else if(ch[0]=='2'){ // for modifying Train info
        handleAdminTrain(nsd);
    }
}



void handleMainMenu(int nsd){
  char ch[5];
  read(nsd,ch,sizeof(ch));
  if(ch[0]=='1'){
    printf("normal \n");
    handleNormalUser(nsd);
  }
  else if(ch[0]=='2'){
    printf("agent \n");
  }
  else if(ch[0]=='3'){
    printf("admin \n");
    handleAdmin(nsd);
  }
  else{
    printf("exiting the system now...\n");
  }
}

void signUp(int nsd){
  struct user currUser;
  read(nsd, &currUser, sizeof(struct user));
  int status = 1;
  if(!checkUserExists(nsd, currUser.userName)){
      int fd = open("database/users.dat", O_CREAT | O_APPEND | O_RDWR , 0666);
      currUser.status = 1;
      currUser.userId = ((rand()%3097)*2) + 1000;
      write(fd, (char* )&currUser, sizeof(struct user));
  }
  else{
    status = -1;
  }
  write(nsd, &status, sizeof(status));
  handleMainMenu(nsd);
}



void handleInitialLogin(int nsd){
    //write(nsd, welcomeMenu, sizeof(welcomeMenu));
    sleep(0.01);
    char choice[1];
    read(nsd, choice, sizeof(choice));
    if(choice[0]=='1'){
      signUp(nsd);
    }
    else if(choice[0]=='2'){
      handleMainMenu(nsd);
    }
}
