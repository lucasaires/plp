-- import main

data Usuario = Usuario { idUsuario :: Int
, nome :: String
, email :: String
, senha :: String
, gostaFiccao :: Bool
, gostaNaoFicao :: Bool
, gostaRomance :: Bool
, gostaHorror :: Bool
, gostaBiografia :: Bool
, estantes :: [Estante]} deriving (Show, Read)

data Livro =  Livro { idLivro :: Int
, titulo :: String
, autor :: String
, paginas :: Int
, ficcao :: Bool
, naoFicao :: Bool
, romance :: Bool
, horror :: Bool
, biografia :: Bool
, leitores :: Int
, notaGeral :: Float} deriving (Show, Read)

data Estante =  Estante { idLivroE :: Int
, idEstante :: Int
, usuario :: Usuario
, livro :: Livro
, nota :: Float
, situacao :: Int} deriving (Show, Read)

size :: [t] -> Int
size [] = 0
size (x:xs) = 1 + size xs

obtemSituacao :: Int -> String
obtemSituacao 1 = "Nao Lido"
obtemSituacao 2 = "Lendo"
obtemSituacao 3 = "Lido"
obtemSituacao 4 = "Abandonei"

printaEstante :: [Estante] -> Int -> IO()
printaEstante _ 0 = putStrLn "Nenhum livro adicionado a sua estante!"
printaEstante [] tamanhoEstante = putStr ""
printaEstante (l:ls) tamanhoEstante = do
    print ("#" ++ show (idLivroE l) ++ " - " ++ titulo (livro l) ++ " - " ++ (autor (livro l)) ++ " (" ++ show (paginas (livro l)) ++ "pgs) [" ++ obtemSituacao (situacao l) ++ "] - Minha Nota: " ++ show (nota l))
    printaEstante ls tamanhoEstante

listagemEstante :: Usuario -> IO()
listagemEstante usuario  
    -- | listaLivrosEstante(usuario) == True = printaEstante estantes (size estantes)                       -- listaLivrosEstante eh uma funcao do DB
    = printaEstante (estantes usuario) (size (estantes usuario))

escolheLivro :: [Livro] -> Livro                                                                             -- FUNCAO DA PARTE DO LIVRO, DELETAR ESTE QUANDO IMPLEMENTADO O CORRETO
escolheLivro livros = Livro 10 "as aventuras de micaela" "micaela" 1000 True True True True True 999 5.0

obtemLivrosEstante :: [Estante] -> [Livro]
obtemLivrosEstante [] = []
obtemLivrosEstante (e:es) = [(livro e)] ++ obtemLivrosEstante es

remocaoLivroEstante :: Usuario -> IO()
remocaoLivroEstante usuario = do
    putStrLn "\n .::. PrompSkoob .::."
    putStrLn " - Remover Livro da Estante - \n"
    
    let livro = escolheLivro (obtemLivrosEstante (estantes usuario))
    putStrLn "Deseja realmente remover este livro da sua estante? (S/N) : "
    confirmacao <- getLine
    removeLivroEst usuario livro confirmacao

removeLivroEst :: Usuario -> Livro -> String -> IO()
removeLivroEst usuario livro "s" = putStrLn "removendo Livro da estante" --removeLivroEstanteDB (idUsuario usuario) (idLivro livro) -- METODO DO DB
removeLivroEst usuario livro "S" = putStrLn "removendo Livro da estante" --removeLivroEstanteDB (idUsuario usuario) (idLivro livro)
removeLivroEst usuario livro "n" = do
    putStrLn "Livro nao serah removido"
    -- retorna para o menu de estante

adicionaLivro :: Usuario -> IO()
adicionaLivro usuario = do
    putStrLn "\n .::. PrompSkoob .::."
    putStrLn " - Adicionar Livros na minha Estante - \n"
    -- let livro = escolheLivro listaLivros -- listaLivros eh uma funcao do DB
    --let sucesso = adicionaLivroEstante (idUsuario usuario) (idLivro livro) -- adicionaLivroEstante eh uma funcao do DB
    let sucesso = True
    if (not sucesso) then putStrLn "Livro adicionado a sua estante com sucesso."
    else putStrLn "Ocorreu um erro ao adicionar livro na estante: "
    putStrLn "Deseja adicionar outro livro a sua estante: (S/N)"
    opcao <- getLine
    validaOpcaoAdicao opcao usuario

validaOpcaoAdicao :: String -> Usuario -> IO()
validaOpcaoAdicao "s" usuario = adicionaLivro usuario
validaOpcaoAdicao "S" usuario = adicionaLivro usuario
validaOpcaoAdicao "n" usuario = putStrLn "retorna para o menu de estante" -- RETORNA PARA O MENU DE ESTANTE
validaOpcaoAdicao "N" usuario = putStrLn "retorna para o menu de estante" -- RETORNA PARA O MENU DE ESTANTE
validaOpcaoAdicao opcao usuario 
    | opcao /= "s" && opcao /= "S" && opcao /= "n" && opcao /= "N" = do 
        putStrLn "\nOpcao invalida"
        adicionaLivro usuario

edicaoSituacao :: Usuario -> IO()
edicaoSituacao usuario = do
    putStrLn "\n .::. PrompSkoob .::." 
    putStrLn " - Mudar Status de Leitura - \n"
    let livro = escolheLivro (obtemLivrosEstante (estantes usuario))
    putStrLn "Digite o status de leitura do livro (Nao Lido[1], Lendo[2], Lido[3], Abandonei[4]): "
    situacao <- readLn :: IO Int
    whileSituacaoInvalida situacao usuario livro

whileSituacaoInvalida :: Int -> Usuario -> Livro -> IO()
whileSituacaoInvalida situacao usuario livro
    | situacao < 1 || situacao > 4 = do
        putStrLn "Status invalido!"
        putStrLn "Digite o status de leitura do livro (Nao Lido[1], Lendo[2], Lido[3], Abandonei[4]): "
        novaSituacao <- readLn :: IO Int
        whileSituacaoInvalida novaSituacao usuario livro
    | otherwise = putStrLn "Situacao valida!" --mudaSituacao (idUsuario usuario) (idLivro livro) novaSituacao -- mudaSituacao EH UMA FUNCAO DO DB