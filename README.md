# PrompSkoob
> Uma versão minimalista do site Skoob para gerenciamento de estante de livros. Projeto desenvolvido para disciplina de
Paradigmas de Linguagens de Programação da UFCG.

## Desenvolvedores

- Álex Micaela de Oliveira Fidelis `<alex.fidelis@ccc.ufcg.edu.br>`
- Caio Benjamim Lima Simplício `<caio.simplicio@ccc.ufcg.edu.br>`
- Caroliny Mylena Bezerra e Silva `<caroliny.silva@ccc.ufcg.edu.br>`
- Júlia Fernandes Alves `<julia.alves@ccc.ufcg.edu.br>`
- Lucas Gomes Aires `<lucas.aires@ccc.ufcg.edu.br>`

## Sobre

O **PrompSkoob** é um mini programa para organização de leituras e livros. O usuário poderá criar sua conta, e assim
usufruir de recursos como recomendações de livros, registro de leitura, gerenciar o acervo geral de livros e muito mais.
Mas, caso prefira, poderá acessá-lo como visitante, podendo consultar os livros do acervo, visualizar a nota de avaliação
dada por usuários do **PrompSkoob**.

## Funcionalidades

### Menu Principal

![Menu Principal Logado](./imperativo/docs/fig1.png)

*Figura 01: Menu principal quando usuário está autenticado.*

![Menu Principal Visitante](./imperativo/docs/fig2.png)

*Figura 02: Menu principal quando usuário é visitante.*

### Funcionalidade 01: Quero me Cadastrar

![Cadastro Usuário](./imperativo/docs/fig3.png)

*Figura 03:  Exibição  quando usuário escolhe a opção [1] para efetuar o cadastro de usuário.*

Será exibido um submenu para o usuário confirme se deseja se cadastrar ou voltar para o menu anterior.

O usuário poderá  se cadastrar no PrompSkoob para ter acesso a recursos exclusivos.

O usuário deverá cadastrar os seguintes campos: **nome** (obrigatório),  **e-mail** (único e obrigatório) que será utilizado para autenticação no programa, **senha** de acesso (obrigatório) e a escolha de **interesses** de gêneros de livros que poderá ser utilizado no futuro para recomendação de livros. Após concluído o cadastrado o menu principal irá mudar para o menu visitante (figura 02).

Caso ocorra algum erro ao registrar as informações será exibido um mensagem de erro.

### Funcionalidade 02: Autenticação

![Autenticação Usuário](./imperativo/docs/fig4.png)

*Figura 04: Exibição  quando usuário escolhe a opção [2] para efetuar a autenticação do usuário.*

Ao escolher a opção `[2]` o usuário poderá realizar autenticação utilizando o e-mail e senha definido no momento do 
cadastro. Os campos **e-mail** (obrigatório) e **senha** (obrigatório).

Caso não exista um usuário com e-mail e senha válido será exibida uma mensagem de erro.

### Funcionalidade 03: Editar Perfil

![Opção edição usuário](./imperativo/docs/fig5.png)

*Figura 05: Pelo menu principal quando usuário logado, o usuário escolhe a opção [1] para efetuar a edição de usuário.*

O usuário irá escolher a opção `[1]`  e em seguida, será possível selecionar qual campo deseja alterar. 

![Edição usuário](./imperativo/docs/fig6.png)

*Figura 06: Exibição  quando usuário efetua a edição do perfil do usuário.*

Após selecionado o campo, o usuário irá informar o novo valor do campo. Após concluída a edição o usuário poderá editar outro campo, caso ache necessário.

Caso o **ID** ou **Campo** informado seja inválido será lançada uma mensagem de erro.
