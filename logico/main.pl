:- initialization main.

main(X):-
    repeat,
    write(".::. PrompSkoob .::." ),
    write(" - Menu Principal - "), 
    write(" Ola, "),
    write(" (1) Editar meu perfil"),
    write(" (2) Gerenciar livro"),
    write(" (3) Minha estante"),
    write(" (4) Pesquisar no acervo"),
    write(" (5) Recomendações de livros"),
    write(" (6) Remover meu perfil"),
    write(" (7) Sair da conta"),
    write(" (8) Sair"),
    write("Opcao: "),
    read(X),
    (X == 1 -> editarPerfil();
     X == 2 -> gerenciarLivro();
     X == 3 -> minhaEstante();
     X == 4 -> pesquisarAcervo();
     X == 5 -> recomendaçõesLivros();
     X == 6 -> removerPerfil();
     X == 7 -> sairConta();
     X == 8 -> sair()),
    halt(0).


editarPerfil():-
    write("Até Breve! ").

gerenciarLivro():-
    write("Até Breve! ").

minhaEstante():-
    write("Até Breve! ").
    

pesquisarAcervo:-
    write("Até Breve! ").
    

recomendaçõesLivros:-
    write("Até Breve! ").

removerPerfil:-
    write("Até Breve! ").

sairConta:-
    write("Até Breve! ").


sair:-
    write("Até Breve! ").
    
    
    





