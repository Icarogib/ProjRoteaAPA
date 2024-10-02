# ProjRoteaAPA
Projeto para a disciplina de APA
<br>
prazo: 29/10/23
<br>
Sprints (4):
<br>
1 -> Euristica de construcao (ao menos 1) 
<br>
1 (1 ao menos)/ 2 (o resto) -> Estrutura de vizinhança (ao menos 3)
<br>
1 -> CRUD
<br>
2/3 -> VND
<br>
3 -> Meta-heuristica (ILS ou GRASP)
<br>
3/4 -> Saídas (tabela etc)
<br>
? -> Makefile
<br>
<br>
//<br>
Variáveis:
<br>grafo G = (V,A)
<br>
n -> numero de pontos para a entrega
<br>
cij -> custo caminho
<br>
i -> cliente
<br>
di -> demanda por cliente
<br>
k -> veiculos
<br>
Q -> capacidade veiculos
<br>
V -> vertices
<br>
A -> arcos (i,j)
<br>
r -> custo veiculo
<br>
pi -> valor de terceirizacao de entrega
<br>
L -> ao menos L entregas nao terceirizadas
<br>
<br>
iniciar no vertice 0, 
acabar no vertice 0.
<br>
MINIMIZAR CUSTO ARCOS, VEICULOS E TERCEIRIZADO
melhor rota.
<br>
Planejamento:
(prioridades a serem colocadas)
<br>
- Ler arquivos e criar arquivos. (basicamente CRUD)
<br>
- Salvar os dados do arquivo na memoria.
<br>
- Fazer uma rota por veiculo de capacidade Q.
	+ Decidir qual aproximacao vamos utilizar.
		(1 Heuristica de construcao(guloso))
		(3 Estruturas de vizinhanca)
		(VND)
		(GRASP/ILS)
<br>
- Respeitar limite L e Q.
<br>
- Soma de todos os custos: 
	+ Uso de veiculos (dado por r)
	+ Custo das rotas (dado pela soma de cij)
	+ Custo da terceirizacao (se utilizada)
<br>
- Apresentar valores conforme a especificacao.
<br>
- Criacao de tabela (Heuristicas construtivas e VND)
	+ especificacao!
<br>
- Makefile!
<br>

Observações após o término:

- O projeto foi feito em conjunto, e não foi satisfatório pois foi recebidas informações que não condizem com o que era requisitado pelo professor.
  Logo, a implementação não ficou condizente com o que foi pedido, e houveram "gambiarras" quando chegava informações de última hora.
  Foi um projeto em conjunto, e nem tudo condiz com a minha habilidade atual.



obs:
- Alteracoes diretas, por referencia.
- Sem problema se faltar uma entrega, terceirizamos.
