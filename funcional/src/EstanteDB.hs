module EstanteDB where

import           Database.HDBC
import           Database.HDBC.Sqlite3
import           EstanteType
import           LivroDB
import           UsuarioDB

-- Adiciona um livro na estante.
adicionaLivroEstante :: Int -> Int -> IO Bool
adicionaLivroEstante idLivro idUsuario = do
  conexao <- connectSqlite3 "prompskoob.db"
  inserido <- run conexao ("INSERT INTO estante(id_usuario, id_livro) VALUES(?, ?);") [toSql idUsuario, toSql idLivro]
  commit conexao
  disconnect conexao
  return (inserido >= 1)

-- Cria uma tabela de estante.
criaTabelaEstante :: IO ()
criaTabelaEstante = do
  conexao <- connectSqlite3 "prompskoob.db"
  run
    conexao
    ("CREATE TABLE IF NOT EXISTS estante(id_usuario INTEGER NOT NULL, id_livro INTEGER NOT NULL, nota REAL NOT " ++
     "NULL DEFAULT (0), situacao INT NOT NULL DEFAULT(1), paginas_lidas INT DEFAULT (0), comentario TEXT, " ++
     "FOREIGN KEY (id_usuario) REFERENCES usuario(id) ON UPDATE CASCADE ON DELETE CASCADE, FOREIGN KEY (id_livro) " ++
     "REFERENCES livro(id) ON UPDATE CASCADE ON DELETE CASCADE, UNIQUE(id_usuario, id_livro));")
    []
  commit conexao
  disconnect conexao

-- Verifica se o livro ja foi adicionado a estante.
verificaLivroAdicionado :: Int -> Int -> IO Bool
verificaLivroAdicionado idUsuario idLivro = do
  conexao <- connectSqlite3 "prompskoob.db"
  resultado <-
    quickQuery' conexao "SELECT 1 FROM estante WHERE id_usuario = ? AND id_livro = ?;" [toSql idUsuario, toSql idLivro]
  disconnect conexao
  return (length resultado > 0)

mudaSituacao :: Livro -> Usuario -> Int -> IO Bool
mudaSituacao livro usuario situacao = do
  conexao <- connectSqlite3 "prompskoob.db"
  editado <-
    run
      conexao
      ("UPDATE estante SET situacao = ? WHERE id_usuario = ? AND id_livro = ?;")
      [toSql situacao, toSql (idUsuario usuario), toSql (idLivro livro)]
  commit conexao
  disconnect conexao
  return (editado >= 1)

avaliaLivro :: Livro -> Usuario -> Int -> IO Bool
avaliaLivro livro usuario nota = do
  conexao <- connectSqlite3 "prompskoob.db"
  editado <-
    run
      conexao
      ("UPDATE estante SET nota = ? WHERE id_usuario = ? AND id_livro = ?;")
      [toSql nota, toSql (idUsuario usuario), toSql (idLivro livro)]
  commit conexao
  disconnect conexao
  return (editado >= 1)

-- Lista todos os livros da estante.
listaEstantes :: Int -> IO [Estante]
listaEstantes idUsuario = do
  conexao <- connectSqlite3 "prompskoob.db"
  resultado <-
    quickQuery'
      conexao
      ("SELECT e.id_usuario, e.id_livro, e.nota, e.situacao, e.paginas_lidas, COALESCE(e.comentario, ''), l.titulo, l.autor, l.paginas, l.ficcao, l.nao_ficcao, l.romance, l.horror, l.biografia FROM " ++
       "estante e JOIN livro l ON e.id_livro = l.id WHERE id_usuario = ?;")
      [toSql idUsuario]
  disconnect conexao
  if null resultado
    then return []
    else do
      usuario <- consultaUsuario idUsuario
      return (map (preencheEstantes usuario) resultado)

preencheEstantes :: Usuario -> [SqlValue] -> Estante
preencheEstantes usuario [sqlIdUsuario, sqlIdLivro, sqlNota, sqlSituacao, sqlpaginasLidas, sqlComentario, sqlTitulo, sqlAutor, sqlPaginas, sqlFiccao, sqlNaoFiccao, sqlRomance, sqlHorror, sqlBiografia] =
  Estante
    { idUsuarioEstante = fromSql sqlIdUsuario :: Int
    , idLivroEstante = fromSql sqlIdLivro :: Int
    , nota = fromSql sqlNota :: Double
    , situacao = fromSql sqlSituacao :: Int
    , paginasLidas = fromSql sqlpaginasLidas :: Int
    , comentario = fromSql sqlComentario :: String
    , livro =
        Livro
          { idLivro = fromSql sqlIdLivro :: Int
          , titulo = fromSql sqlTitulo :: String
          , autor = fromSql sqlAutor :: String
          , paginas = fromSql sqlPaginas :: Int
          , ficcao = fromSql sqlFiccao :: Int
          , naoFiccao = fromSql sqlNaoFiccao :: Int
          , romance = fromSql sqlRomance :: Int
          , horror = fromSql sqlHorror :: Int
          , biografia = fromSql sqlBiografia :: Int
          , leitores = 0
          , notaGeral = 0.0
          }
    , usuario = usuario
    }

-- Remove um livro da base de dados.
removeLivroEstante :: Livro -> Usuario -> IO Bool
removeLivroEstante livro usuario = do
  conexao <- connectSqlite3 "prompskoob.db"
  removido <-
    run
      conexao
      "DELETE FROM estante WHERE id_livro = ? AND id_usuario = ?;"
      [toSql (idLivro livro), toSql (idUsuario usuario)]
  commit conexao
  disconnect conexao
  return (removido >= 1)
