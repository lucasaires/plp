module LivroDB where

import           Database.HDBC
import           Database.HDBC.Sqlite3
import           EstanteType

-- Cria uma tabela de livro
criaTabelaLivro :: IO ()
criaTabelaLivro = do
  conexao <- connectSqlite3 "prompskoob.db"
  run
    conexao
    ("CREATE TABLE IF NOT EXISTS livro(id INTEGER PRIMARY KEY NOT NULL, titulo TEXT NOT NULL, autor TEXT NOT NULL, " ++
     "paginas INT NOT NULL DEFAULT (0), ficcao INT DEFAULT (0), nao_ficcao INT DEFAULT (0), romance INT DEFAULT (0), " ++
     "horror INT  DEFAULT (0), biografia INT DEFAULT (0));")
    []
  commit conexao
  disconnect conexao

-- Consulta o livro por id.
consultaLivro :: Int -> IO Livro
consultaLivro codigo = do
  conexao <- connectSqlite3 "prompskoob.db"
  resultado <- quickQuery' conexao "SELECT * FROM livro WHERE id = ? LIMIT 1;" [toSql codigo]
  disconnect conexao
  if null resultado
    then return (obtemLivroNulo)
    else return (preencheLivro (head resultado))

-- Insere um livro no banco.
insereLivro :: Livro -> IO Bool
insereLivro livro = do
  conexao <- connectSqlite3 "prompskoob.db"
  inserido <-
    run
      conexao
      ("INSERT INTO livro(titulo, autor, paginas, ficcao, nao_ficcao, romance, horror, biografia) VALUES " ++
       "(?, ?, ?, ?, ?, ?, ?, ?);")
      [ toSql (titulo livro)
      , toSql (autor livro)
      , toSql (paginas livro)
      , toSql (ficcao livro)
      , toSql (naoFiccao livro)
      , toSql (romance livro)
      , toSql (horror livro)
      , toSql (biografia livro)
      ]
  commit conexao
  disconnect conexao
  return (inserido >= 1)

-- Lista todos os livros cadastrados no banco.
listaLivros :: IO [Livro]
listaLivros = do
  conexao <- connectSqlite3 "prompskoob.db"
  resultado <-
    quickQuery'
      conexao
      ("SELECT *, COALESCE((SELECT COUNT(id_livro) FROM estante WHERE id_livro = id), 0.0) AS leitores, " ++
       "COALESCE((SELECT AVG(nota) FROM estante WHERE id_livro = id), 0.0) AS nota_geral FROM livro;")
      []
  disconnect conexao
  if null resultado
    then return []
    else return (map preencheLivros resultado)

-- Remove um livro da base de dados.
removeLivro :: Int -> IO Bool
removeLivro codigo = do
  conexao <- connectSqlite3 "prompskoob.db"
  removido <- run conexao "DELETE FROM livro WHERE id = ?;" [toSql codigo]
  commit conexao
  disconnect conexao
  return (removido >= 1)

recomendaLivros :: Usuario -> IO [Livro]
recomendaLivros usuario = do
  conexao <- connectSqlite3 "prompskoob.db"
  resultado <-
    quickQuery'
      conexao
      ("SELECT *, COALESCE((SELECT COUNT(id_livro) FROM estante WHERE id_livro = id), 0) AS leitores, COALESCE((SELECT AVG(nota) FROM " ++
       "estante WHERE id_livro = id), 0.0) AS nota_geral FROM livro WHERE " ++
       whereFiccao ++ whereNaoFiccao ++ whereRomance ++ whereHorror ++ whereBiografia ++ whereCoringa)
      []
  disconnect conexao
  if null resultado
    then return []
    else return (map preencheLivros resultado)
  where
    whereFiccao =
      if gostaFiccao usuario == 1
        then "ficcao = 1 OR "
        else ""
    whereNaoFiccao =
      if gostaNaoFiccao usuario == 1
        then "nao_ficcao = 1 OR "
        else ""
    whereRomance =
      if gostaRomance usuario == 1
        then "romance = 1 OR "
        else ""
    whereHorror =
      if gostaHorror usuario == 1
        then "horror = 1 OR "
        else ""
    whereBiografia =
      if gostaBiografia usuario == 1
        then "biografia = 1 OR "
        else ""
    whereCoringa = " FALSE;"

editaLivro :: Livro -> IO Livro
editaLivro livro = do
  conexao <- connectSqlite3 "prompskoob.db"
  run
    conexao
    ("UPDATE livro SET titulo = ?, autor = ?, paginas = ?, ficcao = ?, nao_ficcao = ?, romance = ?, horror = ?, " ++
     "biografia = ? WHERE id = ?;")
    [ toSql (titulo livro)
    , toSql (autor livro)
    , toSql (paginas livro)
    , toSql (ficcao livro)
    , toSql (naoFiccao livro)
    , toSql (romance livro)
    , toSql (horror livro)
    , toSql (biografia livro)
    , toSql (idLivro livro)
    ]
  commit conexao
  disconnect conexao
  livroEditado <- consultaLivro (idLivro livro)
  return (livroEditado)

pesquisaLivros :: String -> IO [Livro]
pesquisaLivros titulo = do
  conexao <- connectSqlite3 "prompskoob.db"
  resultado <-
    quickQuery'
      conexao
      ("SELECT *, COALESCE((SELECT COUNT(id_livro) FROM estante WHERE id_livro = id),0) AS leitores, COALESCE((SELECT AVG(nota) FROM " ++
       "estante WHERE id_livro = id),0) AS nota_geral FROM livro WHERE titulo like '%" ++ titulo ++ "%';")
      []
  disconnect conexao
  if null resultado
    then return []
    else return (map preencheLivros resultado)

preencheLivro :: [SqlValue] -> Livro
preencheLivro [sqlId, sqlNome, sqlAutor, sqlPaginas, sqlFiccao, sqlNaoFiccao, sqlRomance, sqlHorror, sqlBiografia] =
  Livro
    { idLivro = codigoSql
    , titulo = nomeSql
    , autor = autorSql
    , paginas = paginasSql
    , ficcao = ficcaoSql
    , naoFiccao = naoFiccaoSql
    , romance = romanceSql
    , horror = horrorSql
    , biografia = biografiaSql
    , leitores = 0
    , notaGeral = 0.0
    }
  where
    codigoSql = fromSql sqlId :: Int
    nomeSql = fromSql sqlNome :: String
    autorSql = fromSql sqlAutor :: String
    paginasSql = fromSql sqlPaginas :: Int
    ficcaoSql = fromSql sqlFiccao :: Int
    naoFiccaoSql = fromSql sqlNaoFiccao :: Int
    romanceSql = fromSql sqlRomance :: Int
    horrorSql = fromSql sqlHorror :: Int
    biografiaSql = fromSql sqlBiografia :: Int

preencheLivros :: [SqlValue] -> Livro
preencheLivros [sqlId, sqlNome, sqlAutor, sqlPaginas, sqlFiccao, sqlNaoFiccao, sqlRomance, sqlHorror, sqlBiografia, sqlLeitores, sqlNotaGeral] =
  Livro
    { idLivro = codigoSql
    , titulo = nomeSql
    , autor = autorSql
    , paginas = paginasSql
    , ficcao = ficcaoSql
    , naoFiccao = naoFiccaoSql
    , romance = romanceSql
    , horror = horrorSql
    , biografia = biografiaSql
    , leitores = leitoresSql
    , notaGeral = notaGeralSql
    }
  where
    codigoSql = fromSql sqlId :: Int
    nomeSql = fromSql sqlNome :: String
    autorSql = fromSql sqlAutor :: String
    paginasSql = fromSql sqlPaginas :: Int
    ficcaoSql = fromSql sqlFiccao :: Int
    naoFiccaoSql = fromSql sqlNaoFiccao :: Int
    romanceSql = fromSql sqlRomance :: Int
    horrorSql = fromSql sqlHorror :: Int
    biografiaSql = fromSql sqlBiografia :: Int
    leitoresSql = fromSql sqlLeitores :: Int
    notaGeralSql = fromSql sqlNotaGeral :: Double

obtemLivroNulo :: Livro
obtemLivroNulo = Livro 0 "NULL" "NULL" 0 0 0 0 0 0 0 0.0

isLivroNulo :: Livro -> Bool
isLivroNulo livro
  | (idLivro livro == 0) && (titulo livro == "NULL") = True
  | otherwise = False
