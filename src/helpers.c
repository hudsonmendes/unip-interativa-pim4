/* inclusoes ================================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helpers.h"

/* rotinas ================================================================== */
int parkingHours(time_t checkin, time_t checkout) {
    int totalMinutes = 0, totalHours = 0;
    int totalSeconds = difftime(checkout, checkin);
    
    totalMinutes = totalSeconds / 60;
    totalHours = totalMinutes / 60; // 1h = 60min = 60seg
    
    /***********************************************************************
     * REGRA DE HORAS PARA COBRANÇA
     * ----------------------------
     * 1) Temos uma tolerancia de 15 minutos
     *
     * 2) Caso tenha vencido a tolerância, nós cobramos a "hora" pra cada
     *    hora que tenha sido iniciada, não para cada hora completa. Portanto
     *    sempre somamos +1 para o total de horas.
     *
     ***********************************************************************/
    if (totalHours == 0 && totalMinutes <= 15) {
        return 0;
    }
    
    totalHours += 1;
    return totalHours;
}

float parkingPayment(configInfo config, int totalHours) {
    /***********************************************************************
     * REGRA DE VALOR DE COBRANÇA
     * ----------------------------
     * 1) Para a 1a hora nós cobraremos uma tarifa diferente das demais
     * 2) Os valores são definidos via interface de configuração
     ***********************************************************************/
    bool hasFirstHour = totalHours >= 1;
    bool hasMoreThan1Hour = totalHours > 1;

    float totalPayment = 0.00;
    if (hasFirstHour) {
        totalPayment += config.price1stHour;
    }

    if (hasMoreThan1Hour) {
        int additionalHours = totalHours - 1;
        totalPayment += (additionalHours * config.priceNndHour);
    }
    
    return totalPayment;
}

bool checkLockOut(configInfo config, int current) {
    /***********************************************************************
     * REGRA DE BLOQUEIO
     * ----------------------------
     * 1) Quando o estacionamento alcancar seu limite, ele nao deve mais
     *    permitir que novos veiculos deem entrada
     *
     * 2) Alem disso os usuarios do sistema tem que ser avisados que o
     *    estacionamento alcancou seu limite.
     ***********************************************************************/
     int max = config.maxVehicles;
     return current >= max;
}

void pause() {
#ifdef _WIN32
    system("pause");
#else
    printf("Pressione [ENTER] para continuar...\n");
    char c = 0;
    while (c != '\n' && c != '\r') { 
        c = getch(); 
    }
    breakLine();
#endif
}

void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void breakLine() {
    printf("\n");
}

void getDate(char* dateAsString, time_t* now) {
    getDateExt(dateAsString, now, false);
}

void getDateExt(char* dateAsString, time_t* now, bool isCheckout) {
    *now = time(NULL);
    
    if (isCheckout && FLAG_TESTMODE) {
        int r = rand() % 10000;
        *now += r;
    }
    
    strftime(dateAsString, 20, "%d/%m/%Y %H:%M:%S", localtime(now));
}

void formatDate(time_t* time, char* dateAsString) {
    strftime(dateAsString, 20, "%d/%m/%Y %H:%M:%S", localtime(time));
}

#ifdef _WIN32
#else
char getch(void) {
    char c = getchar();
    if (c == EOF || c == '\n') {
        c = getchar();
    }
    
    return c;
}
#endif
