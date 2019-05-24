module EstanteType where

import           Utilitario

data Usuario =
  Usuario
    { idUsuario      :: Int
    , nome           :: String
    , email          :: String
    , senha          :: String
    , gostaFiccao    :: Int
    , gostaNaoFiccao :: Int
    , gostaRomance   :: Int
    , gostaHorror    :: Int
    , gostaBiografia :: Int
    , estantes       :: [Estante]
    }
  deriving (Eq, Show)

data Livro =
  Livro
    { idLivro   :: Int
    , titulo    :: String
    , autor     :: String
    , paginas   :: Int
    , ficcao    :: Int
    , naoFiccao :: Int
    , romance   :: Int
    , horror    :: Int
    , biografia :: Int
    , leitores  :: Int
    , notaGeral :: Double
    }
  deriving (Eq, Show)

data Estante =
  Estante
    { idLivroEstante   :: Int
    , idUsuarioEstante :: Int
    , livro            :: Livro
    , usuario          :: Usuario
    , nota             :: Double
    , situacao         :: Int
    , paginasLidas     :: Int
    , comentario       :: String
    }
  deriving (Eq, Show)

obtemGenerosLivro :: Livro -> String -> String
obtemGenerosLivro livro "" = ""
obtemGenerosLivro livro genero
  | genero == "ficcao" && ficcao livro == 1 = "Ficcao, " ++ obtemGenerosLivro livro "naoFiccao"
  | genero == "ficcao" && ficcao livro == 0 = "" ++ obtemGenerosLivro livro "naoFiccao"
  | genero == "naoFiccao" && naoFiccao livro == 1 = "Nao Ficcao, " ++ obtemGenerosLivro livro "romance"
  | genero == "naoFiccao" && naoFiccao livro == 0 = "" ++ obtemGenerosLivro livro "romance"
  | genero == "romance" && romance livro == 1 = "Romance, " ++ obtemGenerosLivro livro "horror"
  | genero == "romance" && romance livro == 0 = "" ++ obtemGenerosLivro livro "horror"
  | genero == "horror" && horror livro == 1 = "Horror, " ++ obtemGenerosLivro livro "biografia"
  | genero == "horror" && horror livro == 0 = "" ++ obtemGenerosLivro livro "biografia"
  | genero == "biografia" && biografia livro == 1 = "Biografia, " ++ obtemGenerosLivro livro ""
  | genero == "biografia" && biografia livro == 0 = "" ++ obtemGenerosLivro livro ""

-- Retorna em formato string todos os generos separados por virgulas. Ex.: (Ficcao, Biografia)
obtemGeneros :: Livro -> String
obtemGeneros livro = do
  let generos = obtemGenerosLivro livro "ficcao"
  if generos /= ""
    then "(" ++ (semUltimaVirgula generos) ++ ")"
    else ""
  where
    semUltimaVirgula :: String -> String
    semUltimaVirgula palavras = take (length palavras - 2) palavras

obtemSituacao :: Int -> String
obtemSituacao 1 = "Nao Lido"
obtemSituacao 2 = "Lendo"
obtemSituacao 3 = "Lido"
obtemSituacao 4 = "Abandonei"

obtemGostoGenero :: Int -> String
obtemGostoGenero 1 = "S"
obtemGostoGenero 0 = "N"

imprimeEstante :: [Estante] -> Int -> IO ()
imprimeEstante estantesUsuario 0 = putStrLn "Nenhum livro adicionado a sua estante!"
imprimeEstante (l:ls) tamanhoEstante = do
  putStrLn
    ("#" ++
     show (idLivroEstante l) ++
     " - " ++
     titulo (livro l) ++
     " - " ++
     (autor (livro l)) ++
     " (" ++ show (paginas (livro l)) ++ "pgs) [" ++ obtemSituacao (situacao l) ++ "] - Minha Nota: " ++ show (nota l))
  imprimeEstante ls tamanhoEstante

listagemEstante :: Usuario -> IO ()
listagemEstante usuario = imprimeEstante (estantes usuario) (size (estantes usuario))

size :: [t] -> Int
size []     = 0
size (x:xs) = 1 + size xs

setaCampoUsuario :: Usuario -> String -> String -> Usuario
setaCampoUsuario usuario campo valor
  | campo == "nome" = setaNomeUsuario usuario valor
  | campo == "email" = setaEmailUsuario usuario valor
  | campo == "senha" = setaSenhaUsuario usuario valor
  | campo == "ficcao" = setaFiccaoUsuario usuario (escolhaSimNao valor)
  | campo == "naoFiccao" = setaNaoFiccaoUsuario usuario (escolhaSimNao valor)
  | campo == "romance" = setaRomanceUsuario usuario (escolhaSimNao valor)
  | campo == "horror" = setaHorrorUsuario usuario (escolhaSimNao valor)
  | campo == "biografia" = setaBiografiaUsuario usuario (escolhaSimNao valor)
  | otherwise = usuario

setaNomeUsuario :: Usuario -> String -> Usuario
setaNomeUsuario usuario valor =
  Usuario
    { idUsuario = (idUsuario usuario)
    , nome = valor
    , email = (email usuario)
    , senha = (senha usuario)
    , gostaFiccao = (gostaFiccao usuario)
    , gostaNaoFiccao = (gostaNaoFiccao usuario)
    , gostaRomance = (gostaRomance usuario)
    , gostaHorror = (gostaHorror usuario)
    , gostaBiografia = (gostaBiografia usuario)
    , estantes = (estantes usuario)
    }

setaEmailUsuario :: Usuario -> String -> Usuario
setaEmailUsuario usuario valor =
  Usuario
    { idUsuario = (idUsuario usuario)
    , nome = (nome usuario)
    , email = valor
    , senha = (senha usuario)
    , gostaFiccao = (gostaFiccao usuario)
    , gostaNaoFiccao = (gostaNaoFiccao usuario)
    , gostaRomance = (gostaRomance usuario)
    , gostaHorror = (gostaHorror usuario)
    , gostaBiografia = (gostaBiografia usuario)
    , estantes = (estantes usuario)
    }

setaSenhaUsuario :: Usuario -> String -> Usuario
setaSenhaUsuario usuario valor =
  Usuario
    { idUsuario = (idUsuario usuario)
    , nome = (nome usuario)
    , email = (email usuario)
    , senha = valor
    , gostaFiccao = (gostaFiccao usuario)
    , gostaNaoFiccao = (gostaNaoFiccao usuario)
    , gostaRomance = (gostaRomance usuario)
    , gostaHorror = (gostaHorror usuario)
    , gostaBiografia = (gostaBiografia usuario)
    , estantes = (estantes usuario)
    }

setaFiccaoUsuario :: Usuario -> Int -> Usuario
setaFiccaoUsuario usuario valor =
  Usuario
    { idUsuario = (idUsuario usuario)
    , nome = (nome usuario)
    , email = (email usuario)
    , senha = (senha usuario)
    , gostaFiccao = valor
    , gostaNaoFiccao = (gostaNaoFiccao usuario)
    , gostaRomance = (gostaRomance usuario)
    , gostaHorror = (gostaHorror usuario)
    , gostaBiografia = (gostaBiografia usuario)
    , estantes = (estantes usuario)
    }

setaNaoFiccaoUsuario :: Usuario -> Int -> Usuario
setaNaoFiccaoUsuario usuario valor =
  Usuario
    { idUsuario = (idUsuario usuario)
    , nome = (nome usuario)
    , email = (email usuario)
    , senha = (senha usuario)
    , gostaFiccao = (gostaFiccao usuario)
    , gostaNaoFiccao = valor
    , gostaRomance = (gostaRomance usuario)
    , gostaHorror = (gostaHorror usuario)
    , gostaBiografia = (gostaBiografia usuario)
    , estantes = (estantes usuario)
    }

setaRomanceUsuario :: Usuario -> Int -> Usuario
setaRomanceUsuario usuario valor =
  Usuario
    { idUsuario = (idUsuario usuario)
    , nome = (nome usuario)
    , email = (email usuario)
    , senha = (senha usuario)
    , gostaFiccao = (gostaFiccao usuario)
    , gostaNaoFiccao = (gostaNaoFiccao usuario)
    , gostaRomance = valor
    , gostaHorror = (gostaHorror usuario)
    , gostaBiografia = (gostaBiografia usuario)
    , estantes = (estantes usuario)
    }

setaHorrorUsuario :: Usuario -> Int -> Usuario
setaHorrorUsuario usuario valor =
  Usuario
    { idUsuario = (idUsuario usuario)
    , nome = (nome usuario)
    , email = (email usuario)
    , senha = (senha usuario)
    , gostaFiccao = (gostaFiccao usuario)
    , gostaNaoFiccao = (gostaNaoFiccao usuario)
    , gostaRomance = (gostaRomance usuario)
    , gostaHorror = valor
    , gostaBiografia = (gostaBiografia usuario)
    , estantes = (estantes usuario)
    }

setaBiografiaUsuario :: Usuario -> Int -> Usuario
setaBiografiaUsuario usuario valor =
  Usuario
    { idUsuario = (idUsuario usuario)
    , nome = (nome usuario)
    , email = (email usuario)
    , senha = (senha usuario)
    , gostaFiccao = (gostaFiccao usuario)
    , gostaNaoFiccao = (gostaNaoFiccao usuario)
    , gostaRomance = (gostaRomance usuario)
    , gostaHorror = (gostaHorror usuario)
    , gostaBiografia = valor
    , estantes = (estantes usuario)
    }

setaCampoLivro :: Livro -> String -> String -> Livro
setaCampoLivro livro campo valor
  | campo == "titulo" = setaTituloLivro livro valor
  | campo == "autor" = setaAutorLivro livro valor
  | campo == "paginas" = setaPaginasLivro livro (read valor :: Int)
  | campo == "ficcao" = setaFiccaoLivro livro (escolhaSimNao valor)
  | campo == "naoFiccao" = setaNaoFiccaoLivro livro (escolhaSimNao valor)
  | campo == "romance" = setaRomanceLivro livro (escolhaSimNao valor)
  | campo == "horror" = setaHorrorLivro livro (escolhaSimNao valor)
  | campo == "biografia" = setaBiografiaLivro livro (escolhaSimNao valor)
  | otherwise = livro

setaTituloLivro :: Livro -> String -> Livro
setaTituloLivro livro valor =
  Livro
    { idLivro = (idLivro livro)
    , titulo = valor
    , autor = (autor livro)
    , paginas = (paginas livro)
    , ficcao = (ficcao livro)
    , naoFiccao = (naoFiccao livro)
    , romance = (romance livro)
    , horror = (horror livro)
    , biografia = (biografia livro)
    , leitores = (leitores livro)
    , notaGeral = (notaGeral livro)
    }

setaAutorLivro :: Livro -> String -> Livro
setaAutorLivro livro valor =
  Livro
    { idLivro = (idLivro livro)
    , titulo = (titulo livro)
    , autor = valor
    , paginas = (paginas livro)
    , ficcao = (ficcao livro)
    , naoFiccao = (naoFiccao livro)
    , romance = (romance livro)
    , horror = (horror livro)
    , biografia = (biografia livro)
    , leitores = (leitores livro)
    , notaGeral = (notaGeral livro)
    }

setaPaginasLivro :: Livro -> Int -> Livro
setaPaginasLivro livro valor =
  Livro
    { idLivro = (idLivro livro)
    , titulo = (titulo livro)
    , autor = (autor livro)
    , paginas = valor
    , ficcao = (ficcao livro)
    , naoFiccao = (naoFiccao livro)
    , romance = (romance livro)
    , horror = (horror livro)
    , biografia = (biografia livro)
    , leitores = (leitores livro)
    , notaGeral = (notaGeral livro)
    }

setaFiccaoLivro :: Livro -> Int -> Livro
setaFiccaoLivro livro valor =
  Livro
    { idLivro = (idLivro livro)
    , titulo = (titulo livro)
    , autor = (autor livro)
    , paginas = (paginas livro)
    , ficcao = valor
    , naoFiccao = (naoFiccao livro)
    , romance = (romance livro)
    , horror = (horror livro)
    , biografia = (biografia livro)
    , leitores = (leitores livro)
    , notaGeral = (notaGeral livro)
    }

setaNaoFiccaoLivro :: Livro -> Int -> Livro
setaNaoFiccaoLivro livro valor =
  Livro
    { idLivro = (idLivro livro)
    , titulo = (titulo livro)
    , autor = (autor livro)
    , paginas = (paginas livro)
    , ficcao = (ficcao livro)
    , naoFiccao = valor
    , romance = (romance livro)
    , horror = (horror livro)
    , biografia = (biografia livro)
    , leitores = (leitores livro)
    , notaGeral = (notaGeral livro)
    }

setaRomanceLivro :: Livro -> Int -> Livro
setaRomanceLivro livro valor =
  Livro
    { idLivro = (idLivro livro)
    , titulo = (titulo livro)
    , autor = (autor livro)
    , paginas = (paginas livro)
    , ficcao = (ficcao livro)
    , naoFiccao = (naoFiccao livro)
    , romance = valor
    , horror = (horror livro)
    , biografia = (biografia livro)
    , leitores = (leitores livro)
    , notaGeral = (notaGeral livro)
    }

setaHorrorLivro :: Livro -> Int -> Livro
setaHorrorLivro livro valor =
  Livro
    { idLivro = (idLivro livro)
    , titulo = (titulo livro)
    , autor = (autor livro)
    , paginas = (paginas livro)
    , ficcao = (ficcao livro)
    , naoFiccao = (naoFiccao livro)
    , romance = (romance livro)
    , horror = valor
    , biografia = (biografia livro)
    , leitores = (leitores livro)
    , notaGeral = (notaGeral livro)
    }

setaBiografiaLivro :: Livro -> Int -> Livro
setaBiografiaLivro livro valor =
  Livro
    { idLivro = (idLivro livro)
    , titulo = (titulo livro)
    , autor = (autor livro)
    , paginas = (paginas livro)
    , ficcao = (ficcao livro)
    , naoFiccao = (naoFiccao livro)
    , romance = (romance livro)
    , horror = (horror livro)
    , biografia = valor
    , leitores = (leitores livro)
    , notaGeral = (notaGeral livro)
    }
