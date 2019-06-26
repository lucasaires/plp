:- initialization main.

main:-
    write(".::. PrompSkoob .::.
    - Menu Principal -  
    Ola
    (1) Editar meu perfil
    (2) Gerenciar livro
    (3) Minha estante
    (4) Pesquisar no acervo
    (5) Recomendações de livros
    (6) Remover meu perfil
    (7) Sair da conta
    (8) Sair
    Opcao: "),
    read(X),
    (X == 1 -> editarPerfil(X);
     X == 2 -> gerenciarLivro();
     X == 3 -> minhaEstante();
     X == 4 -> pesquisarAcervo();
     X == 5 -> recomendaçõesLivros();
     X == 6 -> removerPerfil();
     X == 7 -> sairConta();
     X == 8 -> sair()).


editarPerfil(X):- 
    (X == 1 -> write("Até Breve! ")).

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
    
    
    





