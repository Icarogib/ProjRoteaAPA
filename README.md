# ProjRoteaAPA
Projeto para a disciplina de APA

prazo: 29/10/23

Sprints (4):

1 -> Euristica de construcao (ao menos 1) 

1 (1 ao menos)/ 2 (o resto) -> Estrutura de vizinhança (ao menos 3)

1 -> CRUD

2/3 -> VND

3 -> Meta-heuristica (ILS ou GRASP)

3/4 -> Saídas (tabela etc)

? -> Makefile


//
Variáveis:
grafo G = (V,A)

cij -> custo caminho

i -> cliente

di -> demanda por cliente

k -> veiculos

Q -> capacidade veiculos
V -> vertices

A -> arcos (i,j)


r -> custo veiculo

pi -> valor de terceirizacao de entrega

L -> ao menos L entregas nao terceirizadas



iniciar no vertice 0, 
acabar no vertice 0.

MINIMIZAR CUSTO ARCOS, VEICULOS E TERCEIRIZADO
melhor rota.

Planejamento:
(prioridades a serem colocadas)

- Ler arquivos e criar arquivos. (basicamente CRUD)

- Salvar os dados do arquivo na memoria.

- Fazer uma rota por veiculo de capacidade Q.
	+ Decidir qual aproximacao vamos utilizar.
		(1 Heuristica de construcao(guloso))
		(3 Estruturas de vizinhanca)
		(VND)
		(GRASP/ILS)

- Respeitar limite L e Q.

- Soma de todos os custos: 
	+ Uso de veiculos (dado por r)
	+ Custo das rotas (dado pela soma de cij)
	+ Custo da terceirizacao (se utilizada)

- Apresentar valores conforme a especificacao.

- Criacao de tabela (Heuristicas construtivas e VND)
	+ especificacao!

- Makefile!




obs:
- Alteracoes diretas, por referencia.
- Sem problema se faltar uma entrega, terceirizamos.
