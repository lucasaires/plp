module UsuarioCtrl
  ( autenticarUsuario
  , cadastrarUsuario
  , editarUsuario
  , removerUsuario
  ) where

import           EstanteType
import           UsuarioDB
import           Utilitario

-- Exibe a interface para autenticacao e verifica credenciais no banco.
autenticarUsuario :: IO Usuario
autenticarUsuario = do
  exibeTopoMenu "Autenticacao"
  email <- lerEntradaObrigatoria "E-mail: "
  senha <- lerEntradaObrigatoria "Senha: "
  putStrLn ""
  usuario <- autenticaUsuario email senha
  return (usuario)

-- Cadastra um usuario no sistema.
cadastrarUsuario :: IO Bool
cadastrarUsuario = do
  exibeTopoMenu "Quero me Cadastrar"
  nomeUsuario <- lerEntradaObrigatoria "Nome: "
  emailUsuario <- lerEntradaObrigatoria "Email: "
  emailUsuario <- validaEmail emailUsuario "Email: "
  senhaUsuario <- lerEntradaObrigatoria "Senha: "
  escolhaFiccao <- lerEntradaObrigatoria "Tem interesse em livros de ficcao? (S/N): "
  escolhaNaoFiccao <- lerEntradaObrigatoria "Tem interesse em livros de nao ficcao? (S/N): "
  escolhaRomance <- lerEntradaObrigatoria "Tem interesse em livros de romance? (S/N): "
  escolhaHorror <- lerEntradaObrigatoria "Tem interesse em livros de horror? (S/N): "
  escolhaBiografia <- lerEntradaObrigatoria "Tem interesse em livros de biografia? (S/N): "
  let ficcaoUsuario = escolhaSimNao escolhaFiccao
  let naoFiccaoUsuario = escolhaSimNao escolhaNaoFiccao
  let romanceUsuario = escolhaSimNao escolhaRomance
  let horrorUsuario = escolhaSimNao escolhaHorror
  let biografiaUsuario = escolhaSimNao escolhaBiografia
  usuarioFoiInserido <-
    insereUsuario
      Usuario
        { idUsuario = 0
        , nome = nomeUsuario
        , email = emailUsuario
        , senha = senhaUsuario
        , gostaFiccao = ficcaoUsuario
        , gostaNaoFiccao = naoFiccaoUsuario
        , gostaRomance = romanceUsuario
        , gostaHorror = horrorUsuario
        , gostaBiografia = biografiaUsuario
        , estantes = []
        }
  return (usuarioFoiInserido)

-- Edita as informacoes do usuario logado no sistema.
editarUsuario :: Usuario -> IO Usuario
editarUsuario usuario = do
  exibeTopoMenu "Editar Meu Perfil"
  putStrLn "Qual campo deseja modificar?"
  putStrLn ("(1) Nome: " ++ nome usuario)
  putStrLn ("(2) E-mail: " ++ email usuario)
  putStrLn "(3) Senha"
  putStrLn ("(4) Interesse em Ficcao? (S/N): " ++ show (exibeEscolhaSimNao (gostaFiccao usuario)))
  putStrLn ("(5) Interesse em Nao Ficcao? (S/N): " ++ show (exibeEscolhaSimNao (gostaNaoFiccao usuario)))
  putStrLn ("(6) Interesse em Romance? (S/N): " ++ show (exibeEscolhaSimNao (gostaRomance usuario)))
  putStrLn ("(7) Interesse em Horror? (S/N): " ++ show (exibeEscolhaSimNao (gostaHorror usuario)))
  putStrLn ("(8) Interesse em Biografia (S/N): " ++ show (exibeEscolhaSimNao (gostaBiografia usuario)))
  putStrLn "Opcao: "
  opcao <- readLn :: IO Int
  opcao <- validaOpcao "Opcao: " opcao 1 8
  usuario <- modificarCampoPerfil opcao usuario
  usuario <- editaUsuario usuario
  if (isUsuarioNulo usuario)
    then exibeMensagem "Perfil nao editado."
    else exibeMensagem "Perfil editado com sucesso."
  putStrLn "Deseja editar outro campo? (S/N): "
  confirmar <- getLine
  if (confirmar == "s" || confirmar == "S")
    then editarUsuario usuario
    else return (usuario)

modificarCampoPerfil :: Int -> Usuario -> IO Usuario
modificarCampoPerfil 1 usuario = modificarNome usuario
modificarCampoPerfil 2 usuario = modificarEmail usuario
modificarCampoPerfil 3 usuario = modificarSenha usuario
modificarCampoPerfil 4 usuario = modificarFiccao usuario
modificarCampoPerfil 5 usuario = modificarNaoFiccao usuario
modificarCampoPerfil 6 usuario = modificarRomance usuario
modificarCampoPerfil 7 usuario = modificarHorror usuario
modificarCampoPerfil 8 usuario = modificarBiografia usuario

modificarNome :: Usuario -> IO Usuario
modificarNome usuario = do
  valor <- lerEntradaObrigatoria "Nome: "
  return (setaCampoUsuario usuario "nome" valor)

modificarEmail :: Usuario -> IO Usuario
modificarEmail usuario = do
  valor <- lerEntradaObrigatoria "Email: "
  valor <- validaEmail valor "Email: "
  return (setaCampoUsuario usuario "email" valor)

modificarSenha :: Usuario -> IO Usuario
modificarSenha usuario = do
  valor <- lerEntradaObrigatoria "Senha: "
  return (setaCampoUsuario usuario "senha" valor)

modificarFiccao :: Usuario -> IO Usuario
modificarFiccao usuario = do
  escolha <- lerEntradaObrigatoria "Tem interesse em livros de ficcao? (S/N): "
  return (setaCampoUsuario usuario "ficcao" escolha)

modificarNaoFiccao :: Usuario -> IO Usuario
modificarNaoFiccao usuario = do
  escolha <- lerEntradaObrigatoria "Tem interesse em livros de nao ficcao? (S/N): "
  return (setaCampoUsuario usuario "naoFiccao" escolha)

modificarRomance :: Usuario -> IO Usuario
modificarRomance usuario = do
  escolha <- lerEntradaObrigatoria "Tem interesse em livros de romance? (S/N): "
  return (setaCampoUsuario usuario "romance" escolha)

modificarHorror :: Usuario -> IO Usuario
modificarHorror usuario = do
  escolha <- lerEntradaObrigatoria "Tem interesse em livros de horror? (S/N): "
  return (setaCampoUsuario usuario "horror" escolha)

modificarBiografia :: Usuario -> IO Usuario
modificarBiografia usuario = do
  escolha <- lerEntradaObrigatoria "Tem interesse em livros de biografia? (S/N): "
  return (setaCampoUsuario usuario "biografia" escolha)

-- A partir da confirmacao do usuario, sera realizada a remocao do perfiil logado.
removerUsuario :: Usuario -> IO Bool
removerUsuario usuario = do
  exibeTopoMenu "Remover Meu Perfil"
  putStrLn "Deseja realmente remover seu perfil (S/N): "
  confirmacao <- getLine
  if confirmacao == "S" || confirmacao == "s"
    then do
      usuarioFoiRemovido <- removeUsuario (idUsuario usuario)
      return (usuarioFoiRemovido)
    else return (False)

-- Verifica se o e-mail ja foi utilizado no sistema
validaEmail :: String -> String -> IO String
validaEmail email campo = do
  existe <- verificaSeEmailExiste email
  if existe
    then do
      exibeMensagem "E-mail ja cadastrado! Tente novamente. "
      putStrLn campo
      email <- getLine
      validaEmail email campo
    else return email
