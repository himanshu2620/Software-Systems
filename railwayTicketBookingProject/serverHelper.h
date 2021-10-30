#include "user.h"
#include "train.h"
#include "booking.h"



void handleAdminUser(int);
void handleAdminTrain(int);
void handleNormalUser(int);
void handleLoggedInUser(int);
void handleInitialLogin(int);
void deleteAgentBookedTicket(int);
void viewAgentBookings(int);
void updateAgentBookings(int);

void showTrains(int nsd){
  int fd = open("database/trains.dat", O_RDWR , 0666);
  struct train temp;
  int stillRead = 1; //
  while(read(fd, &temp, sizeof(struct train))!=0){
      write(nsd, &stillRead,sizeof(stillRead));
      write(nsd, &temp, sizeof(struct train));
  }
  stillRead = 0;
  write(nsd, &stillRead,sizeof(stillRead));
}

void bookUserTicket(int nsd){
    showTrains(nsd);
    struct booking currBooking;
    read(nsd, &currBooking, sizeof(struct booking));
    // set booking id
    currBooking.bookingId = (rand()%3001) + 1000;
    currBooking.status = 1;
    int fd = open("database/trains.dat", O_RDWR);
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
    int flag = 1;

    int stillRead = 1; //
    while(read(fd, &temp, sizeof(struct booking))!=0){
      if(temp.userId == userBookings.userId){
        status = 1;
        if(status==1 && flag==1){
          write(nsd, &status, sizeof(status));
          flag = 10;
        }
        write(nsd, &stillRead,sizeof(stillRead));
        write(nsd, &temp, sizeof(struct booking));
      }
    }
    if(status==1){
      stillRead=0;
      write(nsd, &stillRead,sizeof(stillRead));
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

void deleteBookedTicket(int nsd){
    struct booking bookedTicket;
    struct booking temp;
    int status = 0;
    read(nsd, &bookedTicket, sizeof(struct booking));
    int fd = open("database/bookings.dat",O_RDWR);
    while(read(fd, &temp, sizeof(struct booking))!=0){
      if(temp.bookingId == bookedTicket.bookingId){
          temp.status = 0;
          lseek(fd, -sizeof(struct booking), SEEK_CUR);
          write(fd , &temp, sizeof(struct booking));
          status = 1;
          break;
      }
    }
    write(nsd, &status, sizeof(status));
    close(fd);
    handleLoggedInUser(nsd);
}

int updateTrainSeats(int nsd, int trainId, int seatsChange){
  int fd = open("database/trains.dat", O_RDWR);
  struct train tempTrain;
  int status = 0;
  while(read(fd, &tempTrain, sizeof(struct train))){
    if(tempTrain.trainId == trainId){
      if(tempTrain.seatsCount >= seatsChange){ // check for the trainId and Available seats
        tempTrain.seatsCount = tempTrain.seatsCount - seatsChange; // decrement the available seats
        lseek(fd, -sizeof(struct train), SEEK_CUR);
        write(fd , &tempTrain, sizeof(struct train));
        status = 1;
        break;
      }
    }
  }
  return status;
}

void updateUserBookings(int nsd){
    struct booking bookedTicket; // orignal
    struct booking temp; // new
    int status = 0;
    read(nsd, &bookedTicket, sizeof(struct booking));
    int fd = open("database/bookings.dat",O_RDWR);
    while(read(fd, &temp, sizeof(struct booking))!=0){
      if(temp.bookingId == bookedTicket.bookingId){
          int change = bookedTicket.seatsBooked - temp.seatsBooked;
          int trainId = temp.trainId;
          int canBook = updateTrainSeats(nsd, trainId, change);
          if(canBook==1){
            temp.seatsBooked = bookedTicket.seatsBooked;
            lseek(fd, -sizeof(struct booking), SEEK_CUR);
            write(fd , &temp, sizeof(struct booking));
            status = 1;
          }
          break;
      }
    }
    write(nsd, &status, sizeof(status));
    close(fd);
    handleLoggedInUser(nsd);
}

void handleLoggedInUser(int nsd){
  char ch[1];
  read(nsd,ch,sizeof(ch));
  if(ch[0]=='1'){ // book  a ticket
    bookUserTicket(nsd);
  }
  else if(ch[0]=='2'){ // delete a booked ticket
    deleteBookedTicket(nsd);
  }
  else if(ch[0]=='3'){ // view bookings
    viewUserBookings(nsd);
  }
  else if(ch[0]=='4'){ // update a booked ticket
    updateUserBookings(nsd);
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

void bookAgentTicket(int nsd){

  showTrains(nsd);
  struct booking currBooking;
  read(nsd, &currBooking, sizeof(struct booking));

  struct flock trainLock;
  struct flock bookingLock;

  // set booking id
  srand(time(0));
  currBooking.bookingId = (rand()%3001) + 1000;
  currBooking.status = 1;
  int fd = open("database/trains.dat", O_RDWR);
  struct train tempTrain;
  int status = 0;
  printf("FD: %d\n",fd);
  while(read(fd, &tempTrain, sizeof(struct train))){
    if(tempTrain.trainId == currBooking.trainId){
      if(tempTrain.seatsCount >= currBooking.seatsBooked){ // check for the trainId and Available seats
        // take lock on CS
        lseek(fd,-sizeof(struct train),SEEK_CUR);
				trainLock.l_type = F_WRLCK;
				trainLock.l_whence = SEEK_CUR;
				trainLock.l_start = 0;
				trainLock.l_len = sizeof(struct train);
        int ts = fcntl(fd, F_SETLK, &trainLock);

        bookingLock.l_type = F_WRLCK;
        bookingLock.l_whence = SEEK_SET;
        bookingLock.l_start = 0; // lock offset
        bookingLock.l_len = 0; // lock all bytes
        int fd1 = open("database/bookings.dat", O_CREAT | O_APPEND | O_RDWR , 0666);
        int bs = fcntl(fd1, F_SETLK, &bookingLock);
        if(ts!=-1 && bs!=-1 ){
          tempTrain.seatsCount = tempTrain.seatsCount - currBooking.seatsBooked; // decrement the available seats
          strcpy(currBooking.trainName,tempTrain.trainName);
          write(fd , (char *)&tempTrain, sizeof(struct train));
          status = 1;
          write(fd1, &currBooking, sizeof(struct booking));
          trainLock.l_type = F_UNLCK;
          bookingLock.l_type = F_UNLCK;
          fcntl(fd, F_SETLK, &trainLock);
          fcntl(fd1, F_SETLK, &bookingLock);
        }
        close(fd1);
        break;
      }
    }
  }
  write(nsd, &status, sizeof(status));
  close(fd);
  handleLoggedInUser(nsd);
}

void handleLoggedInAgent(int nsd){
  char ch[1];
  read(nsd,ch,sizeof(ch));

  if(ch[0]=='1'){ // book  a ticket
    bookAgentTicket(nsd);
  }
  else if(ch[0]=='2'){ // delete a booked ticket
    //deleteAgentBookedTicket(nsd);
  }
  else if(ch[0]=='3'){ // view bookings
    //viewAgentBookings(nsd);
  }
  else if(ch[0]=='4'){ // update a booked ticket
    //updateAgentBookings(nsd);
  }
}

int checkValidAgent(int nsd, char userName[], char password[]){
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

void handleAgentUser(int nsd){
  struct user currUser;
  read(nsd, &currUser, sizeof(struct user));
  int flag = checkValidAgent(nsd, currUser.userName, currUser.password);
  //
  int uid = flag;
  printf("%d\n",flag);
  write(nsd, &flag, sizeof(flag));
  if(flag){
    handleLoggedInAgent(nsd);
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
        lseek(fd, -sizeof(struct user), SEEK_CUR);
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
        lseek(fd, -sizeof(struct user), SEEK_CUR);
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
          tempTrain.status = 0;
          stat = 1;
          lseek(fd, -sizeof(struct train), SEEK_CUR);
          write(fd , &tempTrain, sizeof(struct train));
          break;
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
        lseek(fd, -sizeof(struct train), SEEK_CUR);
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
    handleAgentUser(nsd);
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
  char choice[1];
  read(nsd, choice, sizeof(choice));
  int flag = 0;
  if(choice[0]=='2'){
    flag = 1; // set flag as 1 for Agent signUp
  }
  struct user currUser;
  read(nsd, &currUser, sizeof(struct user));
  int status = 1;
  if(!checkUserExists(nsd, currUser.userName)){
      srand(time(0));
      int fd = open("database/users.dat", O_CREAT | O_APPEND | O_RDWR , 0666);
      currUser.status = 1;
      currUser.userId = ((rand()%3097)*2) + 1000;
      currUser.type = flag;
      write(fd, (char* )&currUser, sizeof(struct user));
  }
  else{
    status = -1;
  }
  write(nsd, &status, sizeof(status));
  handleInitialLogin(nsd);
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
