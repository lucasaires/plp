:- style_check(-singleton).
:- [utilitario].
:- [usuario].
:- [livro].
:- [estante].
:- [estantedb].
:- initialization(main).

main:-
    inicializa,
    exibe_menu_visitante.

% Autentica usuario.
autenticacao:-
    (exibe_autenticacao(Usuario) -> 
    exibe_mensagem('Seja bem-vindo.'), 
    exibe_menu(Usuario);
    exibe_mensagem('Nao existe usuario com o e-mail e/ou senha informados.'),
    exibe_menu_visitante).

% Cadastra o usuario.
cadastro_usuario:-
    (exibe_cadastro_usuario -> 
    exibe_mensagem('Perfil criado com sucesso!'); 
    exibe_mensagem('Nao foi possivel criar o perfil do usuario.')),
    exibe_menu_visitante.

% Edita o perfil do usuario.
edita_perfil(Usuario):-
    (exibe_edicao_perfil(Usuario, UsuarioEditado) -> 
    exibe_mensagem('Perfil editado com sucesso.'),
    exibe_menu(UsuarioEditado); 
    exibe_mensagem('Ops! Perfil nao editado.'),
    exibe_menu(Usuario)).

% Exibe o menu de visitante.
exibe_menu(Usuario):-
    exibe_topo_menu('Menu Principal'),
    obtem_nome(Usuario, Nome),
    write('Ola, '),
    write(Nome),
    writeln('!'),
    writeln('(1) Editar meu perfil'),
    writeln('(2) Gerenciar livro'),
    writeln('(3) Minha estante'),
    writeln('(4) Pesquisar Acervo'),
    writeln('(5) Recomendações de livros'),
    writeln('(6) Remover meu perfil'),
    writeln('(7) Sair da conta'),
    writeln('(8) Sair'),
    ler_opcao(Opcao),
    opcao_escolhida_usuario(Opcao, Usuario).

% Exibe o menu de visitante.
exibe_menu_visitante:-
    exibe_topo_menu('Menu Principal'),
    writeln('Ola, visitante!'),
    writeln('(1) Quero me cadastrar'),
    writeln('(2) Autenticacao'),
    writeln('(3) Pesquisar Acervo'),
    writeln('(4) Sair'),
    ler_opcao(Opcao),
    opcao_escolhida_visitante(Opcao).

% Exibe o menu de livro.
gerencia_estante(Usuario):-
    exibe_topo_menu('Minha estante'),
    lista_estantes(Usuario, Estantes),
    length(Estantes, Tamanho),
    exibe_estantes(Estantes, Tamanho), nl,
    writeln('(1) Mudar Status | (2) Avaliar | (3) Remover | (4) Voltar'),
    ler_opcao(Opcao),
    opcao_escolhida_estante(Opcao, Usuario, Estantes).

% Inicializa o banco de dados, criando as tabelas.
inicializa :-
    cria_tabela_usuario,
    cria_tabela_estante,
    cria_tabela_livro.

% Mudanca de situacao de livro da estante.
mudanca_situacao(Usuario, Estantes):-
    (exibe_mudanca_situacao(Usuario, Estantes) -> 
    exibe_mensagem('Status modificado com sucesso!'); 
    exibe_mensagem('Nao foi possivel mudar a situacao.')),
    gerencia_estante(Usuario).

% Avaliacaode livro da estante.
avaliacao_livro(Usuario, Estantes):-
    (exibe_avaliacao_livro(Usuario, Estantes) -> 
    exibe_mensagem('Avaliacao realizada com sucesso!'); 
    exibe_mensagem('Nao foi possivel realizar a avaliacao.')),
    gerencia_estante(Usuario).

% Remove livro da estante.
remocao_estante(Usuario, Estantes):-
    (exibe_remocao_estante(Usuario, Estantes, gerencia_estante(Usuario)) -> 
    exibe_mensagem('Livro removido da estante com sucesso!'); 
    exibe_mensagem('Nao foi possivel remover o livro da estante.')),
    gerencia_estante(Usuario).

% Exibe livros recomendados.
recomendacoes_livro(Usuario):-
    exibe_topo_menu('Recomendacoes de livros'),
    recomenda_livros(Usuario, Livros),
    length(Livros, Tamanho),
    exibe_livros(Livros, Tamanho), nl,
    exibe_menu(Usuario).

% Exibe livros recomendados.
filtragem_acervo:-
    exibe_topo_menu('Pesquisar Acervo'),
    ler_entrada_texto('Pesquise pelo titulo: ', Titulo),
    pesquisa_livros(Titulo, Livros),
    length(Livros, Tamanho),
    exibe_mensagem('Resultados encontrados: '),
    exibe_livros(Livros, Tamanho), nl,
    exibe_menu_visitante.

% Exibe livros recomendados.
pesquisa_acervo(Usuario):-
    exibe_topo_menu('Pesquisar Acervo'),
    ler_entrada_texto('Pesquise pelo titulo: ', Titulo),
    pesquisa_livros(Titulo, Livros),
    length(Livros, Tamanho),
    exibe_mensagem('Resultados encontrados: '),
    exibe_livros(Livros, Tamanho), nl,
    exibe_menu(Usuario).

% Opcoes de escolha do submenu de estante.
opcao_escolhida_estante(1, Usuario, Estantes):- mudanca_situacao(Usuario, Estantes).
opcao_escolhida_estante(2, Usuario, Estantes):- avaliacao_livro(Usuario, Estantes).
opcao_escolhida_estante(3, Usuario, Estantes):- remocao_estante(Usuario, Estantes).
opcao_escolhida_estante(4, Usuario, Estantes):- exibe_menu(Usuario).
opcao_escolhida_estante(_, Usuario, Estantes):- opcao_invalida(gerencia_estante(Usuario)).

% Executa de acordo com a opcao escolhida.
opcao_escolhida_visitante(1):- cadastro_usuario.
opcao_escolhida_visitante(2):- autenticacao.    
opcao_escolhida_visitante(3):- filtragem_acervo.    
opcao_escolhida_visitante(4):- sair.
opcao_escolhida_visitante(_):- opcao_invalida(exibe_menu_visitante).

% Executa de acordo com a opcao escolhida quando usuario logado.
opcao_escolhida_usuario(1, Usuario):- edita_perfil(Usuario).
opcao_escolhida_usuario(2, Usuario):- gerencia_livro(Usuario, exibe_menu(Usuario)).
opcao_escolhida_usuario(3, Usuario):- gerencia_estante(Usuario).
opcao_escolhida_usuario(4, Usuario):- pesquisa_acervo(Usuario).
opcao_escolhida_usuario(5, Usuario):- recomendacoes_livro(Usuario).
opcao_escolhida_usuario(6, Usuario):- remocao_perfil(Usuario).
opcao_escolhida_usuario(7, _):- exibe_menu_visitante.
opcao_escolhida_usuario(8, _):- sair.
opcao_escolhida_usuario(_, Usuario):- opcao_invalida(exibe_menu(Usuario)).

% Remove o perfil atual do usuario.
remocao_perfil(Usuario):-
    (exibe_remocao_perfil(Usuario, exibe_menu(Usuario)) -> 
    exibe_mensagem('Perfil removido com sucesso!'),
    exibe_menu_visitante; 
    exibe_mensagem('Ops! Perfil nao removido.'),
    exibe_menu(Usuario)).

% Sai do fluxo do programa.
sair:- 
    exibe_mensagem('Ate breve... :)'),
    halt(0).