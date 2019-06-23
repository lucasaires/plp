
listagemEstante(Usuario) :-
    %listaLivrosEstante(Usuario) == 1, getEstantes(Usuario, Estantes), size(Estantes, Size), printaEstante(Estantes, Size).    
    getEstantes(Usuario, Estantes), 
    size(Estantes, Size), 
    printaEstante(Estantes, Size).

size([], 0).
size([X:Xs], Size) :- size(Xs, S), Size is S + 1.

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

remocaoLivroEstante(Usuario) :-
    nl,
    write(" .::. PrompSkoob .::."),
    write(" - Remover Livro da Estante - "), nl,
    getEstantes(Usuario, Estantes),
    obtemLivrosEstante,
    escolheLivro().

obtemLivrosEstante([], []).
obtemLivrosEstante([Estante|Estantes], [Livro|Livros]):-
    %getLivro(Estante, L),
    %Livro = L,
    Livro is Estante;
    obtemLivrosEstante(Estantes, Livros).

teste(E) :- obtemLivrosEstante(E, X), write(X).

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

