data Livro =  Livro { idLivro :: Int
, titulo :: String
, autor :: String
, paginas :: Int
, ficcao :: Bool
, naoFiccao :: Bool
, romance :: Bool
, horror :: Bool
, biografia :: Bool
, leitores :: Int
, notaGeral :: Float} deriving (Show, Read)

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
cadastro = do 
    putStrLn " - Quero me Cadastrar -"
    
    putStrLn "Nome: "
    nome <- getLine 
    
    putStrLn "Email: "
    email <- getLine
    
    putStrLn "Senha: "
    senha <- getLine

    cadastropart2 nome email senha
    putStr ""


cadastropart2 :: String -> String -> String -> IO() 
cadastropart2 campo campo2 campo3
    |campo == " " = cadastro
    |campo2 == " " = cadastro
    |campo3 == " " = cadastro 
    |otherwise = cadastropart3

cadastropart3 :: IO()
cadastropart3 = do
    
    putStrLn "Tem interesse em livros de ficcao? (S/N): "
    escolha1 <- getLine

    putStrLn "Tem interesse em livros de nao ficcao? (S/N): "
    escolha2 <- getLine

    putStrLn "Tem interesse em livros de romance? (S/N): "
    escolha3 <- getLine

    putStrLn "Tem interesse em livros de horror? (S/N): "
    escolha4 <- getLine

    putStrLn "Tem interesse em livros de biografia? (S/N): "
    escolha5 <- getLine
    
    verificaEscolha escolha1 escolha2 escolha3 escolha4 escolha5
     
    putStr""    


    --chama o metodo bd

verificaEscolha :: String -> String -> String -> String -> String -> IO ()
verificaEscolha escolha1 escolha2 escolha3 escolha4 escolha5 = if (escolha1 /= "s" && escolha1 /= "n" ) then do
    cadastropart3
    else if (escolha2 /= "s" && escolha2 /= "n" && escolha2 /= "N" && escolha2 /= "S") then do
        putStrLn "Erro"
        cadastropart3
        else if (escolha3 /= "s" && escolha3 /= "n" && escolha3 /= "N" && escolha3 /= "S") then do 
            putStrLn "Erro"
            cadastropart3
            else if (escolha4 /= "s" && escolha4 /= "n" && escolha4 /= "N" && escolha4 /= "S") then do
                putStrLn "Erro"
                cadastropart3
                else if (escolha5 /= "s" && escolha5 /= "n" && escolha5 /= "N" && escolha5 /= "S") then do
                    putStrLn "Erro"
                    cadastropart3
                    else do
                        operacaoSucesso

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
pesquisarNoAcervo = do
    putStrLn ".::. PrompSkoob .::."
    putStrLn " - Pesquisar Acervo - "
    putStrLn "Pesquise pelo titulo: "
    livro <- getLine
    validaPesquisa livro
    putStrLn ""
    -- pesquisa no bd     

validaPesquisa :: String -> IO()
validaPesquisa livro 
    |livro == " " = pesquisarNoAcervo
    |otherwise = putStr ""

editarPerfil :: IO ()
editarPerfil = do
    putStrLn ".::. PrompSkoob .::."
    putStrLn " - Editar Meu Perfil - "
    putStrLn "Qual campo deseja modificar? "
    putStrLn "(1) Nome: "
    putStrLn "(2) E-mail: "
    putStrLn "(3) Senha: "
    putStrLn "(4) Interesse em Ficcao? (S/N): "
    putStrLn "(5) Interesse em Nao Ficcao? (S/N): "
    putStrLn "(6) Interesse em Romance? (S/N): "
    putStrLn "(7) Interesse em Horror? (S/N): "
    putStrLn "(8) Interesse em Biografia (S/N): "
    
    campo <- readLn :: IO Int

    validaEntradaPerfil campo 

    --chama o metodo bd 
    putStrLn "Deseja editar outro campo? (S/N): "
    desejo <- getLine

    verificaDesejo desejo
    putStr ""


verificaDesejo :: String -> IO()
verificaDesejo desejo = if (desejo == "s" || desejo == "S" || desejo == "n" || desejo == "n") then do
    editarPerfil 
    else do 
        putStrLn "Perfil editado com sucesso"

modificaPerfil :: Int -> IO()
modificaPerfil 1 = modificaNome
modificaPerfil 2 = modifcaEmail
modificaPerfil 3 = modificaSenha
modificaPerfil 4 = modificaFiccao
modificaPerfil 5 = modificaNFiccao
modificaPerfil 6 = modificaRomace
modificaPerfil 7 = modificaHorror
modificaPerfil 8 = modificaBiografia


modificaNome :: IO()
modificaNome = do
    putStr "Nome: "
    nome <- getLine
    -- atualiza bd 
    putStr ""

modifcaEmail :: IO()
modifcaEmail = do 
    putStr "Email: "
    email <- getLine
    -- atualiza bd
    putStr ""

modificaSenha :: IO()
modificaSenha = do 
    putStr "Senha: "
    senha <- getLine
    -- atualiza bd 
    putStr ""

modificaFiccao :: IO()
modificaFiccao = do 
    putStr "Interesse em Ficcao? (S/N): "
    interesse <- getLine
    -- atualiza bd 
    putStr ""

modificaNFiccao :: IO() 
modificaNFiccao = do 
    putStr "Interesse em Nao Ficcao? (S/N): "
    interesse <- getLine
    -- atualiza bd
    putStr ""

modificaRomace :: IO()
modificaRomace = do
    putStr "Interesse em Romance? (S/N): "
    interesse <- getLine
    -- atualiza bd
    putStr ""

modificaHorror :: IO()
modificaHorror = do
    putStr "Interesse em Horror? (S/N): "
    interesse <- getLine
    -- atualiza bd
    putStr ""

modificaBiografia :: IO()
modificaBiografia = do 
    putStr "Interesse em Biografia (S/N): "
    biografia <- getLine
    -- atualiza bd
    putStr ""


validaEntradaPerfil :: Int -> IO ()
validaEntradaPerfil campo = if (campo < 1 || campo > 8) then do 
    putStrLn "Entrada Invalida"
    editarPerfil
    else modificaPerfil campo


gerenciaLivro :: IO()
gerenciaLivro = do

    putStrLn "\n .::. PrompSkoob .::.\n"
    putStrLn " - Gerenciar Livro -\n"
    putStrLn "Cadastrar Livro"
    putStrLn "(1) Cadastrar Livro | (2) Editar | (3) Remover | (4) Adicionar a Estante | (5) Voltar"
    opcao <- readLn :: IO Int 
    verificaGerenciaLivro opcao


verificaGerenciaLivro :: Int -> IO() 
verificaGerenciaLivro opcao 
    | opcao < 1 || opcao > 5 = gerenciaLivro
    | otherwise = livroValido opcao 

livroValido :: Int -> IO() 
livroValido 1 = cadastroLivro
livroValido 2 = editarLivro
livroValido 3 = removerLivro
livroValido 4 = adicionarAEstante
--livroValido 5 =  

cadastroLivro :: IO() 
cadastroLivro = do
    putStrLn "\n .::. PrompSkoob .::.\n"
    putStrLn " - Cadastrar Livro - \n"
    putStrLn "No final da operacao aparecerá uma mensagem caso seja realizada com sucesso"
    putStr "Nome: "
    nome <- getLine
    putStr "Autor: "
    autor <- getLine
    putStr "Total de paginas: "
    paginas <- readLn :: IO Int
    
    verificaPaginas nome autor paginas
    -- cadastra o livro bd 
    
        
operacaoSucesso:: IO()
operacaoSucesso = putStrLn "Operacao realizada com Sucesso"
    
verificaPaginas :: String -> String -> Int -> IO()
verificaPaginas nome autor paginas 
    | paginas < 0 = cadastroLivro
    | nome == " " = cadastroLivro
    | autor == " " = cadastroLivro
    | otherwise = operacaoSucesso -- chama o bd
    

editarLivro :: IO() 
editarLivro = do

    putStrLn "\n .::. PrompSkoob .::.\n"
    putStrLn " - Editar Livro - \n"
    let livros = listaLivros  -- para testes -> [Livro 50 "como sobreviver a UFCG" "micaela" 100 False True False True True 77 4.5, Livro 60 "pagando calculo" "anonimo" 666 True False True False False 800 2.0, Livro 70 "as aventuras de fulaninho" "cicraninho" 50 True False False True False 400 5.0]                         -- FUNCAO DO DB
    let livro = escolheLivro livros -- para testes ->Livro 50 "como sobreviver a UFCG" "micaela" 100 False True False True True 77 4.5
    editarLivroPT2 livro

    --validaEntradaPerfil campo
    --editarperfil2

editarLivroPT2 :: Livro -> IO()
editarLivroPT2 livro = do
    printaOpcoesEditarLivro livro
    campo <- readLn :: IO Int
    whileCampoInvalido campo livro

whileCampoInvalido :: Int -> Livro -> IO()
whileCampoInvalido campo livro
    | campo < 1 || campo > 8 = do
        putStrLn "Campo Invalido!"
        printaOpcoesEditarLivro livro
        novoCampo <- readLn :: IO Int
        whileCampoInvalido novoCampo livro
    | otherwise = selecionaOpcoesEditarLivro campo livro

selecionaOpcoesEditarLivro :: Int -> Livro -> IO()
selecionaOpcoesEditarLivro 1 livro = do
    putStr "Nome: "
    nome <- getLine
    let novoLivro = Livro (idLivro livro) nome (autor livro) (paginas livro) (ficcao livro) (naoFiccao livro) (romance livro) (horror livro) (biografia livro) (leitores livro) (notaGeral livro)
    putStrLn "Deseja editar outro campo? (S/N): "
    opcao <- getLine
    validaOpcaoSN opcao novoLivro
selecionaOpcoesEditarLivro 2 livro = do
    putStr "Autor: "
    autor <- getLine
    let novoLivro = Livro (idLivro livro) (titulo livro) autor (paginas livro) (ficcao livro) (naoFiccao livro) (romance livro) (horror livro) (biografia livro) (leitores livro) (notaGeral livro)
    putStrLn "Deseja editar outro campo? (S/N): "
    opcao <- getLine
    validaOpcaoSN opcao novoLivro
selecionaOpcoesEditarLivro 3 livro = do
    putStr "Total de paginas: "
    paginas <- readLn :: IO Int
    if paginas <= 0 then do
        putStrLn "Total de paginas invalida!"
        selecionaOpcoesEditarLivro 3 livro 
    else do
        let novoLivro = Livro (idLivro livro) (titulo livro) (autor livro) paginas (ficcao livro) (naoFiccao livro) (romance livro) (horror livro) (biografia livro) (leitores livro) (notaGeral livro)
        putStrLn "Deseja editar outro campo? (S/N): "
        opcao <- getLine
        validaOpcaoSN opcao novoLivro
selecionaOpcoesEditarLivro 4 livro = do
    putStr "Livro de ficcao? (S/N): "
    gostar <- getLine
    if gostar /= "S" && gostar /= "s" && gostar /= "N" && gostar /= "n" then do
        putStrLn "Opcao invalida!"
        selecionaOpcoesEditarLivro 4 livro
    else do
        let gostarBool = gostarParaBool gostar
        let novoLivro = Livro (idLivro livro) (titulo livro) (autor livro) (paginas livro) gostarBool (naoFiccao livro) (romance livro) (horror livro) (biografia livro) (leitores livro) (notaGeral livro)
        putStrLn "Deseja editar outro campo? (S/N): "
        opcao <- getLine
        validaOpcaoSN opcao novoLivro
    
selecionaOpcoesEditarLivro 5 livro = do
    putStr "Livro de nao ficcao? (S/N): "
    gostar <- getLine
    if gostar /= "S" && gostar /= "s" && gostar /= "N" && gostar /= "n" then do
        putStrLn "Opcao invalida!"
        selecionaOpcoesEditarLivro 5 livro
    else do
        let gostarBool = gostarParaBool gostar
        let novoLivro = Livro (idLivro livro) (titulo livro) (autor livro) (paginas livro) (ficcao livro) gostarBool (romance livro) (horror livro) (biografia livro) (leitores livro) (notaGeral livro)
        putStrLn "Deseja editar outro campo? (S/N): "
        opcao <- getLine
        validaOpcaoSN opcao novoLivro
    
selecionaOpcoesEditarLivro 6 livro = do
    putStr "Livro de romance? (S/N): "
    gostar <- getLine
    if gostar /= "S" && gostar /= "s" && gostar /= "N" && gostar /= "n" then do
        putStrLn "Opcao invalida!"
        selecionaOpcoesEditarLivro 6 livro
    else do
        let gostarBool = gostarParaBool gostar
        let novoLivro = Livro (idLivro livro) (titulo livro) (autor livro) (paginas livro) (ficcao livro) (naoFiccao livro) gostarBool (horror livro) (biografia livro) (leitores livro) (notaGeral livro)
        putStrLn "Deseja editar outro campo? (S/N): "
        opcao <- getLine
        validaOpcaoSN opcao novoLivro
selecionaOpcoesEditarLivro 7 livro = do
    putStr "Livro de horror? (S/N): "
    gostar <- getLine
    if gostar /= "S" && gostar /= "s" && gostar /= "N" && gostar /= "n" then do
        putStrLn "Opcao invalida!"
        selecionaOpcoesEditarLivro 7 livro
    else do
        let gostarBool = gostarParaBool gostar
        let novoLivro = Livro (idLivro livro) (titulo livro) (autor livro) (paginas livro) (ficcao livro) (naoFiccao livro) (romance livro) gostarBool (biografia livro) (leitores livro) (notaGeral livro)
        putStrLn "Deseja editar outro campo? (S/N): "
        opcao <- getLine
        validaOpcaoSN opcao novoLivro
selecionaOpcoesEditarLivro 8 livro = do
    putStr "Livro de biografia? (S/N): "
    gostar <- getLine
    if gostar /= "S" && gostar /= "s" && gostar /= "N" && gostar /= "n" then do
        putStrLn "Opcao invalida!"
        selecionaOpcoesEditarLivro 8 livro
    else do
        let gostarBool = gostarParaBool gostar
        let novoLivro = Livro (idLivro livro) (titulo livro) (autor livro) (paginas livro) (ficcao livro) (naoFiccao livro) (romance livro) (horror livro) gostarBool (leitores livro) (notaGeral livro)
        putStrLn "Deseja editar outro campo? (S/N): "
        opcao <- getLine
        validaOpcaoSN opcao novoLivro

validaOpcaoSN :: String -> Livro -> IO()
validaOpcaoSN opcao livro
    | opcao == "S" || opcao == "s" = editarLivroPT2 livro
    | opcao == "N" || opcao == "n" = do
        putStrLn "editando livro " --editaLivro livro                              -- FUNCAO DO DB
        gerenciaLivro
    | otherwise = putStrLn "Opcao invalida!"

gostarParaBool :: String -> Bool
gostarParaBool opcao
    | opcao == "S" || opcao == "s" = True
    | opcao == "N" || opcao == "n" = False

printaOpcoesEditarLivro :: Livro -> IO()
printaOpcoesEditarLivro livro = do
    putStrLn "\n Qual campo deseja modificar? \n"
    putStrLn ("(1) Nome: " ++ (titulo livro))
    putStrLn ("(2) Autor: " ++ (autor livro))
    putStrLn ("(3) Total Paginas: " ++ show (paginas livro))
    putStrLn ("(4) Ficcao: " ++ estiloLivro (ficcao livro))
    putStrLn ("(5) Nao Ficcao: " ++ estiloLivro (naoFiccao livro))
    putStrLn ("(6) Romance: " ++ estiloLivro (romance livro))
    putStrLn ("(7) Horror:  " ++ estiloLivro (horror livro))
    putStrLn ("(8) Biografia: " ++ estiloLivro (biografia livro))

estiloLivro :: Bool -> String
estiloLivro True = "S"
estiloLivro False = "N"

--editarperfil2 :: Int -> IO()
--editarperfil2 campo 
--    |campo == 1 = 
--    |campo == 2 = 
--    |campo == 3 = 
--    |campo == 4 =
--    |campo == 5 = 
--    |campo == 6 =
--    |campo == 7 =
--    |campo == 8 = 
--    |otherwise = 


removerLivro :: IO()
removerLivro = putStrLn "removendoLivro"

adicionarAEstante:: IO()
adicionarAEstante = putStrLn "adicionando a estante"

minhaEstante :: IO()
minhaEstante = putStrLn "minha Estante"

recomendaLivros :: IO()
recomendaLivros = do 
    putStrLn ".::. PrompSkoob .::."
    putStrLn "Recomendacoe de livros"
    putStrLn "(1) Adicionar a Estante | (2) Voltar"
    opcao <- readLn :: IO Int
    print opcao


--validaEntradaRecomendacao :: Int -> IO
--validaEntradaRecomendacao opcao 
 --   | opcao == 1 = adicionarAEstante 
 --   | opcao == 2 = 


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