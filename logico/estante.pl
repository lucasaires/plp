

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
 %  no ligar do write("faz avaliacao") colocar a funcao do banco de dados
avaliaNota(Nota,Out) :- lerNota("Digite o valor de acordo com as opcoes dadas: ", Out).

avaliaLivro(IdUsuario, IdLivro, getNota) :- write("avaliado").

