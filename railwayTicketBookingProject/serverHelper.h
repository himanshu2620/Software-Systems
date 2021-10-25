
char welcomeMenu[] = "Login as:\n1.Normal Account User\n2.Agent Account User\n3.Administrator\n4.Exit\nPlease enter your choice:";
char normalUserPrompt[] = "Press:\n1 for Booking a Ticket\n2 for Viewing Previous Bookings\n3 for Updating a Booking\n4 to cancel a booking\n0 to exit";
char trainIdInputMsg[] = "Enter the trainId of the train to book the seat";
char seatsInputMsg[] = "Enter the number of seats to be booked";




void handleNormalUser(int nsd){
  write(nsd, normalUserPrompt, sizeof(normalUserPrompt)); // show the prompt
  char ch[1];
  read(nsd,ch,sizeof(ch));
  if(ch[0]=='1'){
    // book  a ticket

    // take input for trainId
    write(nsd,trainIdInputMsg,sizeof(trainIdInputMsg));
    char inputTrainId[10];
    read(nsd,inputTrainId,sizeof(inputTrainId));

    // take input for number of seats to be booked
    write(nsd,seatsInputMsg,sizeof(seatsInputMsg));
    char buff[10];
    read(nsd,buff,sizeof(buff));
    int seatsToBeBooked = atoi(buff);
  }
}

void handleInitialLogin(int nsd){
    write(nsd, welcomeMenu, sizeof(welcomeMenu));
    //sleep(0.01);
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
    }
    else{
      printf("exitting the system now...\n");
    }
}
