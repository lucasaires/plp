registroLeitura(Usuario) :-
    nl,
    write(" .::. PrompSkoob .::."), nl, nl,
    write(" - Registrar Leitura - "), nl, nl,
    getEstantes(Usuario, Estantes),
    escolheLivro(Estantes, Livro), %_______ banco de dados
	obtemLivrosEstante(Estantes, Livros),
	obtemEstantePorLivro(Estantes, Livro, Estante),
	getPaginasLidas(),
	write("Deixe seu comentario sobre o livro: "), nl,
	read_line_to_string(user_input,Comentario),
	Acao = registraLeitura(Estante,Retorno).%______ banco de dados

	
obtemEstantePorLivro([], Livro, Est) :- write("Este livro nao existe na sua estante").
obtemEstantePorLivro([Estante|Estantes], Livro, Est) :-
	getIdLivroEstante(Estante, idLivroE),
	getIdLivro(Livro, idLivro) -> (idLivroE == idLivro, Est = Estante;
	idLivroE \= idLivro,
obtemEstantePorLivro(Estantes, Livro, Est)).

	
getPaginasLidas(Out) :-
	lerPaginasLidas("Quantas paginas foram lidas? ", Out).

lerPaginasLidas(Mensagem,Out) :-
	write(Mensagem),nl,read_line_to_string(user_input,PaginasLidas), number_string(NewPaginasLidas,PaginasLidas), validaPaginasLidas(NewPaginasLidas, Out).

validaPaginasLidas(NewPaginasLidas, Out) :-
	getPaginas(Livro,NPaginas),
	PaginasLidas > 0, PaginasLidas < NPaginas, Out = PaginasLidas;
	lerPaginasLidas("Digite quantidade de páginas válida: ", Out).






avalicaoLivro(Usuario):-
 nl,
 
 write(" .::. PrompSkoob .::."), nl, nl,
 write(" - Avaliar Livro da Estante  - "), nl, nl,
 
 getEstantes(Usuario, Estantes),
 obtemLivrosEstante(Estantes, Livros),
 
 write("Qual livro da sua estante você deseja avaliar? : "), nl,
 listagemEstante(Usuario),
 getEstantes(Usuario, Estantes),
 
 nl, write("Insira o ID do livro que voce avaliar: "), nl,
 read_line_to_string(user_input, Id),
 atom_string(Atom, Id),
 
 Acao = avaliaLivro(IdUsuario, IdLivro, getNota);



getNota(Out) :-
	lerNota("Escolha uma nota de 1 a 5: ", Out).

lerNota(Mensagem,Out) :-
	write(Mensagem),nl,read_line_to_string(user_input,Nota), avaliaNota(Nota,Out).

avaliaNota(Nota, Out) :-
	number_string(Num,Nota), Num > 0, Num =< 5, Out = Num, write("Faz avaliacao").
 %  no lugar do write("faz avaliacao") colocar a funcao do banco de dados
avaliaNota(Nota,Out) :- lerNota("Digite o valor de acordo com as opcoes dadas: ", Out).

avaliaLivro(IdUsuario, IdLivro, getNota) :- write("avaliado").

