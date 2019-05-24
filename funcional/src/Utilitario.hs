module Utilitario
  ( lerEntradaObrigatoria
  , escolhaSimNao
  , exibeEscolhaSimNao
  , exibeMensagem
  , exibeTopoMenu
  , validaNumeroPositivo
  , validaOpcao
  ) where

lerEntradaObrigatoria :: String -> IO String
lerEntradaObrigatoria campo = do
  putStrLn campo
  entrada <- getLine
  entradaValidada <- validaEntradaVazia entrada campo
  return (entradaValidada)

validaEntradaVazia :: String -> String -> IO String
validaEntradaVazia entrada campo
  | entrada == "" = do
    putStrLn "Campo obrigatorio! Tente novamente. "
    putStrLn campo
    novaEntrada <- getLine
    validaEntradaVazia novaEntrada campo
  | otherwise = return entrada

-- Atraves da escolha (S) ou (N ou qualquer entrada invalida) sera 1 e  0 respectativamente
escolhaSimNao :: String -> Int
escolhaSimNao escolha
  | escolha == "s" || escolha == "S" = 1
  | otherwise = 0

-- Exibe em formato "S" caso 1 e "N" caso 0.
exibeEscolhaSimNao :: Int -> String
exibeEscolhaSimNao escolha
  | escolha == 1 = "S"
  | otherwise = "N"

-- Exibe a estrutura padrao de mensagens do sistema.
exibeMensagem :: String -> IO ()
exibeMensagem mensagem = putStrLn ("--- " ++ mensagem ++ " ---")

-- Exibe o topo padrao do menu.
exibeTopoMenu :: String -> IO ()
exibeTopoMenu titulo = do
  putStrLn " .::. PrompSkoob .::."
  putStrLn (" - " ++ titulo ++ " - ")
  putStrLn ""

validaOpcao :: String -> Int -> Int -> Int -> IO Int
validaOpcao campo opcao minimo maximo = do
  if (opcao < minimo || opcao > maximo)
    then do
      putStrLn "Opcao Invalida! Tente novamente."
      putStrLn campo
      opcao <- readLn :: IO Int
      validaOpcao campo opcao minimo maximo
    else return (opcao)

validaNumeroPositivo :: String -> Int -> IO Int
validaNumeroPositivo campo valor = do
  if (valor <= 0)
    then do
      putStrLn "Valor Invalido! Tente novamente."
      putStrLn campo
      valor <- readLn :: IO Int
      validaNumeroPositivo campo valor
    else return (valor)
