typedef int bool;
#define true 1
#define false 0
#define STDIN_FILENO 0
#define FLAG_TESTMODE 1

typedef struct {
    float price1stHour;
    float priceNndHour;
    int   maxVehicles;
} configInfo;

typedef struct {
    char plate[7];
    time_t checkIn;
    time_t checkOut;
    float paid;
} reservationInfo;

typedef struct node {
  reservationInfo* val;
  struct node* left;
  struct node* right;
} reservationNode;
