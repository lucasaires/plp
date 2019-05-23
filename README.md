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

## Como executar?

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
