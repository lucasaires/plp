data Usuario = Usuario { idUsuario :: Int
, nome :: String
, email :: String
, senha :: String
, gostaFiccao :: Bool
, gostaNaoFicao :: Bool
, gostaRomance :: Bool
, gostaHorror :: Bool
, gostaBiografia :: Bool
, estantes :: [Estante]} deriving (Show)

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
, notaGeral :: Float} deriving (Show)

data Estante =  Estante { idLivroE :: Int
, idEstante :: Int
, usuario :: Usuario
, livro :: Livro
, nota :: Float
, situacao :: Int} deriving (Show)

size :: [t] -> Int
size [] = 0
size (x:xs) = 1 + size xs

registroLeitura :: Usuario -> IO()
registroLeitura usuario = do
	putStrLn " .::. PrompSkoob .::."
	putStrLn "- Registrar Leitura -  \n"
	
	escolheLivro(obtemLivrosEstante(estantes usuario));
	estante = obtemEstantePorLivro(estantes usuario);
	(estantes paginasLidas) <- verificaAvaliacao
	
	putStrLn "Deixe seu comentario sobre o livro: "
	(estantes comentario)<- getLine
	
	registraLeitura(estantes);
	
	putStrLn "Registro de leitura realizado com sucesso."



verificaQuantPaginas :: IO Int
verificaQuantPaginas = do 
	putStrLin "Quantas páginas foram lidas?"
	(estantes paginasLidas) <- readLn :: IO Int
	if((estantes paginasLidas) > 0 || (estantes paginasLidas) < (livro paginas)) then return (estantes paginasLidas)
	else do
		putStrLn "Numero de pagina invalida!"
		(estantes paginasLidas) <- verificaQuantPaginas :: IO Int
		return (estantes paginasLidas)
	
	

verificaAvaliacao :: IO Int
verificaAvaliacao  = do
	putStrLn "Dê sua nota de avalicao no intervalo de 1 a 5: "
	nota <- readLn :: IO Int
	if(nota >= 0 || nota <= 5) then return nota
	else do
		putStrLn "Nota invalida!"
		nota <- verificaAvaliacao :: IO Int
		return nota
	
avalicaoLivro :: Usuario -> IO()
avalicaoLivro usuario = do
    putStrLn " .::. PrompSkoob .::."
	putStrLn " - Avaliar Livro da Estante - \n"
	let livr = escolheLivro (obtemLivrosEstante (estantes usuario))
	nota <- verificaAvaliacao
	avaliaLivro((idUsuario usuario) (idLivro livro) (nota))
	putStrLn "Avaliação realizada com sucesso."
	

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
    -- | listaLivrosEstante(usuario) == True = printaEstante estantes (size estantes)
    = printaEstante (estantes usuario) (size (estantes usuario))

remocaoLivroEstante :: Usuario -> IO()
remocaoLivroEstante usuario = do
    putStrLn " .::. PrompSkoob .::."
    putStrLn " - Remover Livro da Estante - \n"
    let livr = escolheLivro (obtemLivrosEstante (estantes usuario))
    putStrLn "Deseja realmente remover este livro da sua estante? (S/N) : "
    confirmacao <- getLine
    removeLivroEst livr confirmacao

removeLivroEst :: Usuario -> Livro -> String -> IO()
removeLivroEst usuario livro "s" = removeLivroEstanteDB (idUsuario usuario) (idLivro livro)
removeLivroEst usuario livro "S" = removeLivroEstanteDB (idUsuario usuario) (idLivro livro)
removeLivroEst usuario livro "n" = print "oi"
