

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
	write(Mensagem),nl,read_line_to_string(user_input,Nota), number_string(NewNota,Nota), avaliaNota(NewNota,Out).

avaliaNota(NewNota, Out) :-
	Nota > 0, Nota =< 5, Out = Nota;
	lerNota("Digite um valor de acordo com as opcoes dadas: ", Out).
 

avaliaLivro(IdUsuario, IdLivro, getNota) :- write("avaliado").

