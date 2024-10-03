const SerialPort = require('serialport').SerialPort;
const { ReadlineParser } = require('@serialport/parser-readline');
const express = require('express');
const app = express();

// Lista todas as portas disponíveis
SerialPort.list().then(
  ports => ports.forEach(port => {
    console.log(`Porta: ${port.path}`);
    console.log(`Fabricante: ${port.manufacturer}`);
    console.log('--------------------');
  }),
  err => console.error('Erro ao listar portas: ', err)
);

// Defina o caminho correto da porta COM
const port = new SerialPort({ path: 'COM3', baudRate: 9600 }); // Substitua 'COM3' pela porta correta
const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

let arduinoData = { botao1: 0, botao2: 0 };

// Lê os dados do Arduino
parser.on('data', (data) => {
  console.log('Dados recebidos do Arduino:', data);
  const [botao1, botao2] = data.split(' | ').map(d => d.split(': ')[1]);
  arduinoData.botao1 = parseInt(botao1);
  arduinoData.botao2 = parseInt(botao2);
});

// Rota que envia os dados para o site
app.get('/dados', (req, res) => {
  res.json(arduinoData);
});

// Servidor web ouvindo na porta 3000
app.listen(3000, () => {
  console.log('Servidor ouvindo na porta 3000');
});
