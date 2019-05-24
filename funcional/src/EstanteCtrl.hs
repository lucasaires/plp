module EstanteCtrl where

import           EstanteType
import           Utilitario

-- Exibe todos os livros adicionados a estante.
exibeLivrosEstante :: [Estante] -> Int -> IO ()
exibeLivrosEstante estantes 0 = exibeMensagem "Nenhum livro adicionado a sua estante!"
exibeLivrosEstante [] tamanho = putStrLn ""
exibeLivrosEstante (l:ls) tamanhoEstante = do
  putStrLn
    ("#" ++
     show (idLivroEstante l) ++
     " - " ++
     titulo (livro l) ++
     " - " ++
     (autor (livro l)) ++
     " (" ++ show (paginas (livro l)) ++ "pgs) [" ++ obtemSituacao (situacao l) ++ "] - Minha Nota: " ++ show (nota l))
  exibeLivrosEstante ls tamanhoEstante
