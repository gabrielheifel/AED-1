Trabalho agenda 2.0

Neste trabalho era pedido que fosse continuado a implementação da Agenda da semana 1, incluindo:

Imprimir de forma ordenada usando uma fila ordenada, onde:
   O usuário escolhe um parâmetro de ordenação e uma fila ordenada é criada.
   Depois o programa imprime na tela o conteúdo da fila

Neste exercício eu dou a opção de ordenar a fila por ordem alfabética ou numérica(função 'ordenar'). Logo após, é criado um vetor de string('matriz') que armazena os dados do buffer para ordena-los neste vetor de string, usando insertion sort. Enquanto ordena, um outro vetor('index') manipula os endereços respectivos dos dados conforme esses dados são ordenados. Então, ao final da ordenação, uso os valores salvos dentro de 'index' para pegar os Contatos dentro do buffer e dar um PUSH para dentro da fila. Desta forma, a fila respeita a obrigatoriedade de não acontecer ordenação dentro dela. Também o buffer mantém os dados na mesma ordem que foram inseridos, sem serem ordenados.
Após ordenar, o programa volta para o menu, e então, pode-se ver o resultado da ordenação clicando em '6) Imprime fila ordenada', que chama a função imprimeFila.

Implementar a base de dados da agenda usando lista duplamente ligada:
   Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um malloc para cada nodo.

Não consegui fazer este exercício, perdi muito tempo tentando desenvolver uma forma para ordenar sem ordenar, nem o buffer, nem a fila.

Obs: addDefault e nomesDefault são funções para adicionar nomes para facilitar os testes.