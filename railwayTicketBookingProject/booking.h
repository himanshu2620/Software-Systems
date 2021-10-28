struct booking{
  char userId[10];
  char trainId[10];
  char bookingId[10];
  char trainName[30];
  int seatsBooked;
  int status; // 1 for booked , 0 for cancelled
};
