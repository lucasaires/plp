module LivroCtrl
  ( adicionarLivroEstante
  , cadastrarLivro
  , editarLivro
  , exibeLivros
  , removerLivro
  , escolheLivro
  ) where

import           EstanteDB
import           EstanteType
import           LivroDB
import           Utilitario

-- Adiciona o livro na estante do usuario logado.
adicionarLivroEstante :: Usuario -> IO ()
adicionarLivroEstante usuario = do
  exibeTopoMenu "Adicionar Livro na Estante"
  idLivro <- escolheLivroAdicionar usuario
  livroFoiAdicionado <- adicionaLivroEstante idLivro (idUsuario usuario)
  if (livroFoiAdicionado)
    then exibeMensagem "Livro adicionado a sua estante com sucesso."
    else exibeMensagem "Livro nao foi adicionada a sua estante."
  putStrLn "Deseja adicionar outro livro a sua estante? (S/N): "
  confirmar <- getLine
  if (confirmar == "s" || confirmar == "S")
    then adicionarLivroEstante usuario
    else putStrLn ""

-- Cadastra um livro
cadastrarLivro :: IO Bool
cadastrarLivro = do
  exibeTopoMenu "Cadastrar Livro"
  tituloLivro <- lerEntradaObrigatoria "Título: "
  autorLivro <- lerEntradaObrigatoria "Autor: "
  paginasLivro <- lerEntradaObrigatoria "Total de paginas: "
  paginasLivro <- validaNumeroPositivo "Total de paginas: " (read paginasLivro :: Int)
  escolhaFiccao <- lerEntradaObrigatoria "Este livro é de ficcao? (S/N): "
  escolhaNaoFiccao <- lerEntradaObrigatoria "Este livro é de nao ficcao? (S/N): "
  escolhaRomance <- lerEntradaObrigatoria "Este livro é de romance? (S/N): "
  escolhaHorror <- lerEntradaObrigatoria "Este livro é de horror? (S/N): "
  escolhaBiografia <- lerEntradaObrigatoria "Este livro é de biografia? (S/N): "
  let ficcaoLivro = escolhaSimNao escolhaFiccao
  let naoFiccaoLivro = escolhaSimNao escolhaNaoFiccao
  let romanceLivro = escolhaSimNao escolhaRomance
  let horrorLivro = escolhaSimNao escolhaHorror
  let biografiaLivro = escolhaSimNao escolhaBiografia
  livroFoiInserido <-
    insereLivro
      Livro
        { idLivro = 0
        , titulo = tituloLivro
        , autor = autorLivro
        , paginas = paginasLivro
        , ficcao = ficcaoLivro
        , naoFiccao = naoFiccaoLivro
        , romance = romanceLivro
        , horror = horrorLivro
        , biografia = biografiaLivro
        , leitores = 0
        , notaGeral = 0.0
        }
  return (livroFoiInserido)

-- Exibe todos os livros cadastrados
exibeLivros :: [Livro] -> Int -> IO ()
exibeLivros livro 0 = exibeMensagem "Nenhum livro cadastrado!"
exibeLivros [] tamanho = putStrLn ""
exibeLivros (livro:livros) tamanho = do
  putStrLn
    ("#" ++
     show (idLivro livro) ++
     " - " ++
     titulo livro ++
     " - " ++
     autor livro ++
     " (" ++
     show (paginas livro) ++
     "pgs) " ++
     obtemGeneros livro ++ " - Nota Geral: " ++ show (notaGeral livro) ++ " - Leitores: " ++ show (leitores livro))
  exibeLivros livros tamanho

-- A partir da confirmacao do usuario, sera realizada a remocao do livro.
removerLivro :: IO Bool
removerLivro = do
  exibeTopoMenu "Remover Livro"
  livro <- escolheLivro
  putStrLn "Deseja realmente remover este livro? (S/N): "
  confirmacao <- getLine
  if confirmacao == "S" || confirmacao == "s"
    then do
      livroFoiRemovido <- removeLivro (idLivro livro)
      return (livroFoiRemovido)
    else return (False)

escolheLivro :: IO Livro
escolheLivro = do
  idLivro <- lerEntradaObrigatoria "Informe o ID do livro: "
  idLivro <- validaNumeroPositivo "Informe o ID do livro: " (read idLivro :: Int)
  livro <- consultaLivro idLivro
  if isLivroNulo livro
    then do
      exibeMensagem "O ID informado invalido!"
      escolheLivro
    else return (livro)

escolheLivroAdicionar :: Usuario -> IO Int
escolheLivroAdicionar usuario = do
  idLivro <- lerEntradaObrigatoria "Informe o ID do livro: "
  idLivro <- validaNumeroPositivo "Informe o ID do livro: " (read idLivro :: Int)
  livro <- consultaLivro idLivro
  if isLivroNulo livro
    then do
      exibeMensagem "O ID informado invalido!"
      escolheLivroAdicionar usuario
    else return (idLivro)
  idLivro <- verificaSeLivroAdicionado usuario idLivro
  return (idLivro)

verificaSeLivroAdicionado :: Usuario -> Int -> IO Int
verificaSeLivroAdicionado usuario idLivro = do
  livroAdicionado <- verificaLivroAdicionado (idUsuario usuario) idLivro
  if livroAdicionado
    then do
      exibeMensagem "O ID informado ja utilizado!"
      escolheLivroAdicionar usuario
    else return (idLivro)

editarLivro :: IO Livro
editarLivro = do
  exibeTopoMenu "Editar Livro"
  livro <- escolheLivro
  putStrLn "Qual campo deseja modificar?"
  putStrLn ("(1) Titulo: " ++ titulo livro)
  putStrLn ("(2) Autor: " ++ autor livro)
  putStrLn ("(3) Total Paginas: " ++ show (paginas livro))
  putStrLn ("(4) Ficcao (S/N): " ++ show (exibeEscolhaSimNao (ficcao livro)))
  putStrLn ("(5) Nao Ficcao (S/N): " ++ show (exibeEscolhaSimNao (naoFiccao livro)))
  putStrLn ("(6) Romance (S/N): " ++ show (exibeEscolhaSimNao (romance livro)))
  putStrLn ("(7) Horror (S/N): " ++ show (exibeEscolhaSimNao (horror livro)))
  putStrLn ("(8) Biografia (S/N): " ++ show (exibeEscolhaSimNao (biografia livro)))
  putStrLn "Opcao: "
  opcao <- readLn :: IO Int
  opcao <- validaOpcao "Opcao: " opcao 1 8
  livro <- modificarCampoLivro opcao livro
  livro <- editaLivro livro
  if (isLivroNulo livro)
    then exibeMensagem "Livro nao editado."
    else exibeMensagem "Livro editado com sucesso."
  putStrLn "Deseja editar outro livro? (S/N): "
  confirmar <- getLine
  if (confirmar == "s" || confirmar == "S")
    then editarLivro
    else return (livro)

modificarCampoLivro :: Int -> Livro -> IO Livro
modificarCampoLivro 1 livro = modificarTitulo livro
modificarCampoLivro 2 livro = modificarAutor livro
modificarCampoLivro 3 livro = modificarPaginas livro
modificarCampoLivro 4 livro = modificarFiccao livro
modificarCampoLivro 5 livro = modificarNaoFiccao livro
modificarCampoLivro 6 livro = modificarRomance livro
modificarCampoLivro 7 livro = modificarHorror livro
modificarCampoLivro 8 livro = modificarBiografia livro

modificarTitulo :: Livro -> IO Livro
modificarTitulo livro = do
  valor <- lerEntradaObrigatoria "Titulo: "
  return (setaCampoLivro livro "titulo" valor)

modificarAutor :: Livro -> IO Livro
modificarAutor livro = do
  valor <- lerEntradaObrigatoria "Autor: "
  return (setaCampoLivro livro "autor" valor)

modificarPaginas :: Livro -> IO Livro
modificarPaginas livro = do
  valor <- lerEntradaObrigatoria "Total Paginas: "
  valor <- validaNumeroPositivo "Total Paginas: " (read valor :: Int)
  return (setaCampoLivro livro "paginas" (show valor))

modificarFiccao :: Livro -> IO Livro
modificarFiccao livro = do
  escolha <- lerEntradaObrigatoria "Ficcao (S/N): "
  return (setaCampoLivro livro "ficcao" escolha)

modificarNaoFiccao :: Livro -> IO Livro
modificarNaoFiccao livro = do
  escolha <- lerEntradaObrigatoria "Nao ficcao (S/N): "
  return (setaCampoLivro livro "naoFiccao" escolha)

modificarRomance :: Livro -> IO Livro
modificarRomance livro = do
  escolha <- lerEntradaObrigatoria "Romance (S/N): "
  return (setaCampoLivro livro "romance" escolha)

modificarHorror :: Livro -> IO Livro
modificarHorror livro = do
  escolha <- lerEntradaObrigatoria "Horror (S/N): "
  return (setaCampoLivro livro "horror" escolha)

modificarBiografia :: Livro -> IO Livro
modificarBiografia livro = do
  escolha <- lerEntradaObrigatoria "Biografia (S/N): "
  return (setaCampoLivro livro "biografia" escolha)
