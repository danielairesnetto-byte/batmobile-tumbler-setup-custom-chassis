//===========================================
//    BATMOVEL TUMBLER SYSTEM 
//===========================================

// Blibiotecas
#include <Arduino.h>
#include "BluetoothSerial.h"

// Cria o objeto para controlar o Bluetooth
BluetoothSerial Control_Connection;

// Definir nomes amigaveis para os nossos pinos
const int FRONT_HEADLIGHT = 4; const int BACK_LIGHT = 15;
const int INT1 = 26; const int INT2 = 27;
const int INT3 = 14; const int INT4 = 12;

// Variáveis de Tempo do Pisca Dianteiro
unsigned long tempoAnteriorFrente = 0;
const long intervaloFrente = 500; 
bool estadoFrente = LOW;
bool piscaFrenteAtivo = false;     

// Variáveis de Tempo do Pisca Traseiro
unsigned long tempoAnteriorTras = 0;
const long intervaloTras = 1000;  
bool estadoTras = LOW;
bool piscaTrasAtivo = false;     

// Functions
void moverFrente() {
   digitalWrite(INT1, LOW);
   digitalWrite(INT2, HIGH);
   digitalWrite(INT3, LOW);
   digitalWrite(INT4, HIGH);
}

void moverTras() {
   digitalWrite(INT1, HIGH);
   digitalWrite(INT2, LOW);
   digitalWrite(INT3, HIGH);
   digitalWrite(INT4, LOW);
}

void moverDireita() {
   digitalWrite(INT1, LOW);
   digitalWrite(INT2, HIGH);
   digitalWrite(INT3, HIGH);
   digitalWrite(INT4, LOW);
}

void moverEsquerda() {
   digitalWrite(INT1, HIGH);
   digitalWrite(INT2, LOW);
   digitalWrite(INT3, LOW);
   digitalWrite(INT4, HIGH);
}

void acenderLuzesDianteiras() {
   digitalWrite(FRONT_HEADLIGHT, HIGH);
}

void acenderLuzesTraseiras() {
   digitalWrite(BACK_LIGHT, HIGH);
}

void checarPiscaFrente() {
    unsigned long tempoAtual = millis();
    if (tempoAtual - tempoAnteriorFrente >= intervaloFrente) {
        tempoAnteriorFrente = tempoAtual;
        estadoFrente = !estadoFrente;
        digitalWrite(FRONT_HEADLIGHT, estadoFrente);
    }
}

void checarPiscaTras() {
    unsigned long tempoAtual = millis();
    if (tempoAtual - tempoAnteriorTras >= intervaloTras) {
        tempoAnteriorTras = tempoAtual;
        estadoTras = !estadoTras;
        digitalWrite(BACK_LIGHT, estadoTras);
    }
}

void desligarLuzesDianteiras() {
   piscaFrenteAtivo = false;
   digitalWrite(FRONT_HEADLIGHT, LOW);
}

void desligarLuzesTraseiras() {
   piscaTrasAtivo = false;
   digitalWrite(BACK_LIGHT, LOW);
}

void parar() {
    digitalWrite(INT1, LOW);
    digitalWrite(INT2, LOW); 
    digitalWrite(INT3, LOW); 
    digitalWrite(INT4, LOW); 
}

void setup() {
   // Inicializa a comunicação Bluetooth com o nome visível
    Control_Connection.begin("Dark_Knight");  // Ou virus.EXE se voce quiser que ninguem roube a sua conexão

   // Configuração inicial: Definir pinos como OUTPUT e LOW
   pinMode(FRONT_HEADLIGHT, OUTPUT); digitalWrite(FRONT_HEADLIGHT, LOW);
   pinMode(BACK_LIGHT, OUTPUT); digitalWrite(BACK_LIGHT, LOW);
   pinMode(INT1, OUTPUT); digitalWrite(INT1, LOW);
   pinMode(INT2, OUTPUT); digitalWrite(INT2, LOW);
   pinMode(INT3, OUTPUT); digitalWrite(INT3, LOW);
   pinMode(INT4, OUTPUT); digitalWrite(INT4, LOW);
}

void loop() {
   // Processa dados enviados pelo usuario
   if (Control_Connection.available()) {
      char comando = Control_Connection.read();
      switch (comando) {
      case '1':
         moverFrente();
         break;
      case '2':
         moverEsquerda();
         break;
      case '3':
         moverTras();
         break;
      case '4':
         moverDireita();
         break;
      case '5':
         acenderLuzesDianteiras();
         break;
      case '6':
         acenderLuzesTraseiras();
         break;
      case '7':
         piscaFrenteAtivo = true;
         break;
      case '8':
         piscaTrasAtivo = true;
         break;
      case '9':
         desligarLuzesDianteiras();
         break;
      case 'A':
         desligarLuzesTraseiras();
         break;
      case 'B':
         parar();
         break;
      }
   }

   // Roda a checagem dos piscas continuamente no tempo
   if (piscaFrenteAtivo) {
      checarPiscaFrente();
   }
   if (piscaTrasAtivo) {
       checarPiscaTras();
   }
}
// =========================================================================
// 🚀 PROJETO: BATMOVEL TUMBLER SYSTEM
// 👨‍💻 DESENVOLVEDOR: Daniel Aires Netto
// =========================================================================
/*
   📌 NOTA DO AUTOR:
   Este projeto deu tempo e trabalho para ser desenvolvido, e calibrado!
   Se este código te ajudou de alguma forma, o seu apoio e feedback na rede
   são imensamente valiosos para eu continuar inovando, e eu sei, foi extremamente
   sem graça eu não ter colocado nenhum som mais o que você queria no carro do Batman.

   💬 SUPORTE & CONTATO:
   Tem alguma dúvida ou sugestão de melhoria? Deixe nos comentários ou 
   conecte-se comigo. Farei o possível para responder e ajudar!
   Sinta-se totalmente livre para modificar e adaptar o código para o seu projeto.

   🔗 MEU PERFIL:
   Confira mais projetos de Engenharia/Mecatrônica no meu LinkedIn:
   👉 (https://www.linkedin.com/in/daniel-aires-netto-4034b13bb?utm_source=share_via&utm_content=profile&utm_medium=member_android)
*/
// ===============================================================