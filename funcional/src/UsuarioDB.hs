module UsuarioDB where

import           Database.HDBC
import           Database.HDBC.Sqlite3
import           EstanteType

-- Autentica usuario atraves do email e senha.
autenticaUsuario :: String -> String -> IO Usuario
autenticaUsuario email senha = do
  conexao <- connectSqlite3 "prompskoob.db"
  resultado <- quickQuery' conexao "SELECT * FROM usuario WHERE email = ? AND senha = ?;" [toSql email, toSql senha]
  disconnect conexao
  if null resultado
    then return (obtemUsuarioNulo)
    else return (preencheUsuario (head resultado))

-- Cria uma tabela de usuario.
criaTabelaUsuario :: IO ()
criaTabelaUsuario = do
  conexao <- connectSqlite3 "prompskoob.db"
  run
    conexao
    ("CREATE TABLE IF NOT EXISTS usuario(id INTEGER PRIMARY KEY NOT NULL, nome TEXT NOT NULL, email TEXT NOT NULL " ++
     "UNIQUE, senha TEXT NOT NULL, ficcao INT DEFAULT (0), nao_ficcao INT DEFAULT (0), romance INT DEFAULT (0), " ++
     "horror INT DEFAULT (0), biografia INT DEFAULT (0));")
    []
  commit conexao
  disconnect conexao

-- Remove o usuario do sistema.
removeUsuario :: Int -> IO Bool
removeUsuario idUsuario = do
  conexao <- connectSqlite3 "prompskoob.db"
  removido <- run conexao "DELETE FROM usuario WHERE id = ?;" [toSql idUsuario]
  commit conexao
  disconnect conexao
  return (removido >= 1)

-- Verifica se o e-mail ja foi cadastrado no banco de dados
verificaSeEmailExiste :: String -> IO Bool
verificaSeEmailExiste email = do
  conexao <- connectSqlite3 "prompskoob.db"
  resultado <- quickQuery' conexao "SELECT id FROM usuario WHERE email = ?;" [toSql email]
  disconnect conexao
  return (size resultado > 0)

-- Insere um novo usuario no sistema.
insereUsuario :: Usuario -> IO Bool
insereUsuario usuario = do
  conexao <- connectSqlite3 "prompskoob.db"
  inserido <-
    run
      conexao
      ("INSERT INTO usuario(nome, email, senha, ficcao, nao_ficcao, romance, horror, biografia) VALUES " ++
       "(?, ?, ?, ?, ?, ?, ?, ?);")
      [ toSql (nome usuario)
      , toSql (email usuario)
      , toSql (senha usuario)
      , toSql (gostaFiccao usuario)
      , toSql (gostaNaoFiccao usuario)
      , toSql (gostaRomance usuario)
      , toSql (gostaHorror usuario)
      , toSql (gostaBiografia usuario)
      ]
  commit conexao
  disconnect conexao
  return (inserido >= 1)

consultaUsuario :: Int -> IO Usuario
consultaUsuario codigo = do
  conexao <- connectSqlite3 "prompskoob.db"
  resultado <- quickQuery' conexao "SELECT * FROM usuario WHERE id = ? LIMIT 1;" [toSql codigo]
  disconnect conexao
  return (preencheUsuario (head resultado))

editaUsuario :: Usuario -> IO Usuario
editaUsuario usuario = do
  conexao <- connectSqlite3 "prompskoob.db"
  run
    conexao
    ("UPDATE usuario SET nome = ?, email = ?, senha = ?, ficcao = ?, nao_ficcao = ?, romance = ?, horror = ?, " ++
     "biografia = ? WHERE id = ?;")
    [ toSql (nome usuario)
    , toSql (email usuario)
    , toSql (senha usuario)
    , toSql (gostaFiccao usuario)
    , toSql (gostaNaoFiccao usuario)
    , toSql (gostaRomance usuario)
    , toSql (gostaHorror usuario)
    , toSql (gostaBiografia usuario)
    , toSql (idUsuario usuario)
    ]
  commit conexao
  disconnect conexao
  usuarioEditado <- consultaUsuario (idUsuario usuario)
  return (usuarioEditado)

preencheUsuario :: [SqlValue] -> Usuario
preencheUsuario [sqlId, sqlNome, sqlEmail, sqlSenha, sqlFiccao, sqlNaoFiccao, sqlRomance, sqlHorror, sqlBiografia] =
  Usuario
    { idUsuario = codigoSql
    , nome = nomeSql
    , email = emailSql
    , senha = senhaSql
    , gostaFiccao = ficcaoSql
    , gostaNaoFiccao = naoFiccaoSql
    , gostaRomance = romanceSql
    , gostaHorror = horrorSql
    , gostaBiografia = biografiaSql
    , estantes = []
    }
  where
    codigoSql = fromSql sqlId :: Int
    nomeSql = fromSql sqlNome :: String
    emailSql = fromSql sqlEmail :: String
    senhaSql = fromSql sqlSenha :: String
    ficcaoSql = fromSql sqlFiccao :: Int
    naoFiccaoSql = fromSql sqlNaoFiccao :: Int
    romanceSql = fromSql sqlRomance :: Int
    horrorSql = fromSql sqlHorror :: Int
    biografiaSql = fromSql sqlBiografia :: Int

obtemUsuarioNulo :: Usuario
obtemUsuarioNulo = Usuario 0 "NULL" "NULL" "NULL" 0 0 0 0 0 []

isUsuarioNulo :: Usuario -> Bool
isUsuarioNulo usuario
  | (idUsuario usuario == 0) && (nome usuario == "NULL") = True
  | otherwise = False
