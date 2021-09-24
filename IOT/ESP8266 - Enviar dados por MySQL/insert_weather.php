<?php
$temp = filter_input(INPUT_GET, 'temp', FILTER_SANITIZE_NUMBER_FLOAT); //variaveis da firmware esp8266
$humid = filter_input(INPUT_GET, 'humid', FILTER_SANITIZE_NUMBER_FLOAT); //variaveis da firmware esp8266
 

if (is_null($temp) || is_null($humid) ) {
  //Gravar log de erros
  die("Dados inválidos");
} 
$servername = "localhost";
$username = "XXXXXXX"; //usuario do banco
$password = "XXXXXXX"; //senha do banco
$dbname = "XXXXXXX"; // nome do banco 
$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
  //Gravar log de erros
  die("Não foi possível estabelecer conexão com o BD: " . $conn->connect_error);
} 
$sql = "INSERT INTO projetopi.weather (wea_temp, wea_humid) VALUES ($temp,$humid)"; //INSERT INTO (NOME DO BANCO) . (TABELA) (NOME DA COLUNA NO BANCO) E (PARAMETRO PHP)

if (!$conn->query($sql)) {
  //Gravar log de erros
  die("Erro na gravação dos dados no BD");
}
$conn->close();
?>
