#include <Arduino.h>
#include <is_access_opened.hpp>
#define ALARME_PORTA_SALA 2
#define ALARME_JANELA_SALA 3
#define ALARME_PORTA_COZINHA 4
#define ALARME_JANELA_COZINHA 5
#define DESLIGA_ALARME 13
#define LIGA_ALARME 12

void ativarAlarme();
void desativarAlarme();

void setup()
{
  pinMode(ALARME_JANELA_SALA, INPUT_PULLUP);
  pinMode(ALARME_PORTA_SALA, INPUT_PULLUP);
  pinMode(ALARME_PORTA_COZINHA, INPUT_PULLUP);
  pinMode(ALARME_JANELA_COZINHA, INPUT_PULLUP);
  pinMode(DESLIGA_ALARME, INPUT_PULLUP);
  pinMode(LIGA_ALARME, INPUT_PULLUP);
}

int ligaAlarmeLastState = 1;
int desligaAlarmeLastState = 1;
bool isOn = false;

void loop()
{
  int ligaAlarme = digitalRead(LIGA_ALARME);
  if (ligaAlarme == 0 && ligaAlarmeLastState == 1)
  {
    ligaAlarmeLastState = 0;
    ativarAlarme();
  }
  else if (ligaAlarme == 1)
  {
    ligaAlarmeLastState = 1;
  }
  int desligaAlarme = digitalRead(DESLIGA_ALARME);
  if (desligaAlarme == 0 && desligaAlarmeLastState == 1)
  {
    desligaAlarmeLastState = 0;
    desativarAlarme();
  }
  else if (ligaAlarme == 1)
  {
    desligaAlarmeLastState = 1;
  }

  bool janelaSala = isAccessOpened(ALARME_JANELA_SALA);
  bool portaSala = isAccessOpened(ALARME_PORTA_SALA);
  bool janelaCozinha = isAccessOpened(ALARME_JANELA_COZINHA);
  bool portaCozinha = isAccessOpened(ALARME_PORTA_COZINHA);
  if (isOn)
  {
    if (janelaSala)
    {
      // chamar função que liga o alarme da janela da Sala
    }
    else
    {
      // chamar função que desliga alarme da janela da da sala
    }

    if (portaSala)
    {
      // chamar função que liga o alarme da porta da sala
    }
    else
    {
      // chamar função que desliga alarme da janela da sala
    }


    if (janelaCozinha)
    {
      // chamar função que liga o alarme da janela da Cozinha
    }
    else
    {
      // chamar função que desliga alarme da janela da Cozinha
    }
    
    if (portaCozinha)
    {
      // chamar função que liga o alarme da janela da Cozinha
    }
    else
    {
      // chamar função que desliga alarme da janela da Cozinha
    }
  }
}

void ativarAlarme()
{
  isOn = true;
}
void desativarAlarme()
{
  isOn = false;
}