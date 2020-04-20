/* inclusoes ================================================================ */
#include <stdio.h>
#include "helpers.h"
#include "db.h"

/* declaracoes ============================================================== */
int main();
void runMenu();
void fetchOption(char*);
void processOption(configInfo*, char, bool*);

/* rotinas ================================================================== */
int main() {
  runMenu();
}

void runMenu() {
    /*--------------------------------------
    MENU DA APLICACAO
    ---------------------------------------
    1) Configuracao da Aplicacao (Tarifas)
    2) Entrada de Veiculos
    3) Saida de Veiculos
    ---------------------------------------
    4) Encerrar a aplicacao
    --------------------------------------- */

    char rawOption = '0';
    bool shouldRepeat = true;
    
    configInfo config;
    config.maxVehicles = 0;
    config.price1stHour = 0.00;
    config.priceNndHour = 0.00;
    
    screenLogo(config);
    screenSetup(&config);
    
    while (shouldRepeat != false) {
        screenLogo(config);
        screenMain(config);
        fetchOption(&rawOption);
        processOption(&config, rawOption, &shouldRepeat);
    }
}

void fetchOption(char* rawOption) {
    printf("Escolha a opcao: ");
    *rawOption = getch();
}

void processOption(configInfo* config, char rawOption, bool* shouldRepeat) {
    switch (rawOption) {
        case '1':
            screenLogo(*config);
            screenSetup(config);
            *shouldRepeat = true;
            break;
            
        case '2':
            screenLogo(*config);
            if (!checkLockOut(*config, reservationsCount())) {
              screenCheckIn(*config);
            }
            else {
              screenLockOut();
            }
            *shouldRepeat = true;
            break;
            
        case '3':
            screenLogo(*config);
            screenCheckOut(*config);
            *shouldRepeat = true;
            break;
            
        case '4':
            screenLogo(*config);
            screenList();
            *shouldRepeat = true;
            break;
    
        case '5':
            screenGoodbye();
            *shouldRepeat = false;
            return;

        default:
            *shouldRepeat = true;
            break;
    }
}
