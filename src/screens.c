/* inclusoes ================================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "printer.h"
#include "db.h"

/* rotinas ================================================================== */
void screenLogo(configInfo config) {
    int positionsTaken = reservationsActiveCount();
    
    clear();
    printf("====================================================================\n");
    printf("               SISTEMA DE GESTAO DE ESTACIONAMENTO                  \n");
    printf("            Hudson Mendes (1443030), UNIP PIM4/2014                 \n");
    printf("====================================================================\n");
    printf(" CONFIGURACOES DO ESTACIONAMENTO\n");
    printf(" - MAXIMO DE VAGAS: %i veiculos utilitarios\n", config.maxVehicles);
    printf(" - HORA INICIAL   : R$ %5.2f\n", config.price1stHour);
    printf(" - DEMAIS HORAS   : R$ %5.2f\n", config.priceNndHour);
    printf("====================================================================\n");
    printf("                                       VAGAS OCUPADAS: %3d de %3d \n", positionsTaken, config.maxVehicles);
    printf("====================================================================\n");
}

void screenMain() {
    breakLine();
    printf("MENU DO SISTEMA\n");
    breakLine();
    printf("[1] Configuracoes do Sistema\n");
    printf("[2] Entrada de carro\n");
    printf("[3] Saida de carro\n");
    printf("[4] Relatorio geral\n");
    printf("[5] Encerrar o sistema\n");
    breakLine();
}

void screenGoodbye() {
    breakLine();
    printf("Obrigado por usar o SISTEMA DE GESTAO DE ESTACIONAMENTOS\n");
    printf("Foi um prazer atende-lo.\n");
    printf("Esperamos ve-lo novamente em breve!\n");
    breakLine();
    pause();
}

void screenLockOut() {
    breakLine();
    printf(">>>>>>>>>> ESTACIONAMENTO CHEIO <<<<<<<<<<<<\n");
    printf("O ESTACIONAMENTO alcancou seu limite e nao\n");
    printf("pode mais comportar veiculos.\n");
    breakLine();
    printf("Por favor, aguarde ate que carros saiam para\n");
    printf("permitir a entrada de mais carros.\n");
    printf("============================================\n");
    breakLine();
    pause();
}

void screenSetup(configInfo* config) {
     breakLine();
     printf("CONFIGURACAO\n");
     printf("- Total de Vagas     : ");
     scanf("%d", &config->maxVehicles);
     printf("- Tarifa 1a hora     : ");
     scanf("%f", &config->price1stHour);
     printf("- Tarifa DEMAIS horas: ");
     scanf("%f", &config->priceNndHour);
     
     breakLine();
     
     printf("[GRAVACAO]\n");
     printf("- Sucesso!\n");
     
     breakLine();
     pause();
}

void screenCheckIn(configInfo config) {
    char* plate = (char*) malloc(7 * sizeof(char) + 1);
    char* checkinDateAsString = (char*) malloc(20 * sizeof(char) + 1);
    time_t checkInDate;
    
    getDate(checkinDateAsString, &checkInDate);
    
    breakLine();
    printf("ENTRADA DE CARRO\n");
    printf("- Horario da Entrada : ");
    printf("%-20s\n", checkinDateAsString);
    printf("- Placa do Carro     : ");
    scanf("%s", plate);
    
    bool reservationFound = false;
    reservationInfo* reservation;
    findReservation(&reservation, plate, &reservationFound);
    if (reservationFound) {
      printf("- Veiculo PLACA '%s' ja esta no estacionamento.\n", plate);
      pause();
      breakLine();
      return;
    }
    
    reservation = (reservationInfo*) malloc(sizeof(reservationInfo));
    reservation->checkIn = checkInDate;
    reservation->checkOut = 0;
    reservation->paid = 0.00;
    strcpy(reservation->plate, plate);
    appendReservation(reservation);
    
    printf("- Imprimir RECIBO? ([S]im ou [N]ao): ");
    char shouldPrint = getch();
    if (shouldPrint == 'S' || shouldPrint == 's') {
        printCheckIn(
            plate,
            checkinDateAsString,
            config.price1stHour,
            config.priceNndHour);
    }
}

void screenCheckOut(configInfo config) {
    char* plate = (char*) malloc(7 * sizeof(char) + 1);
    char* checkinDateAsString = (char*) malloc(20 * sizeof(char) + 1);
    char* checkoutDateAsString = (char*) malloc(20 * sizeof(char) + 1);
    time_t checkoutDate;
    int totalHours;
    float totalPayment;
    reservationInfo* reservation;
    bool reservationFound;
    
    breakLine();
    printf("SAIDA DE CARRO\n");
    printf("- Placa do Carro         : ");
    scanf("%s", plate);
    
    findReservation(&reservation, plate, &reservationFound);

    if (reservationFound == false) {
        printf("- Veiculo PLACA '%s' não foi encotrado.\n", plate);
        breakLine();
        pause();
        return;
    }
    else {
        printf("  (Ok, veiculo com placa '%s' encontrado)!\n", plate);
        breakLine();
        
        formatDate(&reservation->checkIn, checkinDateAsString);
        printf("- Horario da Entrada     : ");
        printf("%-20s\n", checkinDateAsString);
        
        getDateExt(checkoutDateAsString, &checkoutDate, true);
        reservation->checkOut = checkoutDate;
        printf("- Horario da Saida       : ");
        printf("%-20s\n", checkoutDateAsString);
        
        totalHours = parkingHours(reservation->checkIn, reservation->checkOut);
        printf("- Horas no Estacionamento: ");
        printf("%3d horas\n", totalHours);
        
        breakLine();
        totalPayment = parkingPayment(config, totalHours);
        reservation->paid = totalPayment;
        printf("- VALOR TOTAL A PAGAR    : ");
        printf("R$ %6.2f\n", totalPayment);
        breakLine();
        
        releaseReservation();
    }
    
    printf("- Imprimir COMPROVANTE? ([S]im ou [N]ao): ");
    char shouldPrint = getch();
    if (shouldPrint == 'S' || shouldPrint == 's') {
        printCheckOut(
            plate,
            checkinDateAsString,
            checkoutDateAsString,
            config.price1stHour,
            config.priceNndHour,
            totalHours,
            totalPayment);
    }
}

void screenList() {
    printList();
}
