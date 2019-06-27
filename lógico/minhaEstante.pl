
listagemEstante(Usuario) :-
    %listaLivrosEstante(Usuario) == 1, getEstantes(Usuario, Estantes), size(Estantes, Size), printaEstante(Estantes, Size).    
    getEstantes(Usuario, Estantes), 
    size(Estantes, Size), 
    printaEstante(Estantes, Size).

size([], 0).
size([X|Xs], Size) :- size(Xs, S), Size is S + 1.

printaEstante(_, 0) :- write("Nunhum livro adicionado a sua estante!").
printaEstante([], Size) :- write("").
printaEstante([Estante|Estantes], Size) :-
    stringEstante(Estante),
    printaEstante(Estantes, Size).

stringEstante(Estante) :-
    getIdLivroEstante(Estante, IdLivroE),
    getLivro(Estante, Livro),
    getTitulo(Livro, Titulo),
    getAutor(Livro, Autor),
    getNPaginas(Livro, Paginas),
    getSituacao(Estante, Sit),
    obtemSituacao(Sit, Situacao),
    getNota(Estante, Nota),
    string_concat("#", IdLivroE, Part1),
    string_concat(Part1, " - ", Part2),
    string_concat(Part2, Titulo, Part3),
    string_concat(Part3, " - ", Part4),
    string_concat(Part4, Autor, Part5),
    string_concat(Part5, " (", Part6),
    string_concat(Part6, Paginas, Part7),
    string_concat(Part7, "pgs) [", Part8),
    string_concat(Part8, Situacao, Part9),
    string_concat(Part9, "] - Minha Nota: ", Part10),
    string_concat(Part10, Nota, Part11),
    write(Part11), nl.

removerLivroEstante(Usuario) :-
    nl,
    write(" .::. PrompSkoob .::."), nl, nl,
    write(" - Removendo livros da minha estante - "), nl, nl,
    %getEstantes(Usuario, Estantes),
    %obtemLivrosEstante(Estantes, Livros),
    write("Livros na sua Estante : "), nl,
    %listagemEstante(Usuario),
    getEstantes(Usuario, Estantes),
    nl, write("Insira o ID do livro que voce deseja remover da sua estante: "), nl,
    read_line_to_string(user_input, String),
    atom_string(Atom, String),
    %getIdUsuario(Usuario, IdUsuario),    
    verificaExistenciaLivro(Estantes, Estantes, Atom, Usuario).

verificaExistenciaLivro([], Estantes, IdLivro, Usuario) :- 
    write("Livro nao existe na sua estante."), nl, nl,
    write("Insira um ID valido: "),
    read_line_to_string(user_input, String),
    atom_string(Atom, String),
    verificaExistenciaLivro(Estantes, Estantes, IdLivro, Usuario).
verificaExistenciaLivro([Estante|Estantes], Est, Estante, Usuario) :- removeEstante(0, Estante).
verificaExistenciaLivro([Estante|Estantes], Est, IdLivro, Usuario) :- verificaExistenciaLivro(Estantes, Est, IdLivro, IdUsuario).



    %getIdLivroEstante(Estante, ID),
    %getIdUsuario(Usuario, IdUsuario),
    %ID == IdLivro -> (removeEstante(IdUsuario, IdLivro)),
    %ID \= IdLivro -> (verificaExistenciaLivro(Estantes, Est, IdLivro, IdUsuario)).

removeEstante(IdUsuario, IdLivro) :- write("removido").

obtemLivrosEstante([], []).
obtemLivrosEstante([Estante|Estantes], [Livro|Livros]):-
    getLivro(Estante, L),
    Livro = L,
    obtemLivrosEstante(Estantes, Livros).

adicionaLivroMinhaEst(Usuario) :- 
    nl, write(" .::. PrompSkoob .::."), nl,
    write(" - Adicionando livros a minha estante - "), nl, nl,
    %listaLivros(Livros),
    %escolheLivro(Livros, Livro), %__________________FUNCAO DO DB
    %getIdUsuario(Usuario, IdUsuario),
    %getIdLivro(Livro, IdLivro),
    %adicionaLivroEstanteDB(IdUsuario, IdLivro, Sucesso) ->( %___________FUNCAO DO DB
    %Sucesso == 1, write("Livro adicionado a sua estante com sucesso.");
    %Sucesso \= 1, write("Ocorreu um erro ao adicionar livro na estante: ")),
    write("Deseja adicionar outro livro a sua estante: (S/N) "), nl,
    read_line_to_string(user_input, Entrada),
    Acao = adicionaLivroMinhaEst(Usuario),
    %Acao2 = menuEstante(Usuario),
    verificaEntradaSN(Entrada, Usuario, Acao).       
    
verificaEntradaSN("S", Usuario, Acao) :- Acao.
verificaEntradaSN("s", Usuario, Acao) :- Acao.
verificaEntradaSN("N", Usuario, Acao) :- write("valido N"). % _______________RETORNA PARA MENU
verificaEntradaSN("n", Usuario, Acao) :- write("valido N"). %________________RETORNA PARA MUNU
verificaEntradaSN(Entrada, Usuario, Acao) :- 
    nl, write("Entrada invalida!"), nl,
    write("Por favor insira uma entrada valida: "), nl,
    read_line_to_string(user_input, NewEntrada), 
    verificaEntradaSN(NewEntrada, Usuario, Acao).

mudarSt

%______________________ESTANTE________________________
getIdLivroEstante(estante(IdLivroE,_,_,_,_,_), IdLivroE).
getIdEstante(estante(_,IdEstante,_,_,_,_),IdEstante).
getUsuario(estante(_,_,Usuario,_,_,_),Usuario).
getLivro(estante(_,_,_,Livro,_,_),Livro).
getNota(estante(_,_,_,_,Nota,_),Nota).
getSituacao(estante(_,_,_,_,_,Situacao), Situacao).

%________________________USUARIO_____________________________
getIdUsuario(usuario(IdUsuario,_,_,_,_,_,_,_,_,_), IdUsuario).
getNome(usuario(_,Nome,_,_,_,_,_,_,_,_), Nome).
getEmail(usuario(_,_,Email,_,_,_,_,_,_,_), Email).
getSenha(usuario(_,_,_,Senha,_,_,_,_,_,_), Senha).
getGostaFiccao(usuario(_,_,_,_,Ficcao,_,_,_,_,_), Ficcao).
getGostaNaoFiccao(usuario(_,_,_,_,_,NaoFiccao,_,_,_,_), NaoFiccao).
getGostaRomance(usuario(_,_,_,_,_,_,Romance,_,_,_), Romance).
getGostaHorror(usuario(_,_,_,_,_,_,_,Horror,_,_), Horror).
getGostaBiografia(usuario(_,_,_,_,_,_,_,_,Biografia,_), Biografia).
getEstantes(usuario(_,_,_,_,_,_,_,_,_,Estantes), Estantes).

%________________________LIVRO__________________________
getIdLivro(livro(IdLivro,_,_,_,_,_,_,_,_,_,_), IdLivro).
getTitulo(livro(_,Titulo,_,_,_,_,_,_,_,_,_), Titulo).
getAutor(livro(_,_,Autor,_,_,_,_,_,_,_,_), Autor).
getPaginas(livro(_,_,_,Paginas,_,_,_,_,_,_,_), Paginas).
getFiccao(livro(_,_,_,_,Ficcao,_,_,_,_,_,_), Ficcao).
getNaoFiccao(livro(_,_,_,_,_,NaoFiccao,_,_,_,_,_), NaoFiccao).
getRomance(livro(_,_,_,_,_,_,Romance,_,_,_,_), Romance).
getHorror(livro(_,_,_,_,_,_,_,Horror,_,_,_), Horror).
getBiografia(livro(_,_,_,_,_,_,_,_,Biografia,_,_), Biografia).
getLeitores(livro(_,_,_,_,_,_,_,_,_,Leitores,_), Leitores).
getNotaGeral(livro(_,_,_,_,_,_,_,_,_,_,NotaGeral), NotaGeral).

