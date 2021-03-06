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

[Documentação completa.]()

## Como executar o PrompSkoob Imperativo (C++)?

Deve ter o compilador de C++, `g++` e executar o seguinte comando dentro da pasta do projeto:
```
g++ main.cpp -o main -l sqlite3
```
Após compilado, execute:
```
./main
```
É necessário ter o sqlite3 instalado na sua máquina, nos sistemas Linux/Mac vem previamente instalado, mas caso não 
tenha instalado utilize as seguintes [instruções](https://www.sqlite.org/download.html) ou via *packagers manager:*

Linux
```
apt-get install sqlite3
apt-get install libsqlite3-dev
```
Windows, usando [Chocolatey](https://chocolatey.org)
```
choco install sqlite
```
Mac OS
```
brew install sqlite
```

## Como executar o PrompSkoob Funcional (Haskell)?

É necessário instalar o Haskell no seu computador, possível instalar por [aqui](https://www.haskell.org/downloads/). Após a instalação, é necessário executar os seguintes comandos para instalar as dependências:
```
cd funcional
cabal install
```
Após instalado as dependências, execute a aplicação com o seguinte comando:
```
stack build
```
## Como executar o PrompSkoob Lógico (Prolog)?

É necessário instalar o Prolog no seu computador, possível instalar por [aqui](https://www.swi-prolog.org/download/stable). 
Após a instalação, instale o pacote `prosqlite` conforme [aqui](https://www.swi-prolog.org/pack/list?p=prosqlite) 
executando o comando:
```
swipl
?- pack_install( prosqlite ).
```
Caso obtenha o erro `ERROR: url 'https://www.swi-prolog.org/pack/query'' does not exist (status(500,Internal Server Error))` 
ao tentar instalar a biblioteca `prosqlite`. Possível [solução](https://swi-prolog.discourse.group/t/www-swi-prolog-org-goes-https/811/2).

Após concluída a instalação do pacote, execute:
```
cd logico
swipl main.pl
```
