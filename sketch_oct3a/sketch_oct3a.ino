int BotaoPin = 7;
int BotaoPin2 = 6;
int LedPin = 10;
int LedPin2 = 9;
int BuzzerPin = 8; // Pino para o buzzer
int estadobotao = 0;
int estadobotao2 = 0;
bool buzzerAtivo1 = false; // Variável para o botão 1
bool buzzerAtivo2 = false; // Variável para o botão 2

void setup() {
  // Configura os pinos
  pinMode(BotaoPin, INPUT);
  pinMode(BotaoPin2, INPUT);
  pinMode(LedPin, OUTPUT);
  pinMode(LedPin2, OUTPUT);
  pinMode(BuzzerPin, OUTPUT); // Configura o pino do buzzer como saída
  Serial.begin(9600); 
}

void loop() {
  // Lê o estado do primeiro botão
  estadobotao = digitalRead(BotaoPin);
  Serial.print("Botao1: ");
  Serial.print(estadobotao); 
  Serial.print(" | ");

  // Controla o primeiro LED e o buzzer
  if (estadobotao == 0) {
    digitalWrite(LedPin, HIGH);
    if (!buzzerAtivo1) { // Se o buzzer do botão 1 ainda não foi ativado
      tone(BuzzerPin, 4000); // Toca o buzzer a 4000 Hz
      delay(200); // Duração do bip
      noTone(BuzzerPin); // Para o som do buzzer
      buzzerAtivo1 = true; // Marca que o buzzer foi ativado
    }
  } else {
    digitalWrite(LedPin, LOW);
    buzzerAtivo1 = false; // Permite que o buzzer seja acionado novamente
  }

  // Lê o estado do segundo botão
  estadobotao2 = digitalRead(BotaoPin2);
  Serial.print("Botao2: ");
  Serial.println(estadobotao2);

  // Controla o segundo LED e o buzzer
  if (estadobotao2 == 0) {
    digitalWrite(LedPin2, HIGH);
    if (!buzzerAtivo2) { 
      tone(BuzzerPin, 4000); 
      delay(200);
      noTone(BuzzerPin); 
      buzzerAtivo2 = true; 
    }
  } else {
    digitalWrite(LedPin2, LOW);
    buzzerAtivo2 = false; 
  }

  delay(50); 
}