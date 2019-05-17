exibeMenuUsuario :: String -> String
exibeMenuUsuario nome =  " \n.::. PrompSkoob .::.\n - Menu Principal - \n Ola, " ++ nome ++ "!\n\n (1) Editar meu perfil\n (2) Gerenciar livro\n (3) Minha estante\n (4) Pesquisar no acervo\n (5) Recomendações de livros\n (6) Remover meu perfil\n (7) Sair da conta\n (8) Sair\n\nOpcao: "

exibeMenuVisitante :: String -> String
exibeMenuVisitante nome = " \n.::. PrompSkoob .::.\n - Menu Principal - \n Ola, " ++ nome ++ "!\n (1) Quero me cadastrar\n (2) Autenticacao\n (3) Pesquisar no acervo\n (4) Sair\n\n Opcao: "

exibeMenu :: Bool -> String -> String
exibeMenu True nome = exibeMenuUsuario nome
exibeMenu False nome = exibeMenuVisitante nome

validaOpcao :: Int -> Bool -> Bool
validaOpcao opcao estaLogado 
    | (estaLogado == True) && (opcao < 1 || opcao > 8) = False
    | (estaLogado == False) && (opcao < 1 || opcao > 4) = False
    | otherwise = True

sair :: IO()
sair = putStrLn "Tchau!"

acaoMenu :: Int -> Bool -> IO()
acaoMenu 1 False = cadastro
acaoMenu 2 False = autenticacao
acaoMenu 3 False = pesquisarNoAcervo
acaoMenu 4 False = sair
acaoMenu 1 True = editarPerfil
acaoMenu 2 True = gerenciaLivro
acaoMenu 3 True = minhaEstante
acaoMenu 4 True = pesquisarNoAcervo
acaoMenu 5 True = recomendaLivros
acaoMenu 6 True = removePerfil
acaoMenu 7 True = sairConta
acaoMenu 8 True = sair

cadastro :: IO()
cadastro = putStrLn "cadastrando"

autenticaoUsuario :: String -> String -> Bool -- ESTA FUNCAO SERA REIMPLEMENTADO NA PARTE DE USUARIO
autenticaoUsuario nome senha = True

autenticacao :: IO()
autenticacao = do
    putStrLn " .::. PrompSkoob .::."
    putStrLn " - Autenticacao - \n"
    putStrLn "E-mail: "
    email <- getLine
    putStrLn "Senha: "
    senha <- getLine
    if (autenticaoUsuario email senha) == True then do
        rodarSistema True email
    else do 
        putStrLn "Usuario ou senha incorretos"
        rodarSistema False "visitante"

pesquisarNoAcervo :: IO()
pesquisarNoAcervo = putStrLn "pesquisando"

editarPerfil :: IO()
editarPerfil = putStrLn "editando perfil"

gerenciaLivro :: IO()
gerenciaLivro = putStrLn "gerenciando livro"

minhaEstante :: IO()
minhaEstante = putStrLn "minha Estante"

recomendaLivros :: IO()
recomendaLivros = putStrLn "recomendando livros"

removePerfil :: IO()
removePerfil = putStrLn "removendo perfil"

sairConta :: IO()
sairConta = rodarSistema False "visitante"

main = do
    let estaLogado = False
    let nome = "visitante"
    rodarSistema estaLogado nome
   

rodarSistema :: Bool -> String -> IO()
rodarSistema estaLogado nome = do
    putStrLn (exibeMenu estaLogado nome)
    opcao <- readLn :: IO Int
    putStrLn ""
    if (validaOpcao opcao estaLogado) == False then do
        putStrLn "Opcao invalida!\n"
        main
    else acaoMenu opcao estaLogado
    