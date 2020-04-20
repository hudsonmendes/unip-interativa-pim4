/* inclusoes ================================================================ */
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 
#include "helpers.h"
#include "db.h"

/* rotinas ================================================================== */
void printCheckIn(char* plate, char* checkinDateAsString, float tariff1stHour, float tariffNndHour) {
    time_t printDate;
    char printDateAsString[20];
    getDate(printDateAsString, &printDate);
    
    clear();
    breakLine();
    breakLine();
    
    printf("                ======================================== \n");
    printf("               |        ESTACIONAMENTO PIM4/2014        |\n");
    printf("               |========================================|\n");
    printf("               |                VEICULO                 |\n");
    printf("               | -------------------------------------- |\n");
    printf("               |  IMPRESSAO: %-19s        |\n", printDateAsString);
    printf("               |  ENTRADA  : %-19s        |\n", checkinDateAsString);
    printf("               |    PLACA  : %-7s                    |\n", plate);
    printf("               |                                        |\n");
    printf("               | -------------------------------------- |\n");
    printf("               |                  PRECOS                |\n");
    printf("               | -------------------------------------- |\n");
    printf("               |       1a HORA: R$ %6.2f               |\n", tariff1stHour);
    printf("               |  DEMAIS HORAS: R$ %6.2f               |\n", tariffNndHour);
    printf("               |                                        |\n");
    printf("               | -------------------------------------- |\n");
    printf("               |              IMPORTANTE                |\n");
    printf("               | -------------------------------------- |\n");
    printf("               |  O ESTACIONAMENTO PIM4/2014 NAO SE     |\n");
    printf("               |  RESPONSABILIZA POR ITENS DE VALOR     |\n");
    printf("               |  DEIXADOS NO INTERIOR DO VEICULO.      |\n");
    printf("               |                                        |\n");
    printf("                ======================================== \n");
    breakLine();
    breakLine();
    
    pause();
}

void printCheckOut(char* plate, char* checkinDateAsString, char* checkoutDateAsString, float tariff1stHour, float tariffNndHour, int totalHours, float paidValue) {
    time_t printDate;
    char printDateAsString[20];
    getDate(printDateAsString, &printDate);
    
    clear();
    breakLine();
    breakLine();
    
    printf("                ======================================== \n");
    printf("               |        ESTACIONAMENTO PIM4/2014        |\n");
    printf("               |========================================|\n");
    printf("               |                VEICULO                 |\n");
    printf("               | -------------------------------------- |\n");
    printf("               |    PLACA  : %-7s                    |\n", plate);
    printf("               |                                        |\n");
    printf("               |  IMPRESSAO: %-19s        |\n", printDateAsString);
    printf("               |    ENTRADA: %-19s        |\n", checkinDateAsString);
    printf("               |      SAIDA: %-19s        |\n", checkoutDateAsString);
    printf("               |                                        |\n");
    printf("               | -------------------------------------- |\n");
    printf("               |                  PRECOS                |\n");
    printf("               | -------------------------------------- |\n");
    printf("               |       1a HORA: R$ %6.2f               |\n", tariff1stHour);
    printf("               |  DEMAIS HORAS: R$ %6.2f               |\n", tariffNndHour);
    printf("               |                                        |\n");
    printf("               |  HORAS TOTAIS: %6d horas            |\n", totalHours);
    printf("               |    TOTAL PAGO: R$ %6.2f               |\n", paidValue);
    printf("               |                                        |\n");
    printf("               | -------------------------------------- |\n");
    printf("               |              AGRADECIMENTO             |\n");
    printf("               | -------------------------------------- |\n");
    printf("               |  AGRADECEMOS A PREFERENCIA.            |\n");
    printf("               |  TENHA UMA BOA VIAGEM E CONTE CONOSCO  |\n");
    printf("               |  SEMPRE QUE PRECISAR!                  |\n");
    printf("               |                                        |\n");
    printf("                ======================================== \n");
    breakLine();
    breakLine();
    
    pause();
}

void printList() {
    clear();
    breakLine();
    
    int i, totalCount = reservationsCount();
    reservationInfo* reservations[totalCount];
    loadReservations(reservations);
    
    printf(" =================================================================== \n");
    printf("|                 RELATORIO GERAL DO ESTACIONAMENTO                 |\n");
    printf("|===================================================================|\n");
    printf("| PLACA   | ENTRADA              | SAIDA                |  VALOR    |\n");
    printf("|===================================================================|\n");
    
    for (i = 0; i < totalCount; i++) {
      reservationInfo* reservation = reservations[i];
      
      char* checkinAsString = (char*) malloc(20 * sizeof(char) + 1);
      formatDate(&reservation->checkIn, checkinAsString);
      
      char* checkoutAsString = "(estacionado)";
      if (reservation->checkOut != 0) {
        checkoutAsString = (char*) malloc(20 * sizeof(char) + 1);
        formatDate(&reservation->checkOut, checkoutAsString);
      }
      
      float paidValue = 0.00;
      if (reservation->paid != 0.00) {
        paidValue = reservation->paid;
      }
      
      printf(
        "| %-7s | %-20s | %-20s | R$ %6.2f |\n",
        reservation->plate,
        checkinAsString,
        checkoutAsString,
        paidValue);
    }
    
    printf(" =================================================================== \n");
    breakLine();
    pause();
}
