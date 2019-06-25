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
    halt(0).
    
    
     





