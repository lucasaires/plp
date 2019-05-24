module Main where

import           EstanteCtrl
import           EstanteDB
import           EstanteType
import           LivroCtrl
import           LivroDB
import           UsuarioCtrl
import           UsuarioDB
import           Utilitario

main :: IO ()
main = do
  inicializa
  exibeMenuVisitante

acaoMenuVisitante :: Int -> IO ()
acaoMenuVisitante 1 = cadastroUsuario
acaoMenuVisitante 2 = autenticacaoUsuario
acaoMenuVisitante 3 = pesquisaNoAcervo
acaoMenuVisitante 4 = sair

-- Realiza a autenticacao do usuario
autenticacaoUsuario :: IO ()
autenticacaoUsuario = do
  usuario <- autenticarUsuario
  if not (isUsuarioNulo usuario)
    then exibeMenuUsuario usuario
    else do
      Utilitario.exibeMensagem "Nao existe usuario com o e-mail e/ou senha informados."
      exibeMenuVisitante

-- Cadastra um usuario no sistema
cadastroLivro :: Usuario -> IO ()
cadastroLivro usuario = do
  livroFoiInserido <- cadastrarLivro
  if livroFoiInserido
    then exibeMensagem "Livro cadastrado com sucesso!"
    else exibeMensagem "Nao foi possivel cadastrar livro."
  exibeMenuUsuario usuario

-- Cadastra um usuario no sistema
cadastroUsuario :: IO ()
cadastroUsuario = do
  usuarioInserido <- cadastrarUsuario
  if usuarioInserido
    then exibeMensagem "Perfil criado com sucesso!"
    else exibeMensagem "Nao foi possivel criar o perfil do usuario."
  exibeMenuVisitante

-- Edita o perfil atual do usuario
edicaoPerfil :: Usuario -> IO ()
edicaoPerfil usuario = do
  usuarioEditado <- editarUsuario usuario
  exibeMenuUsuario usuarioEditado

-- Edita o perfil atual do usuario
edicaoLivro :: Usuario -> IO ()
edicaoLivro usuario = do
  livroEditado <- editarLivro
  gerenciaLivro usuario

exibeMenuLivro :: Int -> Usuario -> IO ()
exibeMenuLivro 1 usuario = cadastroLivro usuario
exibeMenuLivro 2 usuario = do
  editarLivro
  gerenciaLivro usuario
exibeMenuLivro 3 usuario = remocaoLivro usuario
exibeMenuLivro 4 usuario = do
  adicionarLivroEstante usuario
  gerenciaLivro usuario

exibeMenuEstante :: Int -> Usuario -> IO ()
exibeMenuEstante 1 usuario = edicaoSituacao usuario
exibeMenuEstante 2 usuario = avaliacaoLivro usuario
exibeMenuEstante 3 usuario = remocaoLivroEstante usuario
exibeMenuEstante 4 usuario = do
  adicionarLivroEstante usuario
  gerenciaLivro usuario

-- Exibe todos os livros cadastrados e o submenu.
gerenciaEstante :: Usuario -> IO ()
gerenciaEstante usuario = do
  exibeTopoMenu "Minha Estante"
  estantes <- listaEstantes (idUsuario usuario)
  exibeLivrosEstante estantes (length estantes)
  putStrLn "(1) Mudar Status | (2) Avaliar | (3) Remover | (4) Voltar"
  putStrLn "Opcao: "
  opcao <- readLn :: IO Int
  opcao <- validaOpcao "Opcao: " opcao 1 4
  if opcao == 4
    then exibeMenuUsuario usuario
    else exibeMenuEstante opcao usuario

-- Exibe todos os livros cadastrados e o submenu.
gerenciaLivro :: Usuario -> IO ()
gerenciaLivro usuario = do
  exibeTopoMenu "Gerenciar Livro"
  livros <- listaLivros
  exibeLivros livros (length livros)
  putStrLn "(1) Cadastrar | (2) Editar | (3) Remover | (4) Adicionar a Estante | (5) Voltar"
  putStrLn "Opcao: "
  opcao <- readLn :: IO Int
  opcao <- validaOpcao "Opcao: " opcao 1 5
  if opcao == 5
    then exibeMenuUsuario usuario
    else exibeMenuLivro opcao usuario

-- Remove o perfil atual do sistema.
remocaoLivro :: Usuario -> IO ()
remocaoLivro usuario = do
  livroFoiRemovido <- removerLivro
  if (livroFoiRemovido)
    then exibeMensagem "Livro removido com sucesso!"
    else exibeMensagem "Livro nao removido!"
  gerenciaLivro usuario

-- Remove o perfil atual do sistema.
remocaoPerfil :: Usuario -> IO ()
remocaoPerfil usuario = do
  usuarioFoiRemovido <- removerUsuario usuario
  if (usuarioFoiRemovido)
    then do
      exibeMensagem "Perfil removido com sucesso!"
      exibeMenuVisitante
    else exibeMenuUsuario usuario

-- Sair da aplicacao
sair :: IO ()
sair = exibeMensagem "Ate breve... :)"

-- Sair da conta logada
sairConta :: IO ()
sairConta = exibeMenuVisitante

inicializa :: IO ()
inicializa = do
  criaTabelaUsuario
  criaTabelaLivro
  criaTabelaEstante

exibeMenuUsuario :: Usuario -> IO ()
exibeMenuUsuario usuario = do
  exibeTopoMenu "Menu Principal"
  putStrLn ("Ola, " ++ (nome usuario) ++ "!")
  putStrLn "(1) Editar meu perfil"
  putStrLn "(2) Gerenciar livro"
  putStrLn "(3) Minha estante"
  putStrLn "(4) Pesquisar no acervo"
  putStrLn "(5) Recomendações de livros"
  putStrLn "(6) Remover meu perfil"
  putStrLn "(7) Sair da conta"
  putStrLn "(8) Sair"
  putStrLn ""
  putStrLn "Opcao: "
  opcao <- readLn :: IO Int
  putStrLn ""
  if not (validaOpcaoMenu opcao True)
    then do
      exibeMensagem "Opcao invalida!"
      exibeMenuUsuario usuario
    else acaoMenu opcao usuario

exibeMenuVisitante :: IO ()
exibeMenuVisitante = do
  exibeTopoMenu "Menu Principal"
  putStrLn "Ola, visitante!"
  putStrLn "(1) Quero me cadastrar"
  putStrLn "(2) Autenticacao"
  putStrLn "(3) Pesquisar no acervo"
  putStrLn "(4) Sair"
  putStrLn ""
  putStrLn "Opcao: "
  opcao <- readLn :: IO Int
  putStrLn ""
  if not (validaOpcaoMenu opcao False)
    then do
      exibeMensagem "Opcao invalida!"
      exibeMenuVisitante
    else acaoMenuVisitante opcao

validaOpcaoMenu :: Int -> Bool -> Bool
validaOpcaoMenu opcao estaLogado
  | estaLogado && (opcao < 1 || opcao > 8) = False
  | not estaLogado && (opcao < 1 || opcao > 4) = False
  | otherwise = True

acaoMenu :: Int -> Usuario -> IO ()
acaoMenu 1 usuario = edicaoPerfil usuario
acaoMenu 2 usuario = gerenciaLivro usuario
acaoMenu 3 usuario = gerenciaEstante usuario
acaoMenu 4 usuario = pesquisaAcervo usuario
acaoMenu 5 usuario = recomendacaoLivros usuario
acaoMenu 6 usuario = remocaoPerfil usuario
acaoMenu 7 usuario = sairConta
acaoMenu 8 usuario = sair

recomendarLivros :: IO ()
recomendarLivros = putStrLn "recomendando livros"

edicaoSituacao :: Usuario -> IO ()
edicaoSituacao usuario = do
  exibeTopoMenu "Mudar Status de Leitura"
  livro <- escolheLivro
  situacao <-
    lerEntradaObrigatoria "Digite o status de leitura do livro (Nao Lido[1], Lendo[2], Lido[3], Abandonei[4]): "
  situacao <- whileSituacaoInvalida (read situacao :: Int)
  mudou <- mudaSituacao livro usuario situacao
  if mudou
    then exibeMensagem "Mudança de status realizado com sucesso."
    else exibeMensagem "Mudança de status nao realizada."
  gerenciaEstante usuario

whileSituacaoInvalida :: Int -> IO Int
whileSituacaoInvalida situacao
  | situacao < 1 || situacao > 4 = do
    putStrLn "Status invalido!"
    putStrLn "Digite o status de leitura do livro (Nao Lido[1], Lendo[2], Lido[3], Abandonei[4]): "
    novaSituacao <- readLn :: IO Int
    whileSituacaoInvalida novaSituacao
  | otherwise = return (situacao)

avaliacaoLivro :: Usuario -> IO ()
avaliacaoLivro usuario = do
  exibeTopoMenu "Avaliar Livro da Estante"
  livro <- escolheLivro
  nota <- lerEntradaObrigatoria "Dê sua nota de avalicao no intervalo de 1 a 5: "
  nota <- verificaAvaliacao (read nota :: Int)
  avaliou <- avaliaLivro livro usuario nota
  if avaliou
    then exibeMensagem "Avaliacao realizada com sucesso."
    else exibeMensagem "Avaliacao nao realizada."
  gerenciaEstante usuario

verificaAvaliacao :: Int -> IO Int
verificaAvaliacao nota
  | nota < 1 || nota > 5 = do
    putStrLn "Nota invalida!"
    putStrLn "Dê sua nota de avalicao no intervalo de 1 a 5: "
    nota <- readLn :: IO Int
    verificaAvaliacao nota
  | otherwise = return (nota)

remocaoLivroEstante :: Usuario -> IO ()
remocaoLivroEstante usuario = do
  exibeTopoMenu "Remover Livro da Estante"
  livro <- escolheLivro
  confirmacao <- lerEntradaObrigatoria "Deseja realmente remover este livro da sua estante? (S/N) : "
  if confirmacao == "s" || confirmacao == "S"
    then do
      removido <- removeLivroEstante livro usuario
      if removido
        then exibeMensagem "Livro removido da estante realizada com sucesso."
        else exibeMensagem "Livro nao removido da estante."
      gerenciaEstante usuario
    else gerenciaEstante usuario

pesquisaNoAcervo :: IO ()
pesquisaNoAcervo = do
  exibeTopoMenu "Pesquisar Acervo"
  titulo <- lerEntradaObrigatoria "Pesquise pelo titulo: "
  livros <- pesquisaLivros titulo
  putStrLn "Resultado: "
  exibeLivros livros (length livros)
  putStrLn ""
  exibeMenuVisitante

pesquisaAcervo :: Usuario -> IO ()
pesquisaAcervo usuario = do
  exibeTopoMenu "Pesquisar Acervo"
  titulo <- lerEntradaObrigatoria "Pesquise pelo titulo: "
  livros <- pesquisaLivros titulo
  putStrLn "Resultado: "
  exibeLivros livros (length livros)
  putStrLn ""
  exibeMenuUsuario usuario

recomendacaoLivros :: Usuario -> IO ()
recomendacaoLivros usuario = do
  exibeTopoMenu "Recomendacoes de livros"
  livros <- recomendaLivros usuario
  exibeLivros livros (length livros)
  putStrLn ""
  exibeMenuUsuario usuario
