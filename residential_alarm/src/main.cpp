#include <Arduino.h>
#include <LiquidCrystal.h>
#include <is_access_opened.hpp>

#define ALARME_PORTA_SALA A3
#define ALARME_JANELA_SALA A2
#define ALARME_PORTA_COZINHA A0
#define ALARME_JANELA_COZINHA A1
#define DESLIGA_ALARME_BUTTON 27
#define LIGA_ALARME_BUTTON 26
#define BUZZER 28
#define LED_PORTA_SALA 22
#define LED_JANELA_SALA 23
#define LED_PORTA_COZINHA 24
#define LED_JANELA_COZINHA 25
#define LED_ALARM_ON 30
#define LED_ALARM_OFF 29

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
unsigned long millisDisplay = millis();
unsigned long millisBuzzer = millis();

void ativarAlarme();
void desativarAlarme();
void dispararBuzzer();
void mostrarMensagemNoDisplay();
void welcome();

int ligaAlarmeLastState = 1;
int desligaAlarmeLastState = 1;
bool isOn = false;
bool buzzerIsPlaying = false;
String alarmesDisparando = "";
String oldAlarmesDisparando = "";
int i = 0;

void setup()
{
  pinMode(ALARME_JANELA_SALA, INPUT_PULLUP);
  pinMode(ALARME_PORTA_SALA, INPUT_PULLUP);
  pinMode(ALARME_PORTA_COZINHA, INPUT_PULLUP);
  pinMode(ALARME_JANELA_COZINHA, INPUT_PULLUP);
  pinMode(DESLIGA_ALARME_BUTTON, INPUT_PULLUP);
  pinMode(LIGA_ALARME_BUTTON, INPUT_PULLUP);
  lcd.begin(16, 2);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_PORTA_SALA, OUTPUT);
  pinMode(LED_JANELA_SALA, OUTPUT);
  pinMode(LED_PORTA_COZINHA, OUTPUT);
  pinMode(LED_JANELA_COZINHA, OUTPUT);
  pinMode(LED_ALARM_ON, OUTPUT);
  pinMode(LED_ALARM_OFF, OUTPUT);
  desativarAlarme();
  welcome();
}

void loop()
{
  if (buzzerIsPlaying)
  {
    if (i >= 180)
    {
      i = 0;
    }
    dispararBuzzer();
  }
  int ligaAlarme = digitalRead(LIGA_ALARME_BUTTON);
  if (ligaAlarme == 0 && ligaAlarmeLastState == 1)
  {
    ligaAlarmeLastState = 0;
    if (!isOn)
    {
      ativarAlarme();
      lcd.clear();
      oldAlarmesDisparando = "";
    }
    else
    {
      noTone(BUZZER);
      buzzerIsPlaying = false;
      oldAlarmesDisparando = "";
    }
  }
  else if (ligaAlarme == 1)
  {
    ligaAlarmeLastState = 1;
  }

  int desligaAlarme = digitalRead(DESLIGA_ALARME_BUTTON);
  if (desligaAlarme == 0 && desligaAlarmeLastState == 1)
  {
    desligaAlarmeLastState = 0;
    desativarAlarme();
  }
  else if (desligaAlarme == 1)
  {
    desligaAlarmeLastState = 1;
  }

  bool janelaSala = isAccessOpened(ALARME_JANELA_SALA);
  bool portaSala = isAccessOpened(ALARME_PORTA_SALA);
  bool janelaCozinha = isAccessOpened(ALARME_JANELA_COZINHA);
  bool portaCozinha = isAccessOpened(ALARME_PORTA_COZINHA);

  if (isOn)
  {
    alarmesDisparando = "";
    if (janelaSala)
    {
      // chamar função que liga o alarme da janela da Sala
      if (!buzzerIsPlaying)
      {
        buzzerIsPlaying = true;
        dispararBuzzer();
      }

      digitalWrite(LED_JANELA_SALA, HIGH);
      alarmesDisparando += " JANELA DA SALA,";
    }
    else
    {
      digitalWrite(LED_JANELA_SALA, LOW);
    }

    if (portaSala)
    {
      // chamar função que liga o alarme da porta da sala
      if (!buzzerIsPlaying)
      {
        buzzerIsPlaying = true;
        dispararBuzzer();
      }

      digitalWrite(LED_PORTA_SALA, HIGH);
      alarmesDisparando += " PORTA DA SALA,";
    }
    else
    {
      digitalWrite(LED_PORTA_SALA, LOW);
    }

    if (janelaCozinha)
    {
      // chamar função que liga o alarme da janela da Cozinha
      if (!buzzerIsPlaying)
      {
        buzzerIsPlaying = true;
        dispararBuzzer();
      }

      digitalWrite(LED_JANELA_COZINHA, HIGH);
      alarmesDisparando += " JANELA DA COZINHA,";
    }
    else
    {
      digitalWrite(LED_JANELA_COZINHA, LOW);
    }

    if (portaCozinha)
    {
      // chamar função que liga o alarme da janela da Cozinha
      if (!buzzerIsPlaying)
      {
        buzzerIsPlaying = true;
        dispararBuzzer();
      }

      digitalWrite(LED_PORTA_COZINHA, HIGH);
      alarmesDisparando += " PORTA DA COZINHA,";
    }
    else
    {
      digitalWrite(LED_PORTA_COZINHA, LOW);
    }
    if (alarmesDisparando != "")
    {
      alarmesDisparando.remove(alarmesDisparando.length() - 1);
    }
    mostrarMensagemNoDisplay();
  }
}

void ativarAlarme()
{
  isOn = true;
  digitalWrite(LED_ALARM_ON, HIGH);
  digitalWrite(LED_ALARM_OFF, LOW);
  digitalWrite(LED_JANELA_COZINHA, LOW);
  digitalWrite(LED_JANELA_SALA, LOW);
  digitalWrite(LED_PORTA_COZINHA, LOW);
  digitalWrite(LED_PORTA_SALA, LOW);
  tone(BUZZER, 450, 200); // LA
}
void desativarAlarme()
{
  isOn = false;
  buzzerIsPlaying = false;
  digitalWrite(LED_ALARM_ON, LOW);
  digitalWrite(LED_ALARM_OFF, HIGH);
  digitalWrite(LED_JANELA_COZINHA, LOW);
  digitalWrite(LED_JANELA_SALA, LOW);
  digitalWrite(LED_PORTA_COZINHA, LOW);
  digitalWrite(LED_PORTA_SALA, LOW);
  tone(BUZZER, 589, 200); // LA
  welcome();
}

void dispararBuzzer()
{
  float seno;
  int frequencia;
  if (buzzerIsPlaying)
  {
    if ((millis() - millisDisplay) > 5)
    {
      // converte graus para radiando e depois obtém o valor do seno
      seno = (sin(i * 3.1416 / 180));
      // gera uma frequência a partir do valor do seno
      frequencia = 2000 + (int(seno * 1000));
      tone(BUZZER, frequencia);
      millisDisplay = millis();
    }
    i++;
    if (i > 180)
      i = 0;
  }
}

void mostrarMensagemNoDisplay()
{
  if (alarmesDisparando == "")
  {
    if (oldAlarmesDisparando != "ok")
    {
      // Limpa a tela
      lcd.clear();

      if (buzzerIsPlaying)
      {
        lcd.setCursor(5, 0);
        lcd.print("ALARME");
        lcd.setCursor(3, 1);
        lcd.print("DISPARANDO");
      }
      else
      {
        lcd.setCursor(1, 0);
        lcd.print("ALARME LIGADO!");
        lcd.setCursor(2, 1);
        lcd.print("TUDO FECHADO");
      }

      oldAlarmesDisparando = "ok";
    }
  }
  else
  {
    if (oldAlarmesDisparando != alarmesDisparando)
    {
      oldAlarmesDisparando = alarmesDisparando;

      // Limpa a tela
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print(alarmesDisparando);
    }

    // Rolagem para a esquerda
    if ((millis() - millisDisplay) > 500)
    {
      lcd.scrollDisplayLeft();
      millisDisplay = millis();
    }
  }
}

void welcome()
{
  // Limpa a tela
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("ALARME");
  lcd.setCursor(2, 1);
  lcd.print("RESIDENCIAL!");
}